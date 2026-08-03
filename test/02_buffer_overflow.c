#include <stdio.h>
#include <string.h>

void process_input(char *user_input) {
    char buffer[16];
    // Vulnerable: no boundary check on user_input
    strcpy(buffer, user_input);
    printf("Processed string: %s\n", buffer);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        process_input(argv[1]);
    } else {
        printf("Usage: %s <input_string>\n", argv[0]);
    }
    return 0;
}