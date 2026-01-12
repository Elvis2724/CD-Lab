#include <stdio.h>
#include <ctype.h>

int main() {
    char ch;
    int digits = 0, vowels = 0, consonants = 0, symbols = 0;

    printf("Enter a line:\n");

    while ((ch = getchar()) != '\n') {

        // Check digit
        if (isdigit(ch)) {
            digits++;
        }
        // Check alphabet
        else if (isalpha(ch)) {
            // Check vowel
            if (ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'||
                ch=='A'||ch=='E'||ch=='I'||ch=='O'||ch=='U') {
                vowels++;
            } else {
                consonants++;
            }
        }
        // Check symbol (special characters)
        else if (!isspace(ch)) {
            symbols++;
        }
    }

    printf("Digits      : %d\n", digits);
    printf("Vowels      : %d\n", vowels);
    printf("Consonants  : %d\n", consonants);
    printf("Symbols     : %d\n", symbols);

    return 0;
}