#include <stdio.h>

int main() {
    int n;
    printf("write n: ");
    scanf_s("%d", &n);

   
    if (n <= 0)
    {printf("please write natural number.\n");
        return 0;}
    
    if (n == 1)
    {printf("first Fibonacci number: 0\n");}
    else if (n == 2) 
    {printf(" second Fibonacci number: 1\n");}
    else 
    {int jungap2 = 0;  
     int jungap1 = 1; 
     int current = 0;  
          
     for (int i = 3; i <= n; i++)
     {
         current = jungap1 + jungap2;
         jungap2 = jungap1;
         jungap1 = current;
     }
       

        printf("%dth Fibonacci number: %d\n", n, current);}

    return 0;
}
