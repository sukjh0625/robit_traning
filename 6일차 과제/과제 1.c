#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct student//구조체 만들기
{
    int grade; //학년 정수형
    float score; // 성적 실수형
    char name[20]; //이름 문자열
} Student;//구조체 이름

int main(void) 
{Student student[5]; //배열
    Student imsi;// 정보 바꿀때 임시 구조체 변수
    int a; //밑 반복문에서 쓰는 변수
    int b; // 학생 비교해주는 변수
    int c; // 이름 비교할때 쓰는 위치 번호
    int change; //순서 바꿀지 저장하는 변수
    int wrong; //오류뜨나 보는 변수
    int wrongname;//이름 비교 됬는지 보는 변수
    for (a = 0; a < 5; a++) //5명 다 보기
    {
        wrong = 0;//일단 올바르지 않다
        while (wrong == 0) //만약 올바르지 않다면
        {
            printf("%dth student's grade: ", a + 1); 
            scanf("%d", &student[a].grade);
            if (student[a].grade >= 1 && student[a].grade <= 4)// 1학년이상인지 4학년 이하인지 확인
            {
                wrong = 1;//맞으면 if문끝내기
            }
            else
            {
                printf("only write 1-4.\n");//아니면 오류
            }
        }
        wrong = 0;//일단 틀린게 기본
        while (wrong == 0)
        {
            printf("write %dth score : ", a + 1);
            scanf("%f", &student[a].score);

            if (student[a].score >= 0.0 && student[a].score <= 4.5)//점수가 0점부터 4.5까지인지 확인
            {
                wrong = 1;
            }
            else
            {
                printf("only grade 0.0-4.5\n");
            }
        }
        printf("write %dth name: ", a + 1);
        scanf("%s", student[a].name);
    }
    for (a = 0; a < 4; a++) //a 4번반복
    {
        for (b = 0; b < 4 - a; b++)//서로 붙어이는 학생 비교
        {
            change = 0;

            if (student[b].grade > student[b + 1].grade)// 앞학생이 뒤 학생보다 큰가?
            {
                change = 1;//그럼 순서 바꾸기
            }
            else if (student[b].grade == student[b + 1].grade)//같다면 성적 보기
            {
                if (student[b].score > student[b + 1].score)// 앞학생 성적이 크다면?
                {
                    change = 1;//바꾸기
                }
                else if (student[b].score == student[b + 1].score)//성적도 같다면 이름비교
                {
                    c = 0;
                    wrongname = 0;//아직 이름비교를 안함

                    while (wrongname == 0)//이름 비교가 끝날때까지 반복
                    {
                        if (student[b].name[c] > student[b + 1].name[c])//앞학생문자가 뒤학생 문자보다 뒤에있다면 
                        {
                            change = 1;//바꾸기
                            wrongname = 1;//틀림
                        }
                        else if (student[b].name[c] < student[b + 1].name[c])
                        {
                            wrongname = 1;//아니면 끝내기
                        }
                        else if (student[b].name[c] == '\0')
                        {
                            wrongname = 1;//같다면 끝내기,얘는 전체 비교했을때
                        }
                        else
                        {
                            c++;//아니라면 다음 문자로이동
                        }
                    }
                }
            }
            if (change == 1)//순서를 바꿔야한다면
            {
                imsi = student[b];//임시칸에 넣고
                student[b] = student[b + 1];//원래칸에 뒤칸걸 옮기고
                student[b + 1] = imsi; //임시칸에 있던거를 옮길 자리에 옮김
            }
        }
    }

    printf("\nresult\n");

    for (a = 0; a < 5; a++)
    {
        printf("%d %.1f %s\n",
            student[a].grade,//학년 점수 이름 추력
            student[a].score,
            student[a].name);
    }

    return 0;
}
