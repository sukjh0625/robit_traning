// 큐는 먼저 넣은 문자가 나오고 스택은 마지막에 넣은 문자가 먼저 나오는것을 이용해 회문 판단을 하려 했다
//과제 2와 과제 3을 합쳐서 만들수 있음
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct nodes// node 구조체 만들기
{
    char data;
    struct nodes* next;
} node;

typedef struct stack//스택 구조체
{
    node* top;// top만 있어도됨
    int size;
} stack;

typedef struct queue//큐 구조체
{
    node* front; //front rear 넣는곳 뺴는곳 둘다 있어야함
    node* rear;
    int size;
} queue;

void initstack(stack* s);// 스택 초기화 하는 함수 선언
void push(stack* s, char data);// 스택의 문자 하나를 넣는 함수 선언이다
char pop(stack* s);//스택의 맨위 문자를 꺼내고, 문자 반환 하는 함수

void initqueue(queue* q);//큐 초기화 함수
void enqueue(queue* q, char data);// 큐 맨뒤에 문자를 넣는 함수
char dequeue(queue* q);//맨 앞 문자 꺼내는 함수

int main(void)
{
    char word[100];// 99글자까지 저장하는 배열 \0이 한자리 있음
    int i;
    int result = 1;

    stack s;// 스택 변수
    queue q;// 큐변수

    initstack(&s);// 스택 주소 넘겨서 초기화
    initqueue(&q);//큐 부소념겨서 초기화

    printf("write char: ");
    fgets(word, 100, stdin);// 이부분이 중요했는데 fgets은 문자열을 입력받는 함수이다. scanf랑 비슷하지만 공백도 입력받을 수 있다

    i = 0;

    while (word[i] != '\0')//문자열 끝 만날때까지 반복
    {
        if (word[i] != ' ' && word[i] != '\n')// 공백과 줄바꿈인가?
        {
            push(&s, word[i]);//문자를 스택에 넣는다
            enqueue(&q, word[i]);//문자를 큐에 넣는다
        }

        i++;// 다음 문자 확인위해 인덱스 1증가
    }

    while (s.size > 0)//스택에 문자가 남아있는동안 반복, 스택과 큐에 같은 문자를 넣을거니까 스택만 검사
    {
        if (pop(&s) != dequeue(&q))// 스택에서 꺼낸 문자와 큐에서 꺼낸 문자 비교// pop은 뒤 dequeue는 앞
        {
            result = 0;
            break;
        }
    }

    if (result == 1)
        printf("Palindrome\n");
    else
        printf("not Palindrome\n");

    return 0;
}

void initstack(stack* s) // 과제 3과 똑같이 초기화 하는 함수
{
    s->top = NULL;
    s->size = 0;
}

void push(stack* s, char data)// 스택에 문자를 넣는 함수
{
    node* newnode;// 새로만드는 노드 주소 저장 포인터

    newnode = (node*)malloc(sizeof(node));//노드 하나 크기만큼 메모리할당

    if (newnode == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    newnode->data = data;// 새노드에 문자 저장
    newnode->next = s->top;// 새노드가 맨위 노드를 가리키게 함

    s->top = newnode;// 맨 위 노드를 새 노드로 바꾸기
    s->size++;// 크기 1증가
}

char pop(stack* s)// 스택 맨 위 문자를 삭제하고 반환하는 함수
{
    node* temp;
    char data;

    if (s->top == NULL)
    {
        printf("Stack is empty\n");
        return '\0';
    }

    temp = s->top;
    data = temp->data;

    s->top = temp->next;

    free(temp);

    s->size--;

    return data;
}

void initqueue(queue* q)
{
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}

void enqueue(queue* q, char data)// 큐 맨뒤에 문자를 넣는 함수// 앞 과제 반복
{
    node* newnode;

    newnode = (node*)malloc(sizeof(node));// 동적 할당 노드 하나크기만큼 메모리 할당

    if (newnode == NULL)
    {
        printf("Memory allocation error\n");
        return;
    }

    newnode->data = data;// 새 노드에 데이터 저장
    newnode->next = NULL;// 새 노드는 큐의 마지막 이니까 다음 노드 없음

    if (q->front == NULL)// 큐비어있다면
    {
        q->front = newnode;// 새노드가 맨 앞 노드
        q->rear = newnode;//동시에 맨 뒤 노드 하나밖에 없으니까
    }
    else
    {
        q->rear->next = newnode;// 아니라면 기존 마지막 노드 뒤에 새 노드 연결
        q->rear = newnode;// 큐의 마지막 노드 새 노드로 바꾸기
    }

    q->size++;// 크기 1 증가
}

char dequeue(queue* q)// 큐의 맨 앞 문자 삭제 반환
{
    node* temp;// 삭제할 앞 노드의 주소 저장 포인터
    char data;// 삭제할 노드의 문자 저장 변수

    if (q->front == NULL)
    {
        printf("Queue is empty\n");
        return '\0';
    }

    temp = q->front;// 맨 앞 노드의 주소 temp에 저장
    data = temp->data;// 삭제할 노드 문자 data에 저장

    q->front = temp->next;// front다음 노드로 옮기기

    if (q->front == NULL)// 빈경우 둘다 null로 바꾸기
        q->rear = NULL;

    free(temp);

    q->size--;

    return data;
}
