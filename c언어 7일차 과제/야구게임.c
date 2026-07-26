#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define result_out 1// 변수를 그냥 변수로 쓰면 너무 코드가 복잡해질 것같아 숫자로 나타내는 방법을 사용해보았다.
#define result_single 2
#define result_double 3
#define result_home_run 4
#define result_strike 5
#define result_ball 6
#define result_strikeout 7
#define result_walk 8
#define result_miss 9

#define queue_capacity 10//큐에 최대 10개의 공 위치를 저장했다
#define stack_capacity 3//스트라이크 3개면 아웃이니까 3개 저장했다
#define list_capacity 200//경기결과 리스트 이다

typedef struct game// 게임상태를 저장하는 구조체 이다
{
    int strike;
    int ball;
    int out;
    int score;
    int base[3];// 홈을 넣어 볼까 했지만 딱히 필요가 없을것 같아서 제외하였따
} game;

typedef struct rule
{
    int hangdifference;// 투수의 투구 위치와 행의 차이를 보여준다
    int yulldifference;// 열의 차이를 보여준다
    int homerun;// 홈런
    int doublehit;//2루타
    int singlehit;//안타이다
} rule;

typedef struct queue// 투수가 던질 공의 위치를 큐로 나타내 보았다// 왜냐하면 투수가 공을 던지면 순서대로 타격데이터랑 비교해보아야하는데 그러면 선입 선추 방식의 큐가 잘 맞을거라고 생각했다
{
    int data[queue_capacity];//투구위치를 저장하는 배여이다
    int size;//배웠다 싶이 크기를 오류가 나지 않도록 적어주었다
} queue;

typedef struct stack// 스트라이크에는 스택을 사용했는데 count로도 표현해 볼수 있지만 그렇게 되면 초기화과정을 반복해야한다 그래서 스택으로 합쳐보았다
{
    int data[stack_capacity];// 스트라이크나 헛스윙 결과를 최대 3개 저장한다
    int top;
} stack;

typedef struct arraylist//전체 투구 결과를 배열로 저장하는 리스트를 만든다
{
    int data[list_capacity];
    int size;
} arraylist;

typedef struct node// 득점을 노드로 만들어보았다. 동적할당을 사용해보고 싶었는데 게임이 끝날때까지 모르는 점수를 노드로 표현해보면 사용할 수 있기 때문이다
{
    int result;// 타석에서의 결과이고
    int scoreafter;// 총점수를 저장한다
    struct node* next;
} node;

typedef struct linkedlist//
{
    node* head;
    node* tail;
    int size;
} linkedlist;

void clearinput(void);// 입력 버퍼에 남은 문자를 제거하는 함수이다
void printsplash(void);// 처음 시작 화면을 출력하는 함수
void waitkey(void);//사용자가 키를 누를 떄까지 기다리는 함수// 생각해보지 못한 함수 였는데 ai의 도움을 받았다
void setcolor(int color);// 보고서
void resetcolor(void);// 보고서
void printmenu(void);
void howtoplay(void);
void startgame(void);
int selectdifficulty(int* missrate, int* strikerate);// 이부분도 ai의 도움을 받았다 원래 따로따로 적었는데 포인터는 다시 매칭시키면 된다는 방법을 이용하여 2개를 한번에 적었다.
int aipitch(int selectcount[], int strikerate);// 알고리즘을 사용한 부분이다. 아래 설명
int choosepitch(int positions[], int size, int selectcount[]);
void chogigame(game* gameinfo);// 초기화하는 함수
void printzoneguide(void);// 게임 시작 전 존을 보여주는 함수 이다
void printgame(game* gameinfo);//현재 상황을 보여준다
void makehint(int pitch, int hint[3][3]);// 힌트 만드는 함수
void printhintboard(int hint[3][3]);//함수로 만들지 않았던 부분인데 계속 이상하게 출력이되어 함수로 만들었다
int inputswing(int hint[3][3]);//타격위치 입력받기
int randomresult(int homerun, int doublehit, int singlehit);//랜덤 결과 결정하기
int judgeswing(int pitch, int swing, rule rules[], int rulecount, int missrate);//타격결과 결정하기
void resetcount(game* gameinfo, stack* strikestack);// 볼과 스트라이크가 다음타자가 되면 초기화 되어야하므로 만든 함수이다
void moverunner(game* gameinfo, int result);// 주자이동 함수
void movewalkrunner(game* gameinfo);// 이부분은 위 함수에 추가했었는데 어떻게 짤지 모르겠어서 따로 뺀 부분이다
int processtake(game* gameinfo, int pitch, stack* strikestack);//스윙 안할때 
int processswing(game* gameinfo, int result, stack* strikestack);//스윙 했을때
void printresult(int result);
void chogiqueue(queue* pitchqueue);// 큐 초기화
int enqueue(queue* pitchqueue, int value);// 투구 위치 추가
int dequeue(queue* pitchqueue, int* value);// 꺼내는 함수
void chogistack(stack* strikestack);//스택을 초기화
int pushstack(stack* strikestack, int value);//
void clearstack(stack* strikestack);
void chogilist(arraylist* resultlist);
int addlist(arraylist* resultlist, int value);
void printsummary(arraylist* resultlist, linkedlist* scorelist, game* gameinfo);// 결과 출력
void chogilinkedlist(linkedlist* scorelist);
int addscoreevent(linkedlist* scorelist, int result, int scoreafter);
void freelinkedlist(linkedlist* scorelist);

int main(void)
{
    int menu;// 메뉴 번호를 저장하고
    int wrong;// 예외 처리이다
    void (*menufunctions[2])(void);//함수 포인터 배열을 이용해서 메뉴 번호 에따라 실행하게 했따

    srand((unsigned int)time(NULL));// 보고서에 적어둔 난수 초기화 이다

    menufunctions[0] = startgame;//메뉴의 번호와 어디로 가는지 연결해 보았따
    menufunctions[1] = howtoplay;

    printsplash();

    while (1)
    {
        printmenu();
        wrong = scanf("%d", &menu);

        if (wrong != 1)
        {
            printf("\ninvalid input. enter a number.\n\n");
            clearinput();
            continue;
        }

        clearinput();

        if (menu >= 1 && menu <= 2)
        {
            menufunctions[menu - 1]();// 함수 포인터를 이용해서  1번과 2번을 실행하게 한다. 이 부분은 포인터를 사용하면 좋을 것 같다 생각했고 ai가 어떤 식으로 사용하면 좋을 지 알려주어 적용해보았다
        }
        else if (menu == 3)// exit
        {
            printf("\ngood bye!\n");
            break;
        }
        else
        {
            printf("\nselect 1, 2, or 3.\n\n");
        }
    }

    return 0;
}

void clearinput(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
    }
}

void printsplash(void)
{
    printf("             baseball game\n");
    printf("\npress any key to continue...");
    waitkey();
    printf("\n\n");
}

void waitkey(void)
{
    _getch();// 아무키나 입력받는다 아무키나 입력하면 넘어가는 것을 만들어보고 싶었다. ai의 도움을 받았다. scanf getchar와 다르게 아무키나 입력받으면 된다
}

void setcolor(int color)// 보고서에 설명했다.
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WORD)color);
}

void resetcolor(void)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void printmenu(void)
{
    printf("========================================\n");
    printf("             baseball game\n");
    printf("========================================\n");
    printf("1. start game\n");
    printf("2. how to play\n");
    printf("3. exit\n");
    printf("\nselect menu: ");
}

void howtoplay(void)
{
    printf("\n              how to play\n\n\n");
    printf("a pitcher's throw is one of the nine blocks we give.\n\n");
    printf("you can choose one of the nine blocks\n");
    printf("or choose not to hit.\n\n");
    printf("the game ends when it's 3 outs.\n\n");
    printf("good luck!\n");
    printf("\npress enter to return to the menu...");
    getchar();
    printf("\n\n");
}

void startgame(void)
{
    game* gameinfo;// 구조체 포인터를 사용해서 게임상태를 저장해보았다. 포인터를 사용하니 게임상태를 바꾸기 편했다
    queue* pitchqueue;
    stack* strikestack;
    arraylist* resultlist;
    linkedlist* scorelist;

    rule rules[6] =// 가장 중요한 부분이었는데 타격했을때 어떻게 가는지 이다
    {
        {0, 0, 40, 30, 10},// 앞의 두개가 투구 위치를 비교하는거고 뒤에가 홈런 2루타 안타 확률이다// 이 코드는 정확한 위치인것이고
        {-1, 0, 10, 20, 10},// 이코드는 한칸위
        {1, 0, 0, 0, 70},// 이코드는 한칸 아래 이런방식이다
        {0, -1, 0, 30, 10},
        {0, 1, 0, 30, 10},
        {-1, -1, 10, 20, 10}
    };

    int hint[3][3];// 힌트
    int pitch;// 투구위치
    int swing;// 치는 위치
    int result;//탁격결과
    int oldscore;// 득점 전 점수
    int missrate;// 헛스윙 확률
    int strikerate;// 스트라이크 비율 알고리즘에 이용해보는 부분이었다
    int difficulty;// 선택한 난이도
    int selectcount[26] = { 0 };// 사용자가 번호를 몇번 선택했는지 저장한다
    int a;

    gameinfo = (game*)malloc(sizeof(game));// 게임 구조체 동적할당
    pitchqueue = (queue*)malloc(sizeof(queue));
    strikestack = (stack*)malloc(sizeof(stack));
    resultlist = (arraylist*)malloc(sizeof(arraylist));
    scorelist = (linkedlist*)malloc(sizeof(linkedlist));

    if (gameinfo == NULL || pitchqueue == NULL || strikestack == NULL ||// 메모리 할당 여부 예외처리
        resultlist == NULL || scorelist == NULL)
    {
        printf("memory allocation failed.\n");
        free(gameinfo);
        free(pitchqueue);
        free(strikestack);
        free(resultlist);
        free(scorelist);
        return;//끝내기
    }

    chogigame(gameinfo);// 초기화
    chogiqueue(pitchqueue);
    chogistack(strikestack);
    chogilist(resultlist);
    chogilinkedlist(scorelist);

    difficulty = selectdifficulty(&missrate, &strikerate);// 난이도 입력받기

    printzoneguide();// 존 출력
    printf("\npress any key to start the game...");
    waitkey();// 이부분이 아무키나 누르는것이다
    printf("\n");

    for (a = 0; a < queue_capacity; a++)// 큐크기만큼 반복한다
    {
        enqueue(pitchqueue, aipitch(selectcount, strikerate));// 투구위치들을 큐에 저장한다
    }

    printf("\n              game start\n");

    if (difficulty == 1)// 난이도 따라 검사
    {
        printf("              difficulty: easy\n\n");
    }
    else if (difficulty == 2)
    {
        printf("              difficulty: normal\n\n");
    }
    else
    {
        printf("              difficulty: hard\n\n");
    }

    while (gameinfo->out < 3)// 아웃이 3개 될때까지 반복
    {
        if (dequeue(pitchqueue, &pitch) == 0)// 큐에서 현재 투구를 가져온다// 이 개념이 잘 이해가 안되었는데 큐에 먼저 할당하고 투구를 가져오는 것이었다
        {
            printf("pitch queue error.\n");// 큐가 비었으면 예외처리
            break;
        }

        enqueue(pitchqueue, aipitch(selectcount, strikerate));// 다음 공을 큐에 넣는다
        makehint(pitch, hint);//현재 투구위치를 포함하는 힌트를 만든다
        printgame(gameinfo);//게임상태 추력
        printhintboard(hint);//힌트출력

        swing = inputswing(hint);// 어디치는지 입력받기
        oldscore = gameinfo->score;//현재점수 저장하기 구조체 포인터를 이용해 보았다

        if (swing == 0)// 스윙 했는지 검사
        {
            result = processtake(gameinfo, pitch, strikestack);// 결과 처리
        }
        else
        {
            selectcount[swing]++;// 선택한 번호 횟수를 1증가 시킨다 알고리즘에 쓰인다
            result = judgeswing(pitch, swing, rules, 6, missrate);// 결과 계산
            result = processswing(gameinfo, result, strikestack);// 실제 게임에 적용한다
        }

        addlist(resultlist, result);// 결과를 배열에 저장한다

        if (gameinfo->score > oldscore)// 점수가 증가했다면
        {
            addscoreevent(scorelist, result, gameinfo->score);// 득점정보를 연결리스트에 저장한다
        }

        printf("\npitch position: %d\n", pitch);
        printresult(result);
    }

    printf("\n----------------------------------------\n");
    printf("                game over\n");
    printf("----------------------------------------\n");
    printf("final score: %d\n", gameinfo->score);

    printsummary(resultlist, scorelist, gameinfo);

    freelinkedlist(scorelist);
    free(scorelist);
    free(resultlist);
    free(strikestack);
    free(pitchqueue);
    free(gameinfo);

    printf("\npress enter to return to the menu...");
    getchar();
    printf("\n\n");
}

int selectdifficulty(int* missrate, int* strikerate)// 난이도를 선택하는 함수이다
{
    int difficulty;
    int wrong;

    while (1)
    {
        printf("\nselect difficulty\n");
        printf("1. easy\n");
        printf("2. normal\n");
        printf("3. hard\n");
        printf("\nselect: ");

        wrong = scanf("%d", &difficulty);

        if (wrong != 1)
        {
            printf("invalid input. enter a number.\n");//숫자인지 확인하는 예외처리
            clearinput();
            continue;
        }

        clearinput();

        if (difficulty == 1)// 난이도에따라 헛스윙 비율과 스트라이크 비율을 다르게 만들었는데 그것을 적용해주는 부분이다
        {
            *missrate = 20;
            *strikerate = 80;
            return difficulty;
        }
        else if (difficulty == 2)
        {
            *missrate = 30;
            *strikerate = 65;
            return difficulty;
        }
        else if (difficulty == 3)
        {
            *missrate = 40;
            *strikerate = 50;
            return difficulty;
        }

        printf("select 1, 2, or 3.\n");
    }
}

int aipitch(int selectcount[], int strikerate)// 알고리즘부분이다
{
    int strikezone[9];
    {
        7, 8, 9,
            12, 13, 14,
            17, 18, 19
            ;// 이부분에 ;을 안썼고 왜 있어야 하는지 몰라서 ai를 통해 배웠다// 안 부분을 연산식 처럼 봐서 연산식을 끝내겠다 선언해야 하기 때문이다
    };

    int ballzone[16] =
    {
        1, 2, 3, 4, 5,
        6, 10,
        11, 15,
        16, 20,
        21, 22, 23, 24, 25
    };

    if (rand() % 100 < strikerate)//보고서
    {
        return choosepitch(strikezone, 9, selectcount);
    }

    return choosepitch(ballzone, 16, selectcount);
}

int choosepitch(int positions[], int size, int selectcount[])// 결국 투수가 최종위치를 정하는 함수이다
{
    int candidates[25];//후보위치중
    int minimum;// 가장 적게 선택된 횟수를 저장한다
    int count;// 후보 개수
    int a;

    if (rand() % 100 < 20)// 보고서
    {
        return positions[rand() % size];
    }

    minimum = selectcount[positions[0]];

    for (a = 1; a < size; a++)// 과제로 만들었던 최솟값을 젤 작은 값으로 바꿔가는 과정이다
    {
        if (selectcount[positions[a]] < minimum)
        {
            minimum = selectcount[positions[a]];
        }
    }

    count = 0;// 초기화 시킨다

    for (a = 0; a < size; a++)// 다시검사한다
    {
        if (selectcount[positions[a]] == minimum)
        {
            candidates[count] = positions[a];
            count++;//
        }
    }

    return candidates[rand() % count];// 후봇값중에 하나를 고른다
}

void chogigame(game* gameinfo)// 게임상태 초기화
{
    gameinfo->strike = 0;
    gameinfo->ball = 0;
    gameinfo->out = 0;
    gameinfo->score = 0;
    gameinfo->base[0] = 0;
    gameinfo->base[1] = 0;
    gameinfo->base[2] = 0;
}

void printzoneguide(void)// 색깔을 입히는 함수이다. 특별한 부분은 없고 반복문을 사용하여서 색깔을 입힌다 색깔 입히는 부분은 보고서에 적었다
{
    int position;
    int a;
    int b;

    position = 1;

    printf("\n----------------------------------------\n");
    printf("             zone guide\n");
    printf("-----------------------------------------\n");
    printf("yellow background = strike zone\n");
    printf("green background  = ball zone\n\n");

    for (a = 0; a < 5; a++)
    {
        for (b = 0; b < 5; b++)
        {
            if ((position >= 7 && position <= 9) ||
                (position >= 12 && position <= 14) ||
                (position >= 17 && position <= 19))
            {
                setcolor(BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            }
            else
            {
                setcolor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE |
                    FOREGROUND_INTENSITY | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
            }

            printf("  %02d  ", position);
            resetcolor();
            position++;
        }

        printf("\n");
    }
}

void printgame(game* gameinfo)// 현재 상황 함수이다
{
    printf("\n----------------------------------------\n");
    printf("score: %d\n", gameinfo->score);// 구조체 포인터 이용해서저장한다
    printf("strike: %d  ball: %d  out: %d\n",
        gameinfo->strike,
        gameinfo->ball,
        gameinfo->out);

    printf("\n");
    printf("              [2b]\n");

    if (gameinfo->base[1] == 1)
    {
        printf("              [x]\n");
    }
    else
    {
        printf("              [ ]\n");
    }

    printf("\n");
    printf("       [3b]           [1b]\n");

    if (gameinfo->base[2] == 1)
    {
        printf("       [x]");
    }
    else
    {
        printf("       [ ]");
    }

    if (gameinfo->base[0] == 1)
    {
        printf("           [x]\n");
    }
    else
    {
        printf("           [ ]\n");
    }

    printf("\n");
    printf("             [home]\n");
    printf("----------------------------------------\n");
}

void makehint(int pitch, int hint[3][3])// 힌트 생성 알고리즘이다
{
    int possiblehang[9];// pitch가 실제 투구 위치이다// 이 줄은 실제 투구 위치를 포함할 수 있는 행을 저장한다
    int possibleyull[9];// 열을 저장한다
    int pitchhang;// 실제 투구 행 저장한다
    int pitchyull;
    int starthang;// 최종선택된 행을 저장한다
    int startyull;
    int count;// 가능한 영역 개수를 저장한다
    int selected;// 선택된 배열의 번호를 저장한다
    int a;
    int b;

    pitchhang = (pitch - 1) / 5;//1부터 25까지의 투구위치를 0부터 4까지 행번호로 바꾼다 
    pitchyull = (pitch - 1) % 5;
    count = 0;

    for (a = 0; a <= 2; a++)// 시작행을 0 1 2 중에 검사한다 왜냐면 2행까지만 가능하기 때문이다
    {
        for (b = 0; b <= 2; b++)
        {
            if (pitchhang >= a && pitchhang <= a + 2 &&// 실제 공의 행이 시작행부터 시작행에 2더한거 사이인지 확인한다
                pitchyull >= b && pitchyull <= b + 2)
            {
                possiblehang[count] = a;// 맞다면 행 저장하고
                possibleyull[count] = b;
                count++;// 개수에 하나 늘린다
            }
        }
    }

    selected = rand() % count;// 보고서
    starthang = possiblehang[selected];
    startyull = possibleyull[selected];

    for (a = 0; a < 3; a++)
    {
        for (b = 0; b < 3; b++)
        {
            hint[a][b] = (starthang + a) * 5 + startyull + b + 1;
        }
    }
}

void printhintboard(int hint[3][3])// 힌트 보드 출력이다
{
    int position;
    int found;// 현재 출력할 위치가 힌트 9칸 안에 있는지 저장한다
    int a;// 행반복 변수
    int b;// 열반복 변수
    int c;// 행검사 변수
    int d;// 열검사 변수

    position = 1;

    printf("\n---------------------------------------\n");
    printf("                  hint\n");
    printf("----------------------------------------\n");
    printf("the pitch is inside the sky blue area.\n\n");

    for (a = 0; a < 5; a++)
    {
        for (b = 0; b < 5; b++)
        {
            found = 0;//0으로 초기화 한후

            for (c = 0; c < 3; c++)// 힌트배열의 세 행을 검사한다
            {
                for (d = 0; d < 3; d++)
                {
                    if (hint[c][d] == position)// 현재 출력할 위치와 힌트 배열에 저장된 위치가 같은지 확인한다
                    {
                        found = 1;
                    }
                }
            }

            if (found == 1)// 보고서
            {
                setcolor(BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }

            printf("  %02d  ", position);// 숫자를 두자리로 출력한다 그래야 사각형이 안삐뚫어진다. ai가 도움을 줬다

            if (found == 1)
            {
                resetcolor();
            }

            position++;
        }

        printf("\n");
    }
}

int inputswing(int hint[3][3])// 타격위치 입력받기
{
    int swing;
    int wrong;
    int found;
    int a;
    int b;

    while (1)
    {
        printf("\ntake = 0 | select position: ");
        wrong = scanf("%d", &swing);

        if (wrong != 1)
        {
            printf("invalid input. enter a number.\n");// 예외처리
            clearinput();
            continue;
        }

        clearinput();// 입력 값을 제거한다 getchar 사용부분이다

        if (swing == 0)// 사용자가 공을 치지 않았는지 본다
        {
            return swing;
        }

        found = 0;

        for (a = 0; a < 3; a++)// 힌트행 반복문이다
        {
            for (b = 0; b < 3; b++)// 열반복문
            {
                if (hint[a][b] == swing)// 힌트위치와 입력 위치가 같은지 확인한다
                {
                    found = 1;
                }
            }
        }

        if (found == 1)// 사용자가 선택한 번호가 힌트 안에 있었는지 확인한다
        {
            return swing;
        }

        printf("select 0 or one of the displayed positions.\n");// 예외처리
    }
}

int randomresult(int homerun, int doublehit, int singlehit)// 확률을 받아서 결과 하나를 결정하는 함수이다
{
    int random;// 보고서

    random = rand() % 100;

    if (random < homerun)
    {
        return result_home_run;
    }
    else if (random < homerun + doublehit)
    {
        return result_double;
    }
    else if (random < homerun + doublehit + singlehit)
    {
        return result_single;
    }

    return result_out;
}

int judgeswing(int pitch, int swing, rule rules[], int rulecount, int missrate)
{
    int pitchhang;// 투수 공의 행 번호
    int pitchyull;// 투수 공의 열 번호 
    int swinghang;// 친 공 행 번호
    int swingyull;// 친 공 열 번호
    int hangdifference;// 차이를 보여주는 곳
    int yulldifference;
    int random;
    int a;

    random = rand() % 100;

    if (random < missrate)// 헛스윙 확률 검사
    {
        return result_miss;
    }

    if (!((pitch >= 7 && pitch <= 9) ||// 공이 스트라이크 존인지 검사
        (pitch >= 12 && pitch <= 14) ||// 두번쨰줄
        (pitch >= 17 && pitch <= 19)))// 세번쨰줄
    {
        return randomresult(0, 0, 10);//볼을 친 경우의 확률이다
    }

    pitchhang = (pitch - 1) / 5;// 공위치를 행번호로 변환
    pitchyull = (pitch - 1) % 5;// 공위치를 열번호로 변환
    swinghang = (swing - 1) / 5;
    swingyull = (swing - 1) % 5;
    hangdifference = swinghang - pitchhang;// 행차이 열차이 계산
    yulldifference = swingyull - pitchyull;

    for (a = 0; a < rulecount; a++)// 규칙 배열을 처음부터 끝까지 검사해준다
    {
        if (rules[a].hangdifference == hangdifference &&// 행차이를 비교한다
            rules[a].yulldifference == yulldifference)// 열차이를 비교한다
        {
            return randomresult(rules[a].homerun,// 규칙에 이동해서 계산한다
                rules[a].doublehit,
                rules[a].singlehit);
        }
    }

    if (hangdifference == -1 && yulldifference == 1)// 왼쪽 위 대각선 규칙
    {
        return randomresult(10, 20, 10);
    }

    if (hangdifference == 1 &&// 아래 대각선 규칙
        (yulldifference == -1 || yulldifference == 1))
    {
        return randomresult(0, 20, 10);
    }

    return result_out;
}

void resetcount(game* gameinfo, stack* strikestack)
{
    gameinfo->strike = 0;
    gameinfo->ball = 0;
    clearstack(strikestack);
}

void moverunner(game* gameinfo, int result)//주자이동 알고리즘이다
{
    int runnercount;

    if (result == result_single)//구조체를 이용해서 게임 상황에 따라서 베이스를 옮기면 된다
    {
        gameinfo->score += gameinfo->base[2];
        gameinfo->base[2] = gameinfo->base[1];
        gameinfo->base[1] = gameinfo->base[0];
        gameinfo->base[0] = 1;
    }
    else if (result == result_double)// 타격결과를 확인해준다
    {
        gameinfo->score += gameinfo->base[2];// 점수 계산
        gameinfo->score += gameinfo->base[1];
        gameinfo->base[2] = gameinfo->base[0];
        gameinfo->base[1] = 1;
        gameinfo->base[0] = 0;
    }
    else if (result == result_home_run)
    {
        runnercount = gameinfo->base[0] + gameinfo->base[1] + gameinfo->base[2];
        gameinfo->score += runnercount + 1;
        gameinfo->base[0] = 0;
        gameinfo->base[1] = 0;
        gameinfo->base[2] = 0;
    }
}

void movewalkrunner(game* gameinfo)// 볼넷이 발생했을때 주자들을 옮기는 함수이다. 원래 위 함수에 추가시켜보려했는데 잘안되었다
{
    if (gameinfo->base[0] == 1)
    {
        if (gameinfo->base[1] == 1)
        {
            if (gameinfo->base[2] == 1)
            {
                gameinfo->score++;
            }

            gameinfo->base[2] = 1;
        }

        gameinfo->base[1] = 1;
    }

    gameinfo->base[0] = 1;
}

int processtake(game* gameinfo, int pitch, stack* strikestack)// 스윙하지 않을 떄 처리 이다
{
    if ((pitch >= 7 && pitch <= 9) ||// 스트라이크 존인지 확인한다
        (pitch >= 12 && pitch <= 14) ||
        (pitch >= 17 && pitch <= 19))
    {
        pushstack(strikestack, result_strike);
        gameinfo->strike = strikestack->top + 1;// 맞다면 스트라이크 카운트 추가

        if (gameinfo->strike == 3)
        {
            gameinfo->out++;
            resetcount(gameinfo, strikestack);// 스트라이크가 3번이라면 아웃
            return result_strikeout;
        }

        return result_strike;
    }

    gameinfo->ball++;// 볼넷인 경우 

    if (gameinfo->ball == 4)
    {
        movewalkrunner(gameinfo);
        resetcount(gameinfo, strikestack);
        return result_walk;// 볼넷 함수 가기
    }

    return result_ball;
}

int processswing(game* gameinfo, int result, stack* strikestack)// 스윙했을 때 판정
{
    if (result == result_miss)// 헛스윙 한다면
    {
        pushstack(strikestack, result_miss);
        gameinfo->strike = strikestack->top + 1;

        if (gameinfo->strike == 3)
        {
            gameinfo->out++;
            resetcount(gameinfo, strikestack);
            return result_strikeout;
        }

        return result_miss;
    }

    if (result == result_out)
    {
        gameinfo->out++;
    }
    else
    {
        moverunner(gameinfo, result);
    }

    resetcount(gameinfo, strikestack);
    return result;
}// 헛스윙 아웃 경우

void printresult(int result)// 결과를 보여주는 함수
{
    if (result == result_out)
    {
        printf("out!\n");
    }
    else if (result == result_single)
    {
        printf("single!\n");
    }
    else if (result == result_double)
    {
        printf("double!\n");
    }
    else if (result == result_home_run)
    {
        printf("home run!\n");
    }
    else if (result == result_strike)
    {
        printf("strike!\n");
    }
    else if (result == result_ball)
    {
        printf("ball!\n");
    }
    else if (result == result_strikeout)
    {
        printf("strikeout!\n");
    }
    else if (result == result_walk)
    {
        printf("walk!\n");
    }
    else if (result == result_miss)
    {
        printf("swing and miss!\n");
    }
}

void chogiqueue(queue* pitchqueue)// 큐를 쓴다
{
    pitchqueue->size = 0;// 큐 초기화
}

int enqueue(queue* pitchqueue, int value)
{
    if (pitchqueue->size >= queue_capacity)// 큐 가득찼는지 확인
    {
        return 0;
    }

    pitchqueue->data[pitchqueue->size] = value;// 맨뒤에 값추가
    pitchqueue->size++;

    return 1;
}

int dequeue(queue* pitchqueue, int* value)// 데이터 꺼내기 아까 ㄱ꺼낸 부분
{
    int a;

    if (pitchqueue->size == 0)
    {
        return 0;
    }

    *value = pitchqueue->data[0];// 맨앞 데이터 가져오기

    for (a = 0; a < pitchqueue->size - 1; a++)// 한칸씩 당기기
    {
        pitchqueue->data[a] = pitchqueue->data[a + 1];
    }

    pitchqueue->size--;

    return 1;
}

void chogistack(stack* strikestack)// 스택에 값저장
{
    strikestack->top = -1;// 빈스택은 항상 -1이다
}

int pushstack(stack* strikestack, int value)
{
    if (strikestack->top >= stack_capacity - 1)
    {
        return 0;
    }

    strikestack->top++;
    strikestack->data[strikestack->top] = value;

    return 1;
}

void clearstack(stack* strikestack)
{
    strikestack->top = -1;
}

void chogilist(arraylist* resultlist)
{
    resultlist->size = 0;
}

int addlist(arraylist* resultlist, int value)
{
    if (resultlist->size >= list_capacity)
    {
        return 0;
    }

    resultlist->data[resultlist->size] = value;
    resultlist->size++;

    return 1;
}

void printsummary(arraylist* resultlist, linkedlist* scorelist, game* gameinfo)
{
    int singlecount;
    int doublecount;
    int homeruncount;
    int walkcount;
    int a;

    singlecount = 0;
    doublecount = 0;
    homeruncount = 0;
    walkcount = 0;

    for (a = 0; a < resultlist->size; a++)
    {
        if (resultlist->data[a] == result_single)
        {
            singlecount++;
        }
        else if (resultlist->data[a] == result_double)
        {
            doublecount++;
        }
        else if (resultlist->data[a] == result_home_run)
        {
            homeruncount++;
        }
        else if (resultlist->data[a] == result_walk)
        {
            walkcount++;
        }
    }

    printf("\n--------------- summary ----------------\n");
    printf("total pitches: %d\n", resultlist->size);
    printf("single: %d\n", singlecount);
    printf("double: %d\n", doublecount);
    printf("home run: %d\n", homeruncount);
    printf("walk: %d\n", walkcount);
    printf("scoring plays: %d\n", scorelist->size);
    printf("final score: %d\n", gameinfo->score);
    printf("----------------------------------------\n");
}

void chogilinkedlist(linkedlist* scorelist)
{
    scorelist->head = NULL;
    scorelist->tail = NULL;
    scorelist->size = 0;
}

int addscoreevent(linkedlist* scorelist, int result, int scoreafter)
{
    node* newnode;

    newnode = (node*)malloc(sizeof(node));

    if (newnode == NULL)
    {
        return 0;
    }

    newnode->result = result;
    newnode->scoreafter = scoreafter;
    newnode->next = NULL;

    if (scorelist->head == NULL)
    {
        scorelist->head = newnode;
        scorelist->tail = newnode;
    }
    else
    {
        scorelist->tail->next = newnode;
        scorelist->tail = newnode;
    }

    scorelist->size++;
    return 1;
}

void freelinkedlist(linkedlist* scorelist)
{
    node* current;
    node* nextnode;

    current = scorelist->head;

    while (current != NULL)
    {
        nextnode = current->next;
        free(current);
        current = nextnode;
    }

    scorelist->head = NULL;
    scorelist->tail = NULL;
    scorelist->size = 0;
}
