#include <stdio.h>

int main() {
    int year;

    printf("write year : ");
    scanf_s("%d", &year);

   if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) 
   {printf("leap year\n");}
    else 
   {printf("common year\n");}

    return 0;
}
