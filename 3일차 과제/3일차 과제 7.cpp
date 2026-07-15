#include <stdio.h>

int main() {
    int n, r;

    printf("write n: ");
    scanf_s("%d", &n);

    printf("Write r : ");
    scanf_s("%d", &r);


    int a = 1;
    for (int i = 1; i <= n; i++) 
    { a = a * i; }

    int b = 1;
    for (int i = 1; i <= (n - r); i++) 
    { b = b * i; }

    int sunyul = a / b;

    int jsunyul = 1;
    for (int i = 0; i < r; i++) 
     { jsunyul = jsunyul * n;  }

    int c = 1;
    for (int i = 1; i <= r; i++) 
      { c = c * i; }

    int johab = a / (b * c);

    int d = 1;
    for (int i = 1; i <= (n + r - 1); i++) 
      { d = d * i; }

    int e = 1;
    for (int i = 1; i <= (n - 1); i++)
     { e = e * i; }

    int jjohab = d / (e * c);

    printf("\nresult\n");
    printf("nP r = %d\n", sunyul);
    printf("nPI r = %d\n", jsunyul);
    printf("nC r = %d\n", johab);
    printf("nH r  = % d\n", jjohab);

    return 0;
}
