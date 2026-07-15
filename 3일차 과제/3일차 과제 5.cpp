#include <stdio.h>

int main() {
    int n;

    printf("write a value : ");

   if (scanf_s("%d", &n) != 1 || n <= 0) 
   {printf("enter a natural number greater than or equal to 1\n");
        return 1; }

    for (int i = 1; i < n; i++) 
    { for (int j = 0; j < i; j++) 
    {printf("*"); }
        for (int j = 0; j < 2 * (n - i); j++) 
        {printf(" "); }
        for (int j = 0; j < i; j++) 
        { printf("*");}
        printf("\n");
    }

    for (int j = 0; j < 2 * n; j++) 
    { printf("*"); }
    printf("\n");

    for (int i = n - 1; i >= 1; i--) 
    { for (int j = 0; j < i; j++) 
    { printf("*"); }
        for (int j = 0; j < 2 * (n - i); j++) 
        { printf(" "); }
        for (int j = 0; j < i; j++) 
        { printf("*"); }
        printf("\n"); 
    }

    return 0;
}
