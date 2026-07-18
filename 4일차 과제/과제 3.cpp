#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int f(char str[]) { // main 함수에서 f함수로 문자열 가져옴
    char up1[] = "cdefgabC"; //올라가는 음 넣기
    char down1[] = "Cbagfedc"; //내려가는 음 넣기

    int up = 0;   // 올라가는 음을 세는 변수
    int down = 0; // 내림차순 음을 세는 변수

    for (int i = 0; i < 8; i++) {// 8개 하나씩 검사
        if (str[i] == up1[i]) { 
            up++; // 올라가는 음이라면 up에서 1 더하기
        }
        if (str[i] == down1[i]) {
            down++; //내려가는 음이라면 down에 1더하기
        }
    }
    if (up == 8) { // 만약만점이라면 결과 번호 1 리턴
        return 1;
    }
    else if (down == 8) { //만약 down만점이라면 결과 번호 2리턴
        return 2;
    }
    else {
        return 3; //아니라면 결과 번호 3리턴
    }
}

int main() {
    char str[100]; //문자열 배열 100개 만들기

    printf("write music\n");
    scanf("%s", str);  
 
    int result = f(str); // f 함수 가져오기

    printf("\nresult : "); 

    switch (result) {
    case 1:
        printf("ascending\n"); //1번 결과라면
        break;
    case 2:
        printf("descending\n"); //2번 결과라면
        break;
    case 3:
        printf("mixed\n"); //3번결과라면
        break;
    }

    return 0;
}
