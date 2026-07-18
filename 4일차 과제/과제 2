#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
    int arr[100]; // 숫자 저장할 배열 100개 만듦
    int n = 0;    // 총개수 변수

    printf("write number with space after writing write word: \n");
    printf("(ex: 14 2 10 5 1 3 17 7)\n\n");

    for (n = 0; scanf("%d", &arr[n]) == 1; n++) {} // 이 부분이 파이썬에서는 len을 썼던것 같은데 c프는 모르겠어서 LLM도움 받음 arr변수안에 하나씩 자연스럽게 채워지는것이라고 함

    printf("Before arrangement : ");
  
    for (int i = 0; i < n; i++) { //숫자 하나씩 쓰는 코드
        printf("%d ", arr[i]);
    }
    printf("\n");

    for (int step = 1; step < n; step++) {

        int last = n - step; // 이번 단계에서 가장 큰 숫자가 들어가야 할 맨 끝번호
        int max = 0;    // 일단 0번 방의 숫자가 가장 크다고 설정

        for (int i = 1; i <= last; i++) { //젤 큰 숫자 찾기
            if (arr[i] > arr[max]) {
                max = i; // 젤 큰 숫자 찾아서 자리 번호 바꾸기
            }
        }

        int imsi = arr[max];//imsi 임시 칸에 넣어 놓기 
            arr[max] = arr[last]; //가장 큰 숫자가 있던 자리에 있던 수를 임시 칸에 넣었기때문에 그자리에 맨 끝 자리 숫자 넣기 
        arr[last] = imsi;// 임시에있던 수 뒤에 넣기

        printf("After pass %d   : ", step); //한 단계씩 추력하기
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

  printf("result  : ");
    for (int i = 0; i < n; i++) { //최종결과
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
