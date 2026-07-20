#include <stdio.h>
int main()

{ int badukpan[5][5] = { 0 };//5곱 5 만들고 0으로 채우기
int num = 1;//시작 숫자 1
for (int i = 0; i < 5; i++ )//가로줄 0부터 4까지 가기
{
    for (int j = 0;j < 5; j++)// 세로줄도 반복
    {
        if (i <= 2) //윗쪽
        {
            if (j >= i && j <= 4 - i)// 역삼각형 모양인가? 위에 5칸 그 밑 123칸 그 밑칸 1
            {
                badukpan[i][j] = num++; //한개 지나갈때마다 1씩 더하기
            }
        }   
        else {//아랫쪽
            if (j >= 4 - i && j <= i)
            {
                badukpan[i][j] = num++;
            }
        }
    }
}
for (int i = 0; i < 5; i++)// 한개씩 보기 5곱5
{
    for (int j = 0; j < 5; j++)//얘까지
    {
        printf("%3d", badukpan[i][j]); // 얘는 3칸씩 받아줘야 예쁘게 결과가 나온다
    }
    printf("\n");
}
return 0;}
