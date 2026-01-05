#include <stdio.h>

int main() {
    FILE *f1 = fopen("filename.txt", "r");
    int ch;
    
    while ((ch = fgetc(f1)) != EOF) {
        printf("%c", ch);  // Temporary: just print characters
    }
    
    fclose(f1);
    return 0;
}