#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct item// 구조체 만들기
{
    char name[20];//이름 배열
    int money;//금액을 뜻하는 변수
} Item;//구조체 이름

int main()
{ Item* item;//구조체 배열을 뜻하는 포인터
    char findname[20];//마지막 물품이름 저장
    int count;// 개수
    int a;//몇번째 물품 배열번혼지 
    int b;//문자배열 번호
    int sum = 0;//합계
    int wrong = 0;//올바른지

    while (wrong == 0)//맞으면 멈춤
    {printf("how many items : ");
        scanf("%d", &count);

        if (count > 0)//물품개수가 한개 이상인가
        {
            wrong = 1;
        }
        else
        {
            printf("write more than one\n");
        }
    }
    item = (Item*)malloc(sizeof(Item) * count);//count개수만큼 물품을 저장할 메모리 동적 할당

    if (item == NULL)// 동적할당 실패 했는가
    {
        printf("wrong memory\n");
        return 0;
    }
    for (a = 0; a < count; a++)//count개 만큼 반복
    {
        printf("%dth item and price : ", a + 1);
        scanf("%s %d", item[a].name, &item[a].money);

        while (item[a].money < 0)//입력한 금액이 음수라면
        {
            printf("price should be atleast 0\n");
            printf("%dth name and price : ", a + 1);// 다시 입력하라말함
            scanf("%s %d", item[a].name, &item[a].money);
        }
    }
    printf("name : ");
    scanf("%s", findname);//find name에 저장

    for (a = 0; a < count; a++)//모든 물품 비교
    {
        b = 0;//첫번쨰 글자부터 시작

        while (item[a].name[b] == findname[b])//b번쨰 글자 찾을때까지 반복
        {
            if (item[a].name[b] == '\0')//모두 같은가?
            {
                sum = sum + item[a].money;//금액 합계에 더하기
                break;
            }

            b++;
        }
    }
    printf("%d\n", sum);

    free(item);
    return 0;
}
