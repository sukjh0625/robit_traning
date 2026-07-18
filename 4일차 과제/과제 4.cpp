#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int n, b;
    int arr[1000]; //배열
    int budi = -1; // b가 어디인지 변수 b udi
    printf("N : ");
    scanf("%d", &n);
    printf("B : ");
    scanf("%d", &b);
    printf("\n");
    for (int i = 0; i < n; i++) { //하나씩 판별 하기
        scanf("%d", &arr[i]);
        if (arr[i] == b) { //전 과제에서 했던 것 
            budi = i; // B의 방 번호를 budi에 기억
        }
    }

    int count = 0; // 조건에 맞는 부분 수열의 개수

    for (int left = 0; left <= budi; left++) { //b의 위치 따라 오른쪽 왼쪽 정하기
        for (int right = budi; right < n; right++) { //맨 끝지점 찾기

            int biggerb = 0;  // B보다 큰 숫자의 개수
            int smallerb = 0; // B보다 작은 숫자의 개수
            for (int k = left; k <= right; k++) { // 개수세기
                if (arr[k] > b) { //만약 b보다 크다면 1더하기
                    biggerb++;
                }
                else if (arr[k] < b) { //만약 b보다 작다면  smallerb에더하기 1
                    smallerb++;
                }
            }
            if (biggerb == smallerb) {
                count++; // 1점 내기
            }
        }
    }

    printf("result : %d\n", b, count);

    return 0;
}
