// number shape 배열 선언하고 count이용해서 숫자 3번 입력 받는다, 범위 검사한후, for문 이용해서 칸을 채운다
// 포인터를 이용해서 배열의 첫번쨰 코드를 찾고 계속 반복시키면서 12개 원소 출력시키는 방법으로 짜봄

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int number[3];//숫자 3개
    int shape[3][4];//3X4배열
    int* p;//포인터
    int count = 0;
    int a;
    int b;
    int c;
    int wrong;

    while (count < 3)//3개 받을때까지 반복
    {wrong = 0;
        while (wrong == 0) //입력받을때까지 반복
        {
            if (count == 0)// 첫번쨰 숫자 입력받늕ㅇ
            {
                printf("input : ");
            }
            else
            {
                printf("next input : ");
            }

            scanf("%d", &number[count]);

            if (number[count] >= 0 && number[count] <= 9)// 입력한 숫자 범위 확인
            {
                wrong = 1;
            }
            else
            {
                printf("write only 0-9\n");
            }
        }
        c = 0;//첫번쨰 숫자 부터 보기
        for (a = 0; a < 3; a++)//3개 행 반복
        {
            for (b = 0; b < 4; b++)//행에 있는 4개 칸 중 정하기
            {
                shape[a][b] = number[c];//배열에 숫자 넣기

                c++;//다음 배열 번호로 이동

                if (c > count)// 마지막 번호로 넘어갔다면
                {
                    c = 0;//첫번째 글자로 넘어가기
                }
            }
        }
        p = &shape[0][0];//첫번째 자리로 가리키기
        printf("\n");
        for (a = 0; a < 12; a++)//12칸이니 12번 반복
        {
            printf("%d", *(p + a));

            if ((a + 1) % 4 == 0)//문자 4개 출력했는지 확인
            {
                printf("\n");//한줄 띄기
            }
        }
        printf("\n");
        count++;
    }
    return 0;
}
