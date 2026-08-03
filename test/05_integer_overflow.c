#include <stdio.h>
#include <stdlib.h>

void allocate_array(unsigned int count) {
    // Vulnerable: count * sizeof(int) can overflow if count is large
    size_t size = count * sizeof(int); 
    int *array = (int *)malloc(size);

    if (array == NULL) {
        printf("Allocation failed!\n");
        return;
    }

    printf("Allocated %zu bytes successfully for %u elements.\n", size, count);
    free(array);
}

int main() {
    // 1,073,741,824 * 4 = 4,294,967,296 (0x100000000), which wraps to 0 in 32-bit arithmetic
    allocate_array(1073741824); 
    return 0;
}