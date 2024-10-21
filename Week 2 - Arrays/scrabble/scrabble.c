#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Array holding the point values for each letter of the alphabet.
int letter[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

// Function prototype for score_word which calculates the score of a given word.
int score_word(string player);

// Main function where the execution of the program begins.
int main(void)
{
    // Array of strings to store inputs from two players.
    string player[2];

    // Prompting each player for a word and storing the input.
    player[0] = get_string("Player 1: ");
    player[1] = get_string("Player 2: ");

    // Calculating scores for each player.
    int score1 = score_word(player[0]);
    int score2 = score_word(player[1]);

    // Outputting each player's score.
    printf("Player 1 Score: %i \n", score1);
    printf("Player 2 Score: %i \n", score2);
    printf("\n");

    // Determining the winner based on the scores.
    if (score1 > score2)
    {
        printf("Player 1 Wins! \n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 Wins! \n");
    }
    else
    {
        printf("Tie!\n");
    }
}

// Function to compute the score of a word based on letter values.
int score_word(string player)
{
    int score = 0;            // Initialize score to 0.
    int len = strlen(player); // Calculate the length of the word.

    // Iterate over each character in the word.
    for (int i = 0; i < len; i++)
    {
        if (islower(player[i])) // If the character is a lowercase letter.
        {
            score += letter[player[i] - 'a']; // Add the point value of the letter to score.
        }
        else if (isupper(player[i])) // If the character is an uppercase letter.
        {
            score += letter[player[i] - 'A']; // Add the point value of the letter to score.
        }
    }
    return score; // Return the total score for the word.
}
