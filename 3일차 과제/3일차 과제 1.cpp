#include <stdio.h>


int main()
{  double num;
   double sum = 0.0;
   double maxv, minv;
   for (int i = 1; i <= 5; ++i)
    { printf("write %d th number  ", i);
        scanf_s("%lf", &num);
           if (i == 1) 
           {maxv = num;
            minv = num;}
            
           else {
            if (num > maxv)
            {maxv = num;}
            if (num < minv)
            { minv = num;}
               }
        sum += num;}
    double ave = sum / 5;

    printf("result\n");
    printf("average is %.6f.\n", ave);
    printf("maximum value is %.6f.\n", maxv);
    printf("minimum value is %.6f.\n", minv);

    return 0;
}
