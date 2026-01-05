#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *f1;
    char ch;

    f1 = fopen("Laxcode.txt", "r");

    if (f1 == NULL) {
        printf("File not found\n");
        exit(0);
    }

    while ((ch = fgetc(f1)) != EOF) {
        printf("%c", ch);  // Temporary: just print characters
    }

    fclose(f1);
    return 0;
}