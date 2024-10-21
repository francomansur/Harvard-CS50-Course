from cs50 import get_int


def luhn_algorithm(card_number):
    card_number_str = str(card_number)
    total_sum = 0

    for i in range(len(card_number_str)):
        digit = int(card_number_str[-(i + 1)])

        if i % 2 == 1:
            digit *= 2
            if digit > 9:
                digit = digit - 9

        total_sum += digit

    return total_sum % 10 == 0


def card_type(card_number):
    card_number_str = str(card_number)
    length = len(card_number_str)
    first_digit = int(card_number_str[0])
    first_two = int(card_number_str[:2])

    if (first_two == 34 or first_two == 37) and length == 15:
        return "AMEX"
    elif first_digit == 4 and (length == 13 or length == 16):
        return "VISA"
    elif (51 <= first_two <= 55) and length == 16:
        return "MASTERCARD"
    else:
        return "INVALID"


card_number = get_int("Number: ")

if luhn_algorithm(card_number):
    print(card_type(card_number))
else:
    print("INVALID")
