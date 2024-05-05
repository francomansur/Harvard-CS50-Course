#include <cs50.h>
#include <stdio.h>

// Function prototype for printing a single row of the pyramid
void print_row(int spaces, int bricks);
int main(void)
{

    // Variables declared to be within scope
    int height;
    int spaces;

    // Get the desired height of the pyramid from the user
    do
    {
        height = get_int("Pyramid height (1 to 8): ");
    }
    while (height > 8 || height < 1);

    // Loop through each level of the pyramid
    for (int i = 0; i < height; i++)
    {

        // Calculate the number of spaces for the current row
        spaces = height - i - 1;

        // Print the current row with the calculated number of spaces and bricks
        print_row(spaces, i + 1);
    }
}

// Define the function to print spaces and bricks for a single row
void print_row(int spaces, int bricks)
{

    // Print the spaces before the bricks
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    // Print the left bricks
    for (int j = 0; j < bricks; j++)
    {
        printf("#");
    }

    // Gap between the pyramids (size: 2 bricks)
    for (int j = 0; j < 2; j++)
    {
        printf(" ");
    }

    // Print the right bricks
    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }

    // Move to the next line after printing a row
    printf("\n");
}
