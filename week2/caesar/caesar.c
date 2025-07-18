#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]) % 26;
    string text = get_string("plaintext: ");

    printf("ciphertext: ");
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]))
        {
            char base = isupper(text[i]) ? 'A' : 'a';
            printf("%c", (text[i] - base + key) % 26 + base);
        }
        else
        {
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}
