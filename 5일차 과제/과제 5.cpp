#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N;
    printf("write N: ");
    if (scanf("%d", &N) != 1) { //1이 아니면 오류로 끝내기
        printf("write correct number\n");
        return 1;
    }
    if (N <= 0) { // 크기가 0이하이면 끝내기
        printf("size is at least 1\n");
        return 1;
    }
    int** dagaksun = (int**)malloc(N * sizeof(int*)); //세로 크기만큼 공간 동적 할당
    for (int i = 0; i < N; i++) {//행의 개수만큼 하나씩 돌아가며보기
        dagaksun[i] = (int*)malloc(N * sizeof(int)); //가로 크기만큼 정수형 배열 만들기
    }
    int num = 1;//배열에 1부터 넣음
    for (int k = 0; k <= 2 * N - 2; k++) {//행과 열 합의 최솟값부터 최댓값까지 반복
        for (int i = 0; i < N; i++) {// 행 첨부터 끝까지 보기
            int j = k - i;//k가 i+j이다
            if (j >= 0 && j < N) {// 범위 안에 있는지 체크
                dagaksun[i][j] = num++;// 하나씩 증가 시키기
            }
        }
    }
    printf("result\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%3d ", dagaksun[i][j]);
        }
        printf("\n");
    }
    for (int i = 0; i < N; i++) {//한개씩 해제 하기
        free(dagaksun[i]); //가로 해제 
    }
    free(dagaksun); //세로해제
    return 0;
}
