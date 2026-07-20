#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main() {
    int N1, N2; //N1 세로 N2 가로
    printf("write hang and yull: "); 
    if (scanf("%d %d", &N1, &N2) != 2) { //두개 입력 못받으면 끝내기
        printf("wrong number\n");
        return 1;
    }

    int** dalpangy = (int**)malloc(N1 * sizeof(int*));//세로 크기만큼 포인터에 공간 동적 할당
    for (int i = 0; i < N1; i++) {//행의 개수만큼 반복
        dalpangy[i] = (int*)malloc(N2 * sizeof(int)); // 가로 크기만큼 실제 정수형 배열 할당
    }
    int num = 1;//칸에 넣을 숫자 1로 설정
    int top = 0, bottom = N1 - 1; //공간의 위아래 경계선
    int left = 0, right = N2 - 1;//왼쪽 오른쪽 경계선

    while (num <= N1 * N2) { // 가로세로 곱해서 다 채워질때까지 반복
        for (int i = left; i <= right && num <= N1 * N2; i++) {// 위 행에서 왼쪽에서 오른쪽으로 이동하면서 채움
            dalpangy[top][i] = num++;// 현재 숫자를 하나씩 넣고 1씩 중가 시키기
        }
        top++;// 위부터 하나씩 내려오기

        for (int i = top; i <= bottom && num <= N1 * N2; i++) {//맨오른쪽 열에서 하나씩 넣고 증가시키기
            dalpangy[i][right] = num++;
        }
        right--;//왼쪽 한칸오기

        for (int i = right; i >= left && num <= N1 * N2; i--) {//맨 아래행
            dalpangy[bottom][i] = num++;
        }
        bottom--;//한칸 올리기

        for (int i = bottom; i >= top && num <= N1 * N2; i--) {
            dalpangy[i][left] = num++;
        }
        left++; //오른쪽한칸 가기
    }
    for (int i = 0; i < N1; i++) {//행 하나씩 ㄷ가기
        for (int j = 0; j < N2; j++) {// 행에있는 열을 하나씩 보기
            printf("%3d ", dalpangy[i][j]); //숫자 출력 3칸인 이유는 아까와 같이 1칸인 상태로 하면 배열이 정돈되지 않아서
        }
        printf("\n");
    }
    for (int i = 0; i < N1; i++) {//메모리 지우기 위해 반복
        free(dalpangy[i]);//가로 배열 마무리
    }
    free(dalpangy);//세로 배열 해제

    return 0;
}
