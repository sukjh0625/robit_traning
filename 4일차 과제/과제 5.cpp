#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int min, max;
    printf("min : ");
    scanf("%d", &min);

    printf("max : ");
    scanf("%d", &max);

    int count = 0; // 제곱 ㄴㄴ가 몇 개인지 알려주는 변수
    int save[10000]; // 정답 숫자들 배열

    for (int i = min; i <= max; i++) {//계속 쓰는 애

        int jegopsu = 0; // 제곱수로 나누어떨어지는 가?

        for (int j = 2; j * j <= i; j++) {
            int square = j * j; // 4부터 제곱수 만들기
            if (i % square == 0) {//나누어 떨어지면 아님
                jegopsu = 1; // 제곱수가 맞음
            }
        }
        if (jegopsu == 0) {
            save[count] = i; // 배열에 넣기
            count++;         // 정답 개수 한개 더하기
        }
    }
    printf("not square : %d\n", count);

    for (int i = 0; i < count; i++) {
        printf("%d ", save[i]);
    }
    printf("\n");

    return 0;
}
