#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

void keyw(char *p);

int i=0, id=0, kw=0, num=0, op=0, sp=0, ar=0, count=0, new_line=0;

char keys[32][10] = {
    "auto","break","case","char","const","continue","default","do","double",
    "else","enum","extern","float","for","goto","if","int","long","register",
    "return","short","signed","sizeof","static","struct","switch","typedef",
    "union","unsigned","void","volatile","while"
};

int main() {

    char ch, str[25], seps[20] = " \t\n,;(){}[]#\"<>", oper[] = "!%^&*-+=~|.<>/?";
    int j;
    FILE *f1;

    f1 = fopen("Laxcode.txt", "r");

    if(f1 == NULL) {
        printf("File not found");
        exit(0);
    }

    while((ch = fgetc(f1)) != EOF) {

        for(j=0; j <= 14; j++) {
            if(ch == oper[j]) {
                printf("%c is an operator\n", ch);
                op++;
                count++;
                str[i] = '\0';
                keyw(str);
            }
        }

        if(ch == '\n') {
            new_line++;
        }

        for(j=0; j <= 14; j++) {
            if(i == -1) break;

            if(ch == seps[j]) {

                if(ch == '#') {
                    while(ch != '>') {
                        printf("%c", ch);
                        ch = fgetc(f1);
                    }
                    printf("%c is a header file\n", ch);
                    i = -1;
                    break;
                }

                if(ch == '"') {
                    do {
                        ch = fgetc(f1);
                        printf("%c", ch);
                    } while(ch != '"');
                    printf("\b is an argument\n");
                    i = -1;
                    ar++;
                    count++;
                    break;
                }

                if(ch == ',' || ch == ';' || ch=='(' || ch==')' || ch=='{' || ch=='}' || ch=='[' || ch==']') {
                    printf("%c is a Separator\n", ch);
                    sp++;
                    count++;
                }

                str[i] = '\0';
                keyw(str);
            }
        }

        if(i != -1) {
            str[i] = ch;
            i++;
        } else {
            i = 0;
        }
    }

    printf("\nKeywords: %d\nIdentifiers: %d\nOperators: %d\nNumbers: %d\nSeparators: %d\nArguments: %d",
           kw, id, op, num, sp, ar);

    printf("\nTotal Tokens: %d", count);
    printf("\nNumber of lines: %d\n", new_line);

    fclose(f1);
    return 0;
}

void keyw(char *p) {
    int k, flag = 0;

    for(k=0; k <= 31; k++) {
        if(strcmp(keys[k], p) == 0) {
            printf("%s is a keyword\n", p);
            kw++;
            count++;
            flag = 1;
            break;
        }
    }

    if(flag == 0) {
        if(isdigit(p[0])) {
            printf("%s is a number\n", p);
            num++;
            count++;
        }
        else {
            if(p[0] != '\0') {
                printf("%s is an identifier\n", p);
                id++;
                count++;
            }
        }
    }

    i = -1;
}