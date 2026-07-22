//문장 길이 계산, 길이만큼 동적할당, 임시배열에 옮김, 포인터 뒤로 이동하면서 거꾸로 출력, 문자 나온횟수 계산, 가장 많이 나온 문자 확인 순으로 짬

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char temp[100];//임시 문자 배열
    char* sentence;//동적할당 한거 가르키는포인터
    char* p;// 문자 하나씩 가리키는 포인터
    int count[128] = { 0 };//문자 몇번 나왔는지 저장하는 배열
    int length = 0;// 길이저장
    int a;
    int max = 0;// 가장 많은 등장 횟수
    char maxchar = '\0';// 가장많이 등장한 문자
    int wrong = 0;//오류

    while (wrong == 0)
    {
        printf("write sentence : ");
        scanf(" %[^\n]", temp);

        if (temp[0] != '\0')//첫번째 문자가 문자 끝이 아닌지 확인 아스키코드 사용
        {
            wrong = 1;
        }
        else
        {
            printf("한 글자 이상 입력하세요.\n");//예외처리
        }
    }

    while (temp[length] != '\0')//문자 처음부터 끝까지 반복
    {
        length++;//문자 하나 확인할때마다 길이 하나씩 증가
    }

    sentence = (char*)malloc(sizeof(char) * (length + 1));// 문장 길이 만큼 메모리 할당 근데 널문자 있어서 하나추가

    if (sentence == NULL)//동적 할당 실패했으면
    {
        printf("wrong memory\n");
        return 0;
    }

    for (a = 0; a <= length; a++)// temp에 있던 문자를 sentence에 복사하기 위해 반복
    {
        sentence[a] = temp[a];
    }

    p = sentence + length;//p를 문자열끝으로 이동

    printf("inverse : ");

    while (p > sentence)//포인터가 문자의 첫번쨰 위치보다 뒤에있으면 반복
    {
        p--;//포인터 한칸 앞으로 이동
        printf("%c", *p);
    }

    printf("\n");

    p = sentence;

    while (*p != '\0')// 문자열끝까지 하나씩 반복
    {
        if (*p != ' ')//공백이라면 계산에서 제외
        {
            count[(int)*p]++;//배열값 1씩 증가 시키기
        }

        p++;
    }

    for (a = 0; a < 128; a++)//0부터 127까지 확인
    {
        if (count[a] > max)//현재 문자 등장횟수가 기본최댓값보다 큰지 확인
        {
            max = count[a];
            maxchar = (char)a;
        }
    }

    printf("most word : %c\n", maxchar);

    free(sentence);

    return 0;
}
