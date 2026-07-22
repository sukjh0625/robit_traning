#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>


int sizetype(int size, int type); //함수 선언

int main() {
    int size, type; // size랑 type이 나옴

    printf("write: "); 
    scanf("%d %d", &size, &type);


    sizetype(size, type); // 함수가 나옴

    return 0;
}
int sizetype(int size, int type) { // sizetype은 이런 함수다
    int mid = size / 2; // 중심을 기준으로 나눈다

    for (int i = 0; i < size; i++) {
        int spaces = 0; // 빈공간인 변수 만들고 0으로 지정
        int stars = 0; // 별 모양 변수 만들고 0으로 지정
        int k;         // 몇째줄인지 보여줌 그런데 위에서 나눈것 처럼 mid이용해서 중간 중심으로 보통 대칭되니까 설정

        if (i <= mid) {
            k = i;           // 중간 이상일때는 그냥 쓰고
        }
        else {
            k = size - 1 - i;  //중간 이하일때는 중심 대칭이니까 저렇게 표현
        }
        switch (type) {
        case 1: // 왼쪽 정렬 삼각형
            spaces = 0;
            stars = k + 1;
            break;
        case 2: // 오른쪽 정렬 삼각형
            spaces = mid - k;
            stars = k + 1;
            break;
        case 3: // 모래시계 모양
            spaces = k;
            stars = size - (2 * k);
            break;
        case 4: // 역삼각형 모양 // 얘는 대칭 아님
            spaces = mid - k;
            stars = k + 1;
            break;
        default: //잘못된 숫자가 들어왔을 때
            printf("wrong type\n");
            return 0; // 함수 종료
        }
        for (int j = 0; j < spaces; j++) {// 이부분이 왜 나오는지 살짝 혼동 되었지만 위 for문 안에 들어있기 때문에 줄 고려 안해줘도 됨
            printf(" ");
        }
        for (int j = 0; j < stars; j++) { // 별 
            printf("*");
        }
        printf("\n");
    }
    return 0;
}
