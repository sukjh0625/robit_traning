//노드를 보여주는 구조체 만들고, 관리해주는 스택 구조체 만들기
//스택은 LIFO구조 마지막 데이터가 젤 먼저 나옴

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct nodes//구조체 만들기
{
    int data;// 실제 데이터 저장 변수
    struct nodes* next;//다음 노드의 주소를 저장하는 포인터, 연결
} node;

typedef struct stack//스택을 관리하는 구조체 만들기
{
    node* top;// 가장 위의 노드의 주소 저장
    int size;// 노드 개수 저장// size_t size 로 바꿀 수 있다
} stack;

void initstack(stack* s); //스택을 초기화하는 함수 스택//어제 배웠던 구조체를 보내는 것이 아니라 주소를 보낸다
void push(stack* s, int data);// 스택에 정수를 추가하는 함수선언
void pop(stack* s);
void top(stack* s);
void size(stack* s);
void empty(stack* s);
void printstack(stack* s);

int main(void)
{
    stack s;// 자료형 변수s를 만든다

    initstack(&s);//주소를 넘겨서 s의 값이 바뀔수 있도록 한다

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printstack(&s);// 모든값을 출력

    top(&s);// 스택은 LIFO구조이기 때문에 나중에 들어간 것이 먼저 나온다

    pop(&s);

    printstack(&s);

    size(&s);

    empty(&s);

    return 0;
}

void initstack(stack* s)
{
    s->top = NULL;//구조체이기때문에 ->을 쓰고 스택의 노드가 아직 없다 함//(*s).top이랑 똑같은 말
    s->size = 0;
}

void push(stack* s, int data)
{
    node* newnode;// 새로만들 노드를 가리킬 포인터 선언

    newnode = (node*)malloc(sizeof(node));//노드 한개만큼의 메모리 할당// 주소 newnode에 저장

    newnode->data = data;//새 노드의 데이터에 전달받은값 저장
    newnode->next = s->top;//새 노드가 원래 맨위 노드 가리키게 한다

    s->top = newnode;//스택의 맨위를 새노드로 바꾼다
    s->size++;//스택의 크기를 1증가시킨다
}

void pop(stack* s)
{
    node* temp;//노드의 주소를 잠깐 저장할 포인터

    if (s->top == NULL)//스택이 비었는지 확인
    {
        printf("stack is empty\n");
        return;
    }

    temp = s->top;//맨위 노드 주소 temp에 저장//free하기위해 보관

    printf("pop : %d\n", temp->data);

    s->top = temp->next;// 스택의 맨위를 다음노드로 바꾼다

    free(temp);

    s->size--; //스택 크기 감소
}

void top(stack* s)// 맨위 값 확인 하는 함수
{
    if (s->top == NULL)//스택이 비었는지 확인
    {
        printf("stack is empty\n");
        return;
    }

    printf("top : %d\n", s->top->data);//스택안에 있는 top을 가져오고 top은 node 포인터이기때문에 한번더 가져올 수 있다
}

void size(stack* s)
{
    printf("size : %d\n", s->size);
}

void empty(stack* s)
{
    if (s->top == NULL)
        printf("true\n");
    else
        printf("false\n");
}

void printstack(stack* s)
{
    node* cur;//노드를 하나씩 따라가면서 보는 포인터

    if (s->top == NULL)
    {
        printf("stack is empty\n");
        return;
    }

    cur = s->top;//맨 위 노드부터 가리키게 하기

    printf("stack\n");

    while (cur != NULL)//cur가 노드를 가리키는 동안만 반복
    {
        printf("%d\n", cur->data);
        cur = cur->next;//cur 를 다음 노드로 움직이게 하기
    }
}
