#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

typedef struct student// 학생 한명의 정보를 저장하는 구조체
{
    int number;// 학번
    char name[30];// 이름
    char country[30];// 국가
    char province[30];// 도
    char city[30];// 도시
    char district[30];// 구역
    char grade;// 성적
} student;

void clear(void);// 입력 값을 비우는 함수임
int inputint(char text[]);// 숫자 입력받는 함수
char inputgrade(void);// 성적을 입력받는 함수
void inputstudent(student* s);
void printstudent(student* s);
void printall(student list[], int count);
void add(student list[], int* count);
void removeStudent(student list[], int* count);
void find(student list[], int count);
void sort(student list[], int count);
void save(student list[], int count);
void load(student list[], int* count);

int main(void)
{
    student list[100];// 학생을 최대 100명까지 저장
    int count = 0;// 현재 저장된 학생 수
    int menu;// 선택한 메뉴 번호 저장

    while (1)// 종료를 선택하기 전까지 반복
    {
        printf("\n1.Add 2.Delete 3.Find 4.Sort\n");
        printf("5.Print 6.Save 7.Load 0.Exit\n");

        menu = inputint("Menu: ");

        if (menu == 1)
            add(list, &count);// 학생 수가 바뀌니까 count 주소를 넘긴다
        else if (menu == 2)
            removeStudent(list, &count);
        else if (menu == 3)
            find(list, count);
        else if (menu == 4)
            sort(list, count);
        else if (menu == 5)
            printall(list, count);
        else if (menu == 6)
            save(list, count);
        else if (menu == 7)
            load(list, &count);
        else if (menu == 0)
            break;
        else
            printf("Invalid menu.\n");
    }

    return 0;
}

void clear(void)
{
    scanf("%*[^\n]");// 엔터가 나오기 전까지 남은 문자 버리기
    scanf("%*c");// 마지막에 남은 줄바꿈 문자도 버림
}

int inputint(char text[])
{
    int number;

    while (1)
    {
        printf("%s", text);

        if (scanf("%d", &number) == 1 && number >= 0)// 정수 입력에 성공하고 0 이상인지 같이 확인한다
        {
            clear();
            return number;
        }

        printf("Invalid number.\n");
        clear();// 잘못 입력한 문자를 버리고 다시 입력받기
    }
}

char inputgrade(void)
{
    char grade;

    while (1)
    {
        printf("Grade: ");
        scanf(" %c", &grade);// 앞의 공백으로 남아있는 줄바꿈 무시
        clear();

        if (grade >= 'a' && grade <= 'z')
            grade -= 32;// 소문자로 입력하면 대문자로 바꾸기

        if (grade == 'A' || grade == 'B' ||
            grade == 'C' || grade == 'D' ||
            grade == 'F')
            return grade;

        printf("Invalid grade.\n");
    }
}

void inputstudent(student* s)
{
    do
    {
        s->number = inputint("Number: ");

        if (s->number == 0)
            printf("Number must be greater than zero.\n");

    } while (s->number == 0);// 학번은 0보다 커야함

    printf("Name: ");
    scanf("%29s", s->name);// 배열 크기를 넘지 않도록 29글자까지만 입력한다

    printf("Country: ");
    scanf("%29s", s->country);

    printf("Province: ");
    scanf("%29s", s->province);

    printf("City: ");
    scanf("%29s", s->city);

    printf("District: ");
    scanf("%29s", s->district);

    clear();

    s->grade = inputgrade();
}

void printstudent(student* s)
{
    printf("%d %s %s %s %s %s %c\n", // 학생 한명의 모든 정보를 한줄에 출력
        s->number, s->name, s->country,
        s->province, s->city, s->district,
        s->grade);
}

void printall(student list[], int count)
{
    int i;

    if (count == 0)
    {
        printf("No students.\n");
        return;
    }

    for (i = 0; i < count; i++)
        printstudent(&list[i]);// 배열의 학생을 하나씩 출력
}

void add(student list[], int* count)
{
    if (*count >= 100)// 배열에 더이상 저장할 공간이 없다면?
    {
        printf("Student list is full.\n");
        return;
    }

    inputstudent(&list[*count]);// 현재 마지막 위치에 새 학생 저장
    (*count)++;

    printf("Student added.\n");
}

void removeStudent(student list[], int* count)
{
    int number;
    int found[100];// 같은 학번을 가진 학생의 배열 위치를 저장
    int total = 0;// 찾은 학생 수
    int select;
    int i;
    int index;

    if (*count == 0)
    {
        printf("No students.\n");
        return;
    }

    number = inputint("Number: ");

    for (i = 0; i < *count; i++)
    {
        if (list[i].number == number)
        {
            found[total] = i;// 찾은 학생이 실제로 저장된 위치 기억
            printf("%d. ", total + 1);
            printstudent(&list[i]);
            total++;
        }
    }

    if (total == 0)
    {
        printf("Student not found.\n");
        return;
    }

    select = inputint("Select: ");

    if (select < 1 || select > total)
    {
        printf("Invalid selection.\n");
        return;
    }

    index = found[select - 1];// 사용자가 고른 학생의 실제 배열 위치이다

    for (i = index; i < *count - 1; i++) // 삭제된 자리를 뒤의 학생들로 한칸씩 채움
        list[i] = list[i + 1];

    (*count)--;

    printf("Student deleted.\n");
}

void find(student list[], int count)
{
    int menu;
    int number = 0;
    char text[30];
    char grade = 0;
    int found = 0;// 학생을 찾았는지 확인하는 변수
    int i;

    if (count == 0)
    {
        printf("No students.\n");
        return;
    }

    printf("1.Number 2.Country 3.Province\n");
    printf("4.City 5.District 6.Grade\n");

    menu = inputint("Search: ");

    if (menu == 1)
        number = inputint("Number: ");
    else if (menu >= 2 && menu <= 5)
    {
        printf("Text: ");
        scanf("%29s", text);
        clear();
    }
    else if (menu == 6)
        grade = inputgrade();
    else
    {
        printf("Invalid selection.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        if ((menu == 1 && list[i].number == number) ||//
        // 선택한 검색 기준에 맞는 학생인지 확인
            (menu == 2 && strcmp(list[i].country, text) == 0) ||
            (menu == 3 && strcmp(list[i].province, text) == 0) ||
            (menu == 4 && strcmp(list[i].city, text) == 0) ||
            (menu == 5 && strcmp(list[i].district, text) == 0) ||
            (menu == 6 && list[i].grade == grade))
        {
            printf("%s\n", list[i].name);
            found = 1;
        }
    }

    if (found == 0)
        printf("Student not found.\n");
}

void sort(student list[], int count)
{
    int menu;
    int i;
    int j;
    int change;// 두 학생의 위치를 바꿀지 저장
    student temp;// 학생 정보 전체를 잠깐 저장하는 변수

    if (count == 0)
    {
        printf("No students.\n");
        return;
    }

    printf("1.Number 2.Name 3.Country 4.Province\n");
    printf("5.City 6.District 7.Grade\n");

    menu = inputint("Sort: ");

    if (menu < 1 || menu > 7)
    {
        printf("Invalid selection.\n");
        return;
    }

    for (i = 0; i < count - 1; i++) // 정렬로 앞뒤 학생을 계속 비교// 어려웠던 부분
    {
        for (j = 0; j < count - 1 - i; j++)
        {
            change = 0;

            if (menu == 1)
                change = list[j].number > list[j + 1].number;
            else if (menu == 2)
                change = strcmp(list[j].name, list[j + 1].name) > 0;
            else if (menu == 3)
                change = strcmp(list[j].country, list[j + 1].country) > 0;
            else if (menu == 4)
                change = strcmp(list[j].province, list[j + 1].province) > 0;
            else if (menu == 5)
                change = strcmp(list[j].city, list[j + 1].city) > 0;
            else if (menu == 6)
                change = strcmp(list[j].district, list[j + 1].district) > 0;
            else
                change = list[j].grade > list[j + 1].grade;

            if (change)// 앞의 값이 더 크면 두 학생 위치 바꾸기
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }

    printall(list, count);// 정렬이 끝난 결과 바로 출력
}

void save(student list[], int count)
{
    FILE* file;
    int i;

    file = fopen("students.txt", "w");// 파일을 쓰기 모드로 열기

    if (file == NULL)
    {
        printf("File open error.\n");
        return;
    }

    for (i = 0; i < count; i++)
    {
        fprintf(file, "%d %s %s %s %s %s %c\n", // 학생 정보를 파일에 한명씩 저장
            list[i].number, list[i].name,
            list[i].country, list[i].province,
            list[i].city, list[i].district,
            list[i].grade);
    }

    fclose(file);// 파일 사용이 끝났으니까 닫기
    printf("File saved.\n");
}

void load(student list[], int* count)
{
    FILE* file;

    file = fopen("students.txt", "r");// 저장된 파일을 읽기 모드로 열기

    if (file == NULL)
    {
        printf("File open error.\n");
        return;
    }

    *count = 0;// 기존 학생 수를 초기화하고 파일 내용 다시 불러옴

   
    while (*count < 100 &&
        fscanf(file, "%d %29s %29s %29s %29s %29s %c", // 학생 정보 7개를 모두 제대로 읽었을때만 학생 수 증가
            &list[*count].number,
            list[*count].name,
            list[*count].country,
            list[*count].province,
            list[*count].city,
            list[*count].district,
            &list[*count].grade) == 7)
    {
        (*count)++;
    }

    fclose(file);
    printf("File loaded.\n");
}
