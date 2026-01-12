#include <stdio.h>
#include <string.h>

int main() {
    char username[20], password[20];

    // Predefined credentials
    char correctUser[] = "Elvis";
    char correctPass[] = "elvis@123";

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", password);

    // Compare username and password
    if (strcmp(username, correctUser) == 0 &&
        strcmp(password, correctPass) == 0) {
        printf("\nLogin Successful!\n");
    } else {
        printf("\nInvalid Username or Password!\n");
    }

    return 0;
}