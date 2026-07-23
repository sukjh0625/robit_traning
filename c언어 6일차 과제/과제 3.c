//queue가 쓰이는데 얘는 FIFO구조 먼저들어간 데이터가 먼저 나온다 
//즉 데이터 추가되는곳과 삭제되는곳이 다름 rear 넣는 곳, front 나가는곳
// 기본 틀은 과제 2와 동일


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct nodes// 구조체 만들기 노드만들기
{
    int data;
    struct nodes* next;
} node;

typedef struct queue// 큐관리하는 구조체 만들기
{
    node* front;// 맨 앞 노드 주소 저장
    node* rear;//맨 뒤 노드주소 저장
    int size;// 노드 개수 저장
} queue;

void initqueue(queue* q);// 함수 선언
void enqueue(queue* q, int data);
void dequeue(queue* q);
void front(queue* q);
void rear(queue* q);
void size(queue* q);
void empty(queue* q);
void printqueue(queue* q);

int main(void)
{
    queue q;// 큐 자료형의 변수 q만들기

    initqueue(&q);

    enqueue(&q, 10);// 데이터를 추가
    enqueue(&q, 20);
    enqueue(&q, 30);

    printqueue(&q);

    front(&q);// 과제 2는 top으로 모든것을 끝냈다면 큐는 front,rear을 씀
    rear(&q);

    dequeue(&q);// 데이터를 꺼내기

    printqueue(&q);

    size(&q);

    empty(&q);

    return 0;
}

void initqueue(queue* q)
{
    q->front = NULL;// 다 비우고
    q->rear = NULL;
    q->size = 0;// 크기도 0으로 만들기
}

void enqueue(queue* q, int data)// 새 데이터를 넣는 함수
{
    node* newnode;// 새 노드 주소 저장할 포인터 만들기

    newnode = (node*)malloc(sizeof(node));// 메모리 동적 할당

    newnode->data = data;//데이터에 전달받은 값 저장
    newnode->next = NULL;// 새노드는 큐의 마지막에 들어가서 다음 노드가 없다

    if (q->front == NULL)
    {
        q->front = newnode;//q가 비어있었다면 새 노드가 맨 앞 노드가 된다
        q->rear = newnode;// 노드가 하나뿐이므로 새 노드는 맨 뒤 노드임
    }
    else
    {
        q->rear->next = newnode;// 아니라면 기존 마지막 노드의 next가 새 노드를 가리키게 함
        q->rear = newnode;//큐의 마지막 노드를 새 노드로 바꿈
    }

    q->size++;// 큐 크기 하나 증가
}

void dequeue(queue* q)// 큐의 맨 앞 노드를 삭제하는 함수
{
    node* temp;// 삭제할 노드의 주소를 잠시 저장할 포인터

    if (q->front == NULL)// 큐가 비어있는지 확인
    {
        printf("queue is empty\n");
        return;
    }

    temp = q->front;// free로 삭제하기 위해 저장

    printf("dequeue : %d\n", temp->data);

    q->front = temp->next;front //다음 노드로 이동

    if (q->front == NULL)
    {
        q->rear = NULL;//q가 완전히 비면 rear null로 바꾸기
    }

    free(temp);

    q->size--;
}

void front(queue* q)
{
    if (q->front == NULL)
    {
        printf("queue is empty\n");
        return;
    }

    printf("front : %d\n", q->front->data);
}

void rear(queue* q)
{
    if (q->rear == NULL)
    {
        printf("queue is empty\n");
        return;
    }

    printf("rear : %d\n", q->rear->data);
}

void size(queue* q)
{
    printf("size : %d\n", q->size);
}

void empty(queue* q)
{
    if (q->front == NULL)
        printf("true\n");
    else
        printf("false\n");
}

void printqueue(queue* q)
{
    node* cur;

    if (q->front == NULL)
    {
        printf("queue is empty\n");
        return;
    }

    cur = q->front;

    printf("queue\n");

    while (cur != NULL)
    {
        printf("%d\n", cur->data);
        cur = cur->next;
    }
}
