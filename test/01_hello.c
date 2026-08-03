#include <stdio.h>

void print_grade(int score) {
    if (score >= 90) {
        printf("Grade: A\n");
    } else if (score >= 75) {
        printf("Grade: B\n");
    } else {
        printf("Grade: C or below\n");
    }
}

int main() {
    int score = 0;
    printf("Enter score: ");
    if (scanf("%d", &score) == 1) {
        print_grade(score);
    }
    return 0;
}