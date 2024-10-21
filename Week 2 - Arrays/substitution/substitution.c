#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Function prototype declaration for checking the validity of the cipher key
bool is_valid_key(string key);

int main(int argc, string argv[])
{
    // Check if the correct number of arguments is provided and if the provides key is valid
    if (argc != 2 || !is_valid_key(argv[1]))
    {
        printf("Usage: ./substitution key\n");
        return 1; // Return with error code 1 indicating incorrect usage
    }

    string key = argv[1]; // Store the substitution key provided as command line argument
    string plaintext = get_string("plaintext: "); // Get the plaintext from the user
    printf("ciphertext: ");

    int n = strlen(plaintext);  // Determine the length of the plaintext
    for (int i = 0; i < n; i++) // Iterate over each character in the plaintext
    {
        char c = plaintext[i]; // Current character in plaintext

        if (isalpha(c))
        {
            int index =
                toupper(c) - 'A'; // Calculate index for substitution (0 for 'A', 1 for 'B', etc.)
            char mapped_char = isupper(c)
                                   ? toupper(key[index])
                                   : tolower(key[index]); // Map using the key and maintain case
            printf("%c", mapped_char); // Print the mapped character as part of ciphertext
        }
        else
        {
            printf("%c", c); // If non-alphabetic, print the character as is
        }
    }
    printf("\n");
    return 0;
}

// Function to check if the key is valid
bool is_valid_key(string key)
{
    int length = strlen(key); // Get the length of the key

    if (length != 26) // Ensure the key is exactly 26 characters long
        return false;

    int letters[26] = {0}; // Array to track each letter's occurrence in the key

    for (int i = 0; i < length; i++) // Loop through each character in the key
    {
        if (!isalpha(key[i])) // Check if the character is not alphabetic
            return false;

        int index = toupper(key[i]) - 'A'; // Calculate index based on alphabetic position

        if (letters[index] > 0) // Check if the letter has already been used
            return false;
        letters[index]++; // Mark this letter as used
    }
    return true; // Return true if the key passes all checks
}
