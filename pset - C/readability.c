#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int coleman_liau(int letters, int words, int sentences);

int main(void)
{
    // Prompt the user for some text
    string text = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    int index = coleman_liau(letters, words, sentences);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    if ((index > 1) && (index <= 16))
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    // Return the number of letters in text
    int letters = 0;
    int n = strlen(text);

    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }

    return letters;
}

int count_words(string text)
{
    // Return the number of words in text
    int words = 0;
    int in_word = 0;

    while (*text)
    {
        if (isspace(*text))
        {
            in_word = 0;
        }
        else if (!in_word)
        {
            in_word = 1;
            words++;
        }
        text++;
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;

    while (*text)
    {
        if (*text == '.' || *text == '!' || *text == '?')
        {
            sentences++;
        }
        text++;
    }
    return sentences;
}

int coleman_liau(int letters, int words, int sentences)
{
    double L = ((double) letters / words) * 100;
    double S = ((double) sentences / words) * 100;

    double index = 0.0588 * L - 0.296 * S - 15.8;

    return round(index);
}
