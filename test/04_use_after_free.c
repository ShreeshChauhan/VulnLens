#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[20];
} User;

int main() {
    User *u = (User *)malloc(sizeof(User));
    if (!u) return 1;

    u->id = 101;
    printf("User ID: %d\n", u->id);

    free(u); // Memory released

    // Vulnerable: Modifying freed memory
    u->id = 202; 
    printf("Dangling ID access: %d\n", u->id);

    return 0;
}