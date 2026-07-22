#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void print(int* hang, int* yull, int** pArr); //print 함수 선언 행 열 주소 받음, 2차원 배열 주소받음
void snail(int* hang, int* yull, int** pArr);// snail 함수 선언 배열안에 숫자 넣는 역할

int main(void)
{
    int** arr = NULL;// 이중포인터 선언 아직 아무주소도 저장되 있지 않음
    int hang, yull;
    int i;

    printf("yullnumber: ");
    scanf("%d", &yull);

    printf("hangnumber : ");
    scanf("%d", &hang);

    if (hang <= 0 || yull <= 0)// 행또는 열이 0이하인지 보기
    {
        printf("hang and yull number should be at least 1\n");
        return 0;
    }

    arr = (int**)malloc(sizeof(int*) * hang);//행 개수만큼 포인터 공간 동적 할당

    if (arr == NULL)//동적 할당 실패 하면
    {
        printf("wrong memory allocation\n");
        return 0;
    }

    for (i = 0; i < hang; i++)//행 개수 만큼 반복
    {
        arr[i] = (int*)malloc(sizeof(int) * yull);//열개수만큼 정수 공간 할당

        if (arr[i] == NULL)// 메모리 할당 실패 했다면
        {
            int j;

            printf("wrong memory allocation\n");

            for (j = 0; j < i; j++)//성공한 행만 반복
            {
                free(arr[j]);//행 부터 해제
            }

            free(arr);
            return 0;
        }
    }

    snail(&hang, &yull, arr);// snail함수 호출
    print(&hang, &yull, arr);

    for (i = 0; i < hang; i++)//행개수만큼 반복후 메모리 해제
    {
        free(arr[i]);
    }

    free(arr);

    return 0;
}

void snail(int* hang, int* yull, int** pArr)//snail 함수
{
    int top = 0;
    int bottom = *hang - 1;
    int left = 0;
    int right = *yull - 1;
    int number = 1;
    int i;

    while (top <= bottom && left <= right)// 위쪽경계가 아래쪽 경계안넘는다는 것은 자리가 있다는것
    {
        for (i = left; i <= right; i++)// 위쪽행 왼쪽부터 오른쪼까지 이동
        {
            pArr[top][i] = number;//number 저장//배운것처럼 i고정
            number++;// 다음 넣을 숫자 증가
        }

        top++;//한개씩 증가

        for (i = top; i <= bottom; i++)//오른쪽 열을 위에서 아래로 채우기
        {
            pArr[i][right] = number;
            number++;
        }

        right--;

        if (top <= bottom)
        {
            for (i = right; i >= left; i--)
            {
                pArr[bottom][i] = number;
                number++;
            }

            bottom--;
        }

        if (left <= right)
        {
            for (i = bottom; i >= top; i--)
            {
                pArr[i][left] = number;
                number++;
            }

            left++;
        }
    }
}

void print(int* hang, int* yull, int** pArr)// 배열 출력 함수
{
    int i, j;

    for (i = 0; i < *hang; i++)//0부터 마지막 행까지 반복
    {
        for (j = 0; j < *yull; j++)
        {
            printf("%4d", pArr[i][j]);//4칸 있어야 깔끔
        }

        printf("\n");
    }
}
