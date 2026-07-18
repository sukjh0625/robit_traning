#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int S[21] = { 0 }; // 집합 만들기
    char command[20];  // 명령어 집합
    int x;             // 뒤에 붙는 수

    printf("CHOOSE calculation (1 <= x <= 20)\n");
    printf("add X\nremove X\ncheck X\ntoggle X\nall 0\nempty 0\n\n");

    while (1) {
        printf("input : ");
        scanf("%s %d", command, &x); // 문자열은 문자열대로 숫자는 숫자대로

        if (command[0] == 'a' && command[1] == 'd' && command[2] == 'd' && command[3] == '\0') {// add 인지 확인
            S[x] = 1; // x자리를 1로 만들기
        }
        else if (command[0] == 'r' && command[1] == 'e' && command[2] == 'm' && command[3] == 'o' && command[4] == 'v' && command[5] == 'e' && command[6] == '\0') {//remove인지 확인
            S[x] = 0; // x를 0으로 만들고 제거
        }
        else if (command[0] == 'c' && command[1] == 'h' && command[2] == 'e' && command[3] == 'c' && command[4] == 'k' && command[5] == '\0') {
            if (S[x] == 1) printf("1 "); // x가 들어있으면 1 출력 후 한 칸 띄기
            else printf("0 ");           // 아니면 0 출력 후 한 칸 띄기
        }
        else if (command[0] == 't' && command[1] == 'o' && command[2] == 'g' && command[3] == 'g' && command[4] == 'l' && command[5] == 'e' && command[6] == '\0') {
            if (S[x] == 1) S[x] = 0; // 집합에 있으면 0
            else S[x] = 1;           // 없다면 1
        }
        else if (command[0] == 'a' && command[1] == 'l' && command[2] == 'l' && command[3] == '\0') {
            for (int i = 1; i <= 20; i++) S[i] = 1; // 1부터 20까지 1로 채우기
        }
        else if (command[0] == 'e' && command[1] == 'm' && command[2] == 'p' && command[3] == 't' && command[4] == 'y' && command[5] == '\0') {
            for (int i = 1; i <= 20; i++) S[i] = 0; // 맞다면 0으로 채우기
        }

        printf("jiphap : { ");
        for (int i = 1; i <= 20; i++) {
            if (S[i] == 1) {
                printf("%d, ", i); 
            }
        }
        printf("}\n");
    }
    return 0;
}
