#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char html[500]; // 문자열 저장 배열
    char tag[30];//tag이름 저장 배열
    char** spain; //문자열 자리 저장

    int a = 0; // 몇번째문장을 읽는지
    int b;// 배열 위치 번호
    int c; //밑에 반복문에서 쓰임
    int top = -1; //가장 위 위치
    int space = 0; //들여쓰기 개수
    int close; //닫는 태그 먼지 저장
    int error = 0;

    spain = (char**)malloc(sizeof(char*) * 100); //100개저장할수있는 자리 만듦
     printf(" write HTML : ");
    scanf("%s", html);

    while (html[a] != '\0')//빈공간있을때까지 다 읽기
    {
        if (html[a] == '<')//<전까지 익기
        {close = 0; //다음문자 이동
            a++;
            if (html[a] == '/') //닫는 태그라면 저장후 건너뜀
            { close = 1; //아니면 하나 추가
                a++;}
              b = 0;//배열 첫칸부터 저장하기 위해 0으로 초기화
              
            while (html[a] != '>' && html[a] != '\0')//>나올때까지 읽기
            {
                if (b >= 29 || html[a] == '<')//태그 이름이 길면 오류
                { error = 1; //반복문 종료 끝냄
                    break;  }
                tag[b] = html[a]; //현재문자 b에 tag에 저장
                b++;//다음칸 이동
                a++;//다음문자 읽기
            }
            tag[b] = '\0';//문자열 끝 표시
            if (error == 1 || html[a] != '>' || tag[0] == '\0')// 에러났는가 끝이 >인가 태그이름이 없는가 검사
            {
                printf("wrong tag type\n");
                error = 1;
                break;
            }
            if (close == 0)// 여는태그면
            {
                if (top >= 99)//스택 많으면 끝남
                {
                    printf("too many tags\n");
                    error = 1;
                    break;
                }
                top++;//한칸 증가
                spain[top] = (char*)malloc(sizeof(char) * (b + 1));//태그이름만큼 자리 만들기
                
                while (tag[c] != '\0')//한글자씩 복사
                {
                    spain[top][c] = tag[c];
                    c++;
                }
                spain[top][c] = '\0'; //문자열에 저장

                for (c = 0; c < space; c++)//현재 빈공간확인
                    printf("    ");//출력

                printf("<%>s\n", tag);//태그 출력
                space++; //빈공간 하나 추가
            }
            else//닫는 태그면
            {if (top == -1)//스택이 비었는가?
                {
                    printf("no open tag\n");
                    error = 1;
                    break;
                }
                c = 0; //0으로 초기화

                while (spain[top][c] == tag[c] && //한글자씩 태그 비교
                    spain[top][c] != '\0')
                {
                    c++;
                }

                if (spain[top][c] != tag[c])// 끝난 위치의 문자가 다르면 태그가 다르다
                {
                    printf("wrong tag order\n");//태그 순서 다르다 출력
                    error = 1;
                    break;
                }

                space--;// 닫는태그니까 빈공간 하나 줄이기

                for (c = 0; c < space; c++) //줄어든 만큼 들여쓰기 하기
                    printf("    ");

                printf("</%s>\n", tag);//태그 출력

                free(spain[top]);//메모리 해제하기
                top--; //한칸 내리기
            }

            a++;//다음 문자 보기
        }
        else //현재 문자가<가 아니면
        {
            for (c = 0; c < space; c++)//현재 만큼 들여쓰기
                printf("    ");

            while (html[a] != '<' && html[a] != '\0') //다음 태그 전까지 문자 출력하기
            {
                printf("%c", html[a]);
                a++;//다음문자로 넘어가기
            }

            printf("\n");
        }
    }
    if (error == 0 && top != -1)// 태그가 남아있는지 보기
        printf("no close tag\n");

    while (top != -1)//남은 거 다 free로 지우기
    {
        free(spain[top]);
        top--;
    }

    free(spain);

    return 0;
}
