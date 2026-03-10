#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

// Function Prototypes
void push(char *s, int *sp, char item);
char pop(char *s, int *sp);
char stacktop(char *s);
void isproduct(char x, char p);
void isreduce(char x, char p);
int ister(char x);
int isnter(char x);
int isstate(char p);
void error();
void printt(char *t, int *p, char inp[], int i);
void rep(char t[], int r);

// Structures for Parser Tables
struct action {
    char row[6][5];
};

struct gotol {
    char r[3][4];
};

struct grammar {
    char left;
    char right[5];
};

// Global Data
const struct action A[12] = {
    {"sf", "emp", "emp", "se", "emp", "emp"}, // State 0
    {"emp", "sg", "emp", "emp", "emp", "acc"}, // State 1
    {"emp", "rc", "sh", "emp", "rc", "rc"},   // State 2
    {"emp", "re", "re", "emp", "re", "re"},   // State 3
    {"sf", "emp", "emp", "se", "emp", "emp"}, // State 4
    {"emp", "rg", "rg", "emp", "rg", "rg"},   // State 5
    {"sf", "emp", "emp", "se", "emp", "emp"}, // State 6
    {"sf", "emp", "emp", "se", "emp", "emp"}, // State 7
    {"emp", "sg", "emp", "emp", "sl", "emp"}, // State 8
    {"emp", "rb", "sh", "emp", "rb", "rb"},   // State 9
    {"emp", "rb", "rd", "emp", "rd", "rd"},   // State 10
    {"emp", "rf", "rf", "emp", "rf", "rf"}    // State 11
};

const struct gotol G[12] = {
    {"b", "c", "d"},    {"emp", "emp", "emp"}, {"emp", "emp", "emp"},
    {"emp", "emp", "emp"}, {"i", "c", "d"},       {"emp", "emp", "emp"},
    {"emp", "j", "d"},     {"emp", "emp", "k"},   {"emp", "emp", "emp"},
    {"emp", "emp", "emp"}, {"emp", "emp", "emp"}, {"emp", "emp", "emp"}
};

char ter[6] = {'i', '+', '*', ')', '(', '$'};
char nter[3] = {'E', 'T', 'F'};
char states[12] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'm', 'j', 'k', 'l'};
char stack[100];
int top = -1;
char temp[10];

const struct grammar rl[6] = {
    {'E', "E+T"}, {'E', "T"}, {'T', "T*F"}, {'T', "F"}, {'F', "(E)"}, {'F', "i"}
};

void main() {
    char inp[80], x, p, dl[2], y, bl = 'a';
    int i = 0, j, k, n, len;

    system("cls"); // Clear screen
    printf("Enter the input: ");
    scanf("%s", inp);

    len = strlen(inp);
    inp[len] = '$';
    inp[len + 1] = '\0';

    push(stack, &top, bl); // Push initial state 'a' (0)

    printf("\nStack\t\t\tInput");
    printf("\n-------------------------------------");
    printt(stack, &top, inp, i);

    do {
        x = inp[i];
        p = stacktop(stack);
        isproduct(x, p);

        if (strcmp(temp, "emp") == 0) {
            error();
        }

        if (strcmp(temp, "acc") == 0) {
            break;
        } else {
            if (temp[0] == 's') {
                // SHIFT
                push(stack, &top, inp[i]);   // Push Symbol
                push(stack, &top, temp[1]); // Push State
                i++;
            } else if (temp[0] == 'r') {
                // REDUCE
                j = isstate(temp[1]);       // Get grammar rule index
                n = strlen(rl[j - 2].right); // Get length of RHS

                // Pop 2*n elements (Symbol + State pairs)
                for (k = 0; k < 2 * n; k++) {
                    pop(stack, &top);
                }

                y = stacktop(stack);        // Get state currently at top
                dl[0] = rl[j - 2].left;     // Get LHS Non-terminal
                dl[1] = '\0';

                push(stack, &top, dl[0]);   // Push LHS Symbol
                isreduce(y, dl[0]);         // Find next state from GOTO table
                push(stack, &top, temp[0]); // Push New State
            }
        }
        printt(stack, &top, inp, i);
    } while (1);

    if (strcmp(temp, "acc") == 0)
        printf("\n\nSuccess: Input Accepted!");
    else
        printf("\n\nError: Input Rejected.");

    getch();
}

// Helper Functions
void push(char *s, int *sp, char item) {
    if (*sp == 99) printf("Stack Overflow");
    else s[++(*sp)] = item;
}

char pop(char *s, int *sp) {
    if (*sp == -1) return '\0';
    return s[(*sp)--];
}

char stacktop(char *s) {
    return s[top];
}

void isproduct(char x, char p) {
    int k = ister(x);
    int l = isstate(p);
    if (k > 0 && l > 0) strcpy(temp, A[l - 1].row[k - 1]);
    else strcpy(temp, "emp");
}

void isreduce(char x, char p) {
    int k = isstate(x);
    int l = isnter(p);
    if (k > 0 && l > 0) strcpy(temp, G[k - 1].r[l - 1]);
    else strcpy(temp, "emp");
}

int ister(char x) {
    for (int i = 0; i < 6; i++) if (x == ter[i]) return i + 1;
    return 0;
}

int isnter(char x) {
    for (int i = 0; i < 3; i++) if (x == nter[i]) return i + 1;
    return 0;
}

int isstate(char p) {
    for (int i = 0; i < 12; i++) if (p == states[i]) return i + 1;
    return 0;
}

void error() {
    printf("\nSyntax Error: Invalid transition.");
    getch();
    exit(0);
}

void printt(char *t, int *p, char inp[], int i) {
    int r;
    printf("\n");
    for (r = 0; r <= *p; r++) rep(t, r);
    printf("\t\t\t");
    for (r = i; inp[r] != '\0'; r++) printf("%c", inp[r]);
}

void rep(char t[], int r) {
    char c = t[r];
    if (c >= 'a' && c <= 'l') {
        // Map chars back to state numbers for display
        int val = isstate(c) - 1;
        printf("%d", val);
    } else {
        printf("%c", c);
    }
}