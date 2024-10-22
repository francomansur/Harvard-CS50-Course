import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    user_stocks_sum = db.execute("""
        SELECT symbol, SUM(shares) AS total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id)

    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]

    portfolio_value = 0
    stocks = []

    for stock in user_stocks_sum:
        stock_price = lookup(stock["symbol"])["price"]
        total_value = stock["total_shares"] * stock_price
        portfolio_value += total_value

        stocks.append({
            "symbol": stock["symbol"],
            "shares": stock["total_shares"],
            "price": stock_price,
            "total_value": total_value,
        })

    grand_total = portfolio_value + user_cash

    return render_template("index.html", cash=user_cash, stocks=stocks, portfolio_value=portfolio_value, grand_total=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    user_id = session["user_id"]

    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = user_cash[0]["cash"]
    session["cash"] = cash

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return render_template("buy.html", symbol_error="You must provide a stock symbol.", cash=cash), 400

        try:
            shares = int(shares)
            if shares <= 0:
                return render_template("buy.html", symbol_error="Invalid number of shares.", cash=cash), 400
        except ValueError:
            return render_template("buy.html", symbol_error="Shares must be a valid integer.", cash=cash), 400

        stock = lookup(symbol)
        if not stock:
            return render_template("buy.html", symbol_error="This stock does not exist.", cash=cash), 400

        total_cost = stock["price"] * shares

        if total_cost > cash:
            return render_template("buy.html", symbol_error="Not enough cash to complete the purchase.", cash=cash), 400

        new_cash = cash - total_cost
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_type) VALUES (?, ?, ?, ?, ?)",
                   user_id, symbol, shares, stock["price"], "buy")

        return redirect("/")

    return render_template("buy.html", cash=cash)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    user_transactions = db.execute(
        "SELECT symbol, shares, price, transaction_type, timestamp FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transactions=user_transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return render_template("login.html", username_error=True)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return render_template("login.html", password_error=True)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return render_template("login.html", user_pass_error=True)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/quote")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")

        user_shares = db.execute("""
        SELECT SUM(shares) AS total_shares
        FROM transactions
        WHERE user_id = ? AND symbol = ?
        GROUP BY symbol
         """, user_id, symbol)

        user_shares_sum = user_shares[0]["total_shares"] if user_shares else 0

        if not symbol:
            return render_template("quote.html", symbol_error="This stock does not exist.", cash=session.get("cash"), user_shares_sum=user_shares_sum), 400

        stock = lookup(symbol)

        if not stock:
            return render_template("quote.html", symbol_error="This stock does not exist.", cash=session.get("cash"), user_shares_sum=user_shares_sum), 400

        stock["price"] = float(stock["price"])

        return render_template("quoted.html", stock=stock, cash=session.get("cash"), user_shares_sum=user_shares_sum)

    return render_template("quote.html", cash=session.get("cash"))


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirm_password = request.form.get("confirmation")

        if not username or not password or not confirm_password:
            return render_template("register.html", field_blank_error="All fields are mandatory."), 400

        if password != confirm_password:
            return render_template("register.html", password_match_error="Passwords do not match."), 400

        password_hash = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash)
        except ValueError:
            return render_template("register.html", username_error="Username already exist."), 400

        return redirect("/success")

    return render_template("register.html")


@app.route("/success")
def success():
    """Display success message after registration"""
    return render_template("success.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    user_stocks = db.execute("""
        SELECT symbol, SUM(shares) AS total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, user_id)

    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = user_cash[0]["cash"]

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return render_template("sell.html", symbol_error="You must select a stock to sell.", cash=cash, stocks=user_stocks), 400

        try:
            shares = int(shares)
            if shares <= 0:
                return render_template("sell.html", symbol_error="Invalid number of shares.", cash=cash, stocks=user_stocks), 400
        except ValueError:
            return render_template("sell.html", symbol_error="Shares must be a valid integer.", cash=cash, stocks=user_stocks), 400

        stock_owned = db.execute("""
            SELECT SUM(shares) AS total_shares
            FROM transactions
            WHERE user_id = ? AND symbol = ?
            GROUP BY symbol
        """, user_id, symbol)

        if not stock_owned or stock_owned[0]["total_shares"] < shares:
            return render_template("sell.html", symbol_error="You don't have enough shares to sell.", cash=cash, stocks=user_stocks), 400

        stock = lookup(symbol)
        if not stock:
            return render_template("sell.html", symbol_error="This stock does not exist.", cash=cash, stocks=user_stocks), 400

        total_sale_value = stock["price"] * shares

        new_cash = cash + total_sale_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", new_cash, user_id)

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, transaction_type) VALUES (?, ?, ?, ?, ?)",
                   user_id, symbol, -shares, stock["price"], "sell")

        return redirect("/")

    return render_template("sell.html", cash=cash, stocks=user_stocks)


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    user_id = session["user_id"]
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = user_cash[0]["cash"]
    session["cash"] = cash

    if request.method == "POST":

        deposit_value = request.form.get("deposit").replace("$", "").replace(",", "")
        deposit_value = float(deposit_value)

        if deposit_value <= 0:
            return render_template("deposit.html", error="Please enter a valid amount.", cash=cash)

        wallet_deposit_value = cash + deposit_value
        db.execute("UPDATE users SET cash = ? WHERE id = ?", wallet_deposit_value, user_id)

        session["cash"] = wallet_deposit_value

        return render_template("deposit.html", cash=session["cash"], success=True, deposit_value=deposit_value, new_balance=wallet_deposit_value)

    return render_template("deposit.html", cash=cash)
