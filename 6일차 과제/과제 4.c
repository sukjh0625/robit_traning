//시간차이 기준을 초로 잡을지 분으로 잡을지 고민했지만 초로 가면 단위가 너무 작아져서 분으로 하기로 설정
// 윤년을 main함수 안에 넣기는 너무 복잡해서 밖으로 빼서 함수를 만듦
//에러처리도 함수로 빼서 판단

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct//date라는 구조체 만들기
{
    int year;
    int month;
    int day;
} Date;

typedef struct//시간을 나타내는 구조체
{
    int hour;
    int minute;
    int second;
} Time;

typedef struct//날짜와 시간을 나타내는 구조체
{
    Date date;
    Time time;
} DateTime;

int yunnyun(int year);//윤년과 아닌 년으로 나누는함수만들기
int lastday(int year, int month);// 입력한 연도와 월의 마지막 날짜를 보여주는 함수
int correct(DateTime value);//맞는지 확인하는 함수
int changeminute(DateTime value);// 날짜와시간을 분으로 바꾸는 함수

int main(void)
{
    DateTime date[2];//위에 말했던것처럼 날짜와 시간 저장 배열
    int totalMinute[2];// 두 날짜를 분으로 바꾼 값 저장
    int differenceMinute;//분차이
    int differenceSecond;//초차이
    int hour;//시간
    int minute;//분
    int second;//초
    int a;//배열 번호
    int wrong;// 오류인지 아닌지

    for (a = 0; a < 2; a++)//날짜와 시간 두번 입력
    {
        wrong = 0;//올바르지않다

        while (wrong == 0)//입력될때까지 반복
        {
            printf("write date and hour of %dth: ", a + 1);

            scanf("%d %d %d %d %d %d",
                &date[a].date.year,//연도
                &date[a].date.month,//월
                &date[a].date.day,//날짜
                &date[a].time.hour,//시간
                &date[a].time.minute,//분
                &date[a].time.second);//초 입력 받기

            if (correct(date[a]) == 1)//날짜와 시간이 옳은가
            {
                wrong = 1;//끝내기
            }
            else//아니면
            {
                printf("잘못된 날짜 또는 시간입니다.\n");
            }//예외처리
        }
        totalMinute[a] = changeminute(date[a]);// 날짜와 시간ㅇ르 분으로 바꾸기
    }

    if (totalMinute[0] < totalMinute[1] ||//첫번째 날짜가 두번쨰 날짜보다 빠른가
        (totalMinute[0] == totalMinute[1] &&//분이 같은가
            date[0].time.second <= date[1].time.second))//첫번쨰 날짜 초가 두번쨰 날짜 초보다작거나 같은가
    {
        differenceMinute = totalMinute[1] - totalMinute[0];// 두번쨰 날짜 분에서 첫번째 날짜 분빼기
        differenceSecond = date[1].time.second - date[0].time.second;//초빼기
    }
    else
    {
        differenceMinute = totalMinute[0] - totalMinute[1];
        differenceSecond = date[0].time.second - date[1].time.second;
    }

    if (differenceSecond < 0)//초 차이가 음수인가
    {
        differenceSecond = differenceSecond + 60;//1분에서 60초 빌리기
        differenceMinute--;//빌렸으니까 빼주기
    }
    hour = differenceMinute / 60;//시간을 분으로 나누기
    minute = differenceMinute % 60;//분을 60으로 나눈 나머지를 분으로 저장
    second = differenceSecond;//초차이는 초에 저장

    printf("%dhour %dminute %dsecond\n", hour, minute, second);

    return 0;
}

int yunnyun(int year)// 윤년 구별 함수
{
    if ((year % 4 == 0 && year % 100 != 0) ||//4의 배수면서 100의 배수인지 확인
        year % 400 == 0)
    {
        return 1;//윤년이면 1반환
    }

    return 0; //아니면 0변환
}

int lastday(int year, int month)//한달이 볓일인지 보는 함수
{
    int monthday[12] = {//월 날짜 저장 배열에
        31, 28, 31, 30, 31, 30,
        31, 31, 30, 31, 30, 31
    };

    if (month == 2 && yunnyun(year) == 1)//입력한 월이 2월이고 윤년인가
    {
        return 29;//2월 29일이니까 반환
    }

    return monthday[month - 1];
}

int correct(DateTime value)//오류확인 함수
{
    if (value.date.year < 1 || value.date.year > 4000)//연도 범위
    {
        return 0;
    }

    if (value.date.month < 1 || value.date.month > 12)
    {
        return 0;
    }
    if (value.date.day < 1 ||
        value.date.day > lastday(value.date.year, value.date.month))//본인 월보다 날이 많은지 확인
    {
        return 0;
    }
    if (value.time.hour < 0 || value.time.hour > 23)//시간 하루
    {
        return 0;
    }
    if (value.time.minute < 0 || value.time.minute > 59)//한시간 분
    {
        return 0;
    }
    if (value.time.second < 0 || value.time.second > 59)//분 초
    {
        return 0;
    }
    return 1;
}

int changeminute(DateTime value)//날짜와 시간을 분으로 바꾸는 함수
{
    int totalday = 0;//날짜 저장하는 곳
    int totalminute;// 시간을 분으로 바꾼 값 저장
    int a;//연도 번호 월번호

    for (a = 1; a < value.date.year; a++)
    {
        if (yunnyun(a) == 1)
        {
            totalday = totalday + 366;
        }
        else
        {
            totalday = totalday + 365;
        }
    }
    for (a = 1; a < value.date.month; a++)
    {
        totalday = totalday + lastday(value.date.year, a);
    }

    totalday = totalday + value.date.day - 1;
    totalminute = totalday * 24 * 60;
    totalminute = totalminute + value.time.hour * 60;
    totalminute = totalminute + value.time.minute;

    return totalminute;
}
