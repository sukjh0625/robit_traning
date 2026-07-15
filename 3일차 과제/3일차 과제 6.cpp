#include <stdio.h>

int main() {
    int n;

    printf("write a value . ");
    if (scanf_s("%d", &n) != 1 || n <= 0) {
        printf("enter a natural number greater than or equal to 1\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {

        for (int j = 0; j < n - i; j++) {
            printf(" ");
        }

        if (i == 1) {
            printf("*\n"); 
        }
        else if (i == n) {
            for (int j = 0; j < 2 * n - 1; j++) {
                printf("*");
            }
            printf("\n"); 
        }
        else {
            printf("*"); 

            for (int j = 0; j < 2 * i - 3; j++) {
                printf(" ");
            }

            printf("*\n"); 
        }
    }

    return 0;
}
