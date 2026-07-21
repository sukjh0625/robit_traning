#include <stdio.h>
#include <stdlib.h>

typedef struct node// data정수저장 next다음노드주소 저장
{
    int data;
    struct node* next;
} Node;

typedef struct linkedList//리스트 전체
{
    Node* head;//처음 노드주소
    Node* tail;//마지막 노드주소
    int size;// 노드개수
} LinkedList;

void init_list(LinkedList* list);//함수 선언

int insert(LinkedList* list, int mode, int target, int data);
int insert_back(LinkedList* list, int data);
int insert_first(LinkedList* list, int data);

int delete(LinkedList* list, int mode, int target);
int delete_first(LinkedList* list);
int delete_back(LinkedList* list);

int get_entry(LinkedList* list, int mode, int target);//반환값있는 int성공1 실패0 
int get_length(LinkedList* list);

void print_list(LinkedList* list);//반환 없음
void reverse(LinkedList* list);

int main(void)
{
    LinkedList list;//연결리스트 변수 만듦

    init_list(&list);//리스트 초기화

    insert_first(&list, 10);//리스트 만들기//맨앞에 10넣기
    insert_back(&list, 20);//뒤에 20넣기
    insert_back(&list, 30);//맨뒤에 30넣기

    insert(&list, 2, 1, 25);//index 기준, 20뒤에 25넣기
    insert(&list, 1, 20, 22);//data기준, 20뒤에 22 넣기

    print_list(&list);//리스트 출력

    printf("%d\n", get_entry(&list, 1, 22));//data22인 index출력
    printf("%d\n", get_entry(&list, 2, 3));//data
    printf("%d\n", get_length(&list)); //노드 개수 출력

    delete(&list, 1, 22);//data
    delete(&list, 2, 2);//index

    delete_first(&list);//처음거 삭제
    delete_back(&list);//마지막 삭제

    print_list(&list);//리스트 출력

    reverse(&list);//바꾸기

    print_list(&list);

    while (list.head != NULL)
    {
        delete_first(&list);//동적 메모리 해제
    }

    return 0;
}

void init_list(LinkedList* list)
{
    list->head = NULL;//첫번쨰 노드 없음
    list->tail = NULL;//마지막 노드도 없음
    list->size = 0;//사이즈 0
}

int insert_first(LinkedList* list, int data)
{
    Node* newNode;// 노드 주소 저장 포인터

    newNode = (Node*)malloc(sizeof(Node));// 노드 하나크기만큼 동적 할당

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->data = data;// 새노드의 data에 값 저장
    newNode->next = list->head;//첫번쨰 노드 가리키게하기 새 노드가

    list->head = newNode;// 새노드 첫번쨰 노드로 만들기

    if (list->tail == NULL)
    {
        list->tail = newNode;
    }

    list->size++;

    return 1;
}

int insert_back(LinkedList* list, int data)
{
    Node* newNode;

    newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL)
    {
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->next = newNode;
        list->tail = newNode;
    }

    list->size++;

    return 1;
}

int insert(LinkedList* list, int mode, int target, int data)
{
    Node* current;
    Node* newNode;
    int index;

    if (list->head == NULL)
    {
        return 0;
    }

    current = list->head;

    if (mode == 1)//데이터있는 노드찾기
    {
        while (current != NULL && current->data != target)
        {
            current = current->next;
        }
    }
    else if (mode == 2)//index로 보기
    {
        if (target < 0 || target >= list->size)
        {
            return 0;
        }

        for (index = 0; index < target; index++)
        {
            current = current->next;
        }
    }
    else
    {
        return 0;
    }

    if (current == NULL)
    {
        return 0;
    }

    newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        return 0;
    }

    newNode->data = data;
    newNode->next = current->next;
    current->next = newNode;

    if (current == list->tail)
    {
        list->tail = newNode;
    }

    list->size++;

    return 1;
}

int delete_first(LinkedList* list)
{
    Node* remove;// 삭제할 노드 주소를 임시로 저장하는 포인터

    if (list->head == NULL)
    {
        return 0;
    }

    remove = list->head;//첫번째 노드 주소 remove에 저장
    list->head = list->head->next;//두먼쨰 노드를 새로운 첫번째 노드로 만들기

    free(remove);//메모리 해제

    list->size--;//노드 개수 줄이기

    if (list->head == NULL)
    {
        list->tail = NULL;
    }

    return 1;
}

int delete_back(LinkedList* list)
{
    Node* current;

    if (list->head == NULL)
    {
        return 0;
    }

    if (list->head == list->tail)
    {
        return delete_first(list);
    }

    current = list->head;

    while (current->next != list->tail)
    {
        current = current->next;
    }

    free(list->tail);

    list->tail = current;
    list->tail->next = NULL;

    list->size--;

    return 1;
}

int delete(LinkedList* list, int mode, int target)
{
    Node* current;
    Node* previous;
    int index;

    if (list->head == NULL)
    {
        return 0;
    }

    current = list->head;
    previous = NULL;

    if (mode == 1)
    {
        while (current != NULL && current->data != target)
        {
            previous = current;
            current = current->next;
        }
    }
    else if (mode == 2)
    {
        if (target < 0 || target >= list->size)
        {
            return 0;
        }

        for (index = 0; index < target; index++)
        {
            previous = current;
            current = current->next;
        }
    }
    else
    {
        return 0;
    }

    if (current == NULL)
    {
        return 0;
    }

    if (current == list->head)
    {
        return delete_first(list);
    }

    if (current == list->tail)
    {
        return delete_back(list);
    }

    previous->next = current->next;

    free(current);

    list->size--;

    return 1;
}

int get_entry(LinkedList* list, int mode, int target)
{
    Node* current;
    int index;

    if (list->head == NULL)
    {
        return -1;
    }

    current = list->head;//첫번쨰 노드 부터 탐색

    if (mode == 1)//data받아서 index찾기
    {
        index = 0;

        while (current != NULL)//노드가 있으면 반복
        {
            if (current->data == target)//현재랑 찾는거 비교
            {
                return index;
            }

            current = current->next;//다음노드로 이동
            index++;
        }
    }
    else if (mode == 2)
    {
        if (target < 0 || target >= list->size)
        {
            return -1;
        }

        for (index = 0; index < target; index++)
        {
            current = current->next;
        }

        return current->data;
    }

    return -1;
}

int get_length(LinkedList* list)
{
    return list->size;//노드개수 반환
}

void print_list(LinkedList* list)
{
    Node* current;

    current = list->head;

    while (current != NULL)
    {
        printf("%d", current->data);

        if (current->next != NULL)
        {
            printf(" -> ");
        }

        current = current->next;
    }

    printf("\n");
}

void reverse(LinkedList* list)
{
    Node* previous;//현재 노드 앞쪽을 에 있는 노드 가리키기
    Node* current;//바꿀노드 가리키기
    Node* nextNode;//// 다음 노드 잠시 보관

    if (list->head == NULL || list->head == list->tail)
    {
        return;
    }

    previous = NULL;// 마지막 노드가 첫번쨰 노드가 되니까 다음은 null이어야한다
    current = list->head;// 첫번째부터 방향 바꾸기

    list->tail = list->head;//첫번째 노드는 마지막 노드가 되니까 tail

    while (current != NULL)
    {
        nextNode = current->next;
        current->next = previous;

        previous = current;
        current = nextNode;
    }

    list->head = previous;
}
