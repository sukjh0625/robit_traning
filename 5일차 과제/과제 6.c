#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main() {
    int N1, N2;//변수 선언
    printf("write odd number n1 n2: ");
    if (scanf("%d %d", &N1, &N2) != 2) {//2개 아니면 오류
        printf("Error: Please write correct numbers.\n");
        return 1;
    }
    if (N1 <= 0 || N2 <= 0 || N1 % 2 == 0 || N2 % 2 == 0) {//홀수 아니면 오류
        printf("Error: Only write odd numbers bigger than 1.\n");
        return 1;
    }
    int** marmo = (int**)malloc(N1 * sizeof(int*));// 세로 배열 행개수만큼 동적할당
    for (int i = 0; i < N1; i++) { //가로배열 동적 할당 만들기
        marmo[i] = (int*)malloc(N2 * sizeof(int)); // 2차원 배열 만들어짐
        for (int j = 0; j < N2; j++) {
            marmo[i][j] = 0;// 0으로 채우기
        }
    }
    int cx = N1 / 2;// center x중심좌표
    int cy = N2 / 2;// 마무리
    int x = cx;//중앙값 세팅
    int y = cy;// 중앙값 세팅
    int num = 1; //1부터 시작
    marmo[x][y] = num++; //한개씩 추가
    int max_dist = N1 + N2; // 최대거리 설정
    for (int d = 1; d <= max_dist; d++) { //마름모로 추가해 나가는식
        x = cx + d; //한칸 내려간 곳을 위치로 잡기
        y = cy;// x y가 통상생각하는거랑 바껴있음

        if (x >= 0 && x < N1 && y >= 0 && y < N2 && marmo[x][y] == 0) { //0있는칸이라면 NUM채우기
            marmo[x][y] = num++;
        }
        for (int i = 0; i < d; i++) { //오른쪽 위 방향으로 이동
            x--; y++;
            if (x >= 0 && x < N1 && y >= 0 && y < N2 && marmo[x][y] == 0) marmo[x][y] = num++;
        }
        for (int i = 0; i < d; i++) { //왼쪽 위로 이동
            x--; y--;
            if (x >= 0 && x < N1 && y >= 0 && y < N2 && marmo[x][y] == 0) marmo[x][y] = num++;
        }
        for (int i = 0; i < d; i++) { //왼쪽아래로 이동
            x++; y--;
            if (x >= 0 && x < N1 && y >= 0 && y < N2 && marmo[x][y] == 0) marmo[x][y] = num++;
        }
        for (int i = 0; i < d; i++) { //오른쪽 아래로 이동
            x++; y++;
            if (x >= 0 && x < N1 && y >= 0 && y < N2 && marmo[x][y] == 0) marmo[x][y] = num++;
        }
    }
    for (int i = 0; i < N1; i++) { //오른쪽 아래로 이동
        for (int j = 0; j < N2; j++) {
            printf("%3d ", marmo[i][j]);
        }
        printf("\n");//출력 해주기
    }
    for (int i = 0; i < N1; i++) {//for문 이용해서 하나씩 제거해주기 free로
        free(marmo[i]);
    }
    free(marmo); //그리고 남은 통?같은 느낌의 세로 다 지우기
    return 0;
}
