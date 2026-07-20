#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("how many number would you write : ");
    if (scanf("%d", &n) != 1) {//정수가 아니면 에러처리
        printf("wrong number\n");
        return 1;
    }
    if (n <= 0) {// 원소개수 0혹은 음수면 오류
        printf("number should exist at least one\n");
        return 1;
    }
    int* arr = (int*)malloc(n * sizeof(int));// 입력 받은 개수 만큼 정수형 배열 동적 할당
    for (int i = 0; i < n; i++) {// 원소 개수만큼 반복숫자 입력
        printf("write int:"); 
        if (scanf("%d", &arr[i]) != 1) {//정수 아니면
            printf("wrong you should write int\n");
            free(arr);//메모리 해제
            return 1;
        }
    }
    int max = arr[0]; //원소 초기화
    int min = arr[0];
    int sum = 0;
    for (int i = 0; i < n; i++) { //원소 하나씩 보기
        if (arr[i] > max) max = arr[i]; //출력
        if (arr[i] < min) min = arr[i];
        sum += arr[i]; 
    }
    double avg = (double)sum / n;// 소수도 가능하게 형 바꿈
    printf("max: %d\n", max);
    printf("min: %d\n", min);
    printf("sum: %d\n", sum);
    printf("avg: %f\n", avg);
    free(arr);
    return 0;
}
