#include <cs50.h>
#include <stdio.h>

// Function prototype for verifying the card number using Luhn's algorithm
bool verify(long long card_number);
// Function prototype for determining the flag of the card (AMEX, VISA, MASTERCARD)
void card_flag(long long card_number);

int main(void)
{
    // Prompt user for the card number
    long long card_number = get_long_long("Card Number: ");

    // If the card number is valid according to Luhn's algorithm, determine the flag
    if (verify(card_number))
    {
        card_flag(card_number);
    }
    else
    {
        // If the card is not valid, print "INVALID"
        printf("INVALID\n");
    }
}

// Function to verify the card number using Luhn's algorithm
bool verify(long long card_number)
{
    int sum = 0; // Initialize sum for the checksum calculation
    int pos = 0; // Position of digit in card number, starting from 0

    // Process each digit starting from the end
    while (card_number > 0)
    {
        int digit = card_number % 10; // Get the last digit

        // If the position is odd (even index since we start at 0), double the digit
        if (pos % 2 == 1)
        {
            digit *= 2;

            // If the doubled digit is greater than 9, subtract 9 from it
            if (digit > 9)
            {
                digit -= 9;
            }
        }
        sum += digit; // Add the digit to the sum

        card_number /= 10; // Remove the last digit from the card number
        pos++;             // Move to the next position
    }

    // Return true if the sum is a multiple of 10, false otherwise
    return (sum % 10 == 0);
}

// Function to print the flag of the card based on the starting digits and the length
void card_flag(long long card_number)
{
    int length = 0; // Initialize length of the card number
    long long n = card_number;

    // Calculate the length of the card number
    while (n > 0)
    {
        n /= 10;
        length++;
    }

    // Calculate the divisor to isolate the first two digits
    long long divisor = 1;
    for (int i = 0; i < length - 2; i++)
    {
        divisor *= 10;
    }
    int first_two = card_number / divisor; // Get the first two digits

    int first_digit = first_two / 10; // Get the first digit for VISA check

    // Determine the flag of the card based on the starting digits and length
    if ((first_two == 34 || first_two == 37) && length == 15)
    {
        printf("AMEX\n"); // American Express starts with 34 or 37 and has 15 digits
    }
    else if (first_digit == 4 && (length == 13 || length == 16))
    {
        printf("VISA\n"); // Visa starts with 4 and has 13 or 16 digits
    }
    else if ((first_two == 51 || first_two == 52 || first_two == 53 || first_two == 54 ||
              first_two == 55) &&
             length == 16)
    {
        printf("MASTERCARD\n"); // MasterCard starts with 51 to 55 and has 16 digits
    }
    else
    {
        printf("INVALID\n"); // If none of the conditions are met, the card is invalid
    }
}
