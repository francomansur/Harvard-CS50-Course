#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Whats is your name? ");
    printf("Hello, %s\n", name);
}
