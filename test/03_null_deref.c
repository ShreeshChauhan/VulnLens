#include <stdio.h>
#include <stdlib.h>

void inspect_data(int *ptr, int flag) {
    if (flag == 1) {
        // Vulnerable: ptr is NULL when flag is 1
        printf("Value: %d\n", *ptr); 
    } else if (ptr != NULL) {
        printf("Valid value: %d\n", *ptr);
    }
}

int main() {
    int *data = NULL;
    inspect_data(data, 1);
    return 0;
}