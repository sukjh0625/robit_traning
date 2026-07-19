#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    char inputstr[100]; // 적은 전체 함수 배열
    char findstr[100];//찾는 함수 배열

    printf("write less than 99 <inputstr> : ");
    scanf("%99s", inputstr);

    printf("? str <findstr> : ");
    scanf("%99s", findstr);

    printf("%s location : ", findstr);

    for (int i = 0; inputstr[i] != '\0'; i++) { //전체 한글자씩 이동
        int j = 0; // 자리 번호 초기화

        while (findstr[j] != '\0' && inputstr[i + j] == findstr[j]) { //문자열이 안끝나고 일치하면 계속 비교
            j++;
        }
        if (findstr[j] == '\0') { // 성공경우
            printf("%d ", i + 1); // 1부터 시작하는 위치 출력
        }
    }
printf("\n");
    return 0;
}
