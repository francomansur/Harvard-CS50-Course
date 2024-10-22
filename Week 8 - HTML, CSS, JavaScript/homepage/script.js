window.onload = function() {
    const currentLocation = window.location.pathname;
    const menuItems = document.querySelectorAll('.nav-pills .nav-link');

    menuItems.forEach(item => {
        if (item.pathname === currentLocation) {
            item.classList.add('active');
        } else {
            item.classList.remove('active');
        }
    });
};

document.addEventListener('DOMContentLoaded', function() {
    document.getElementById("contact-button").addEventListener("click", function() {
        this.style.display = "none";

        document.getElementById("confirmation-message").style.display = "block";
    });
});
