#include <stdio.h>

int main() {
    double num1, num2;
    char op;

       printf("Input Arithmetic Operation\n");
    printf("ex)      3.4 * 8.5\n");
    printf("         2.9 - 5.4\n");
    printf("         3.9 * 8.0\n");
    printf("         3.9 ^ 8\n\n");

    printf("input : ");

    
    if (scanf_s("%lf %c %lf", &num1, &op, 1, &num2) != 3) { //scan_f 썼더니 계속 오류가 나서 LLM사용 크기를 적지 않아서 오류발생
        printf("wrong input form\n");
        return 1;
    }

   
    switch (op) {
    case '+':
        printf("%.2f + %.2f = %.2f\n", num1, num2, num1 + num2);
        break;

    case '-':
        printf("%.2f - %.2f = %.2f\n", num1, num2, num1 - num2);
        break;

    case '*':
        printf("%.2f * %.2f = %.2f\n", num1, num2, num1 * num2);
        break;

    case '/':
        if (num2 == 0) {
            printf("cannot be devided by 0\n");
        }
        else {
            printf("%.2f / %.2f = %.2f\n", num1, num2, num1 / num2);
        }
        break;

    case '^': {
        double gap = 1.0;
        int jisu = (int)num2; 

        for (int i = 0; i < jisu; i++) {
            gap = gap * num1;
        }

        printf("%.2f ^ %.2f = %.2f\n", num1, num2, gap);
        break;
    }

    default:
        printf("Unsupported operator\n");
        break;
    }

    return 0;
}
