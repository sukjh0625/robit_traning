  #define _CRT_SECURE_NO_WARNINGS 
  #include <stdio.h>
  #include <stdlib.h> //동적 할당 쓰려면 필요
  int main() 
  {   int arr[100][100]; //임시로 만들기
      int hang = 0; //초기값 정하기
      int yull = 0;

      int current_yull = 0; //현재 행에서 몇번쨰 열인가?
      int num;// 사용자가 적은 것 임시 저장
      char ch; //스페이스바를 눌렀는지 엔터를 눌렀는지 확인하는 변수 이게 따로 필요한지 몰라서 어려웠던 부분

      printf("write number\n"); 
      printf("if you end you should write -119:\n");
  
      while (1) //끝내기 전까지 반복해라
      {if (scanf("%d", &num) != 1) break; //1개 숫자 읽기 안되면 끝내기
          if (num == -119) { //어려웠던 부분 -119를 마지막 열에 넣는다면 그 줄은 삭제 될거니까 그렇지 않게 해주기
              if (current_yull > 0) { //
                  hang++; 
              }
              break;
          }
          arr[hang][current_yull] = num; //현재 행과 열에 사용자가 적은 숫자 저장
          current_yull++; //칸채웠으니 한칸 오른쪽으로
          scanf("%c", &ch); //공백 읽기
          if (ch == '\n') //엔터를 치면?
          { if (hang == 0) { //첫번째줄 마치면
                  yull = current_yull;//그 걸 현재열로 
              }
              hang++;            //행하나 추가
              current_yull = 0;  //열위치 0으로 옮기기
          }
      }
      if (hang == 0 || yull == 0) { // 만약 아무것도 입력하지않거나 열 크기 가 0이면 메세지 띄우고 종료
          printf("wrong input\n"); 
          return 1;
      }
      int** A = (int**)malloc(hang * sizeof(int*)); //오늘 배운부분, 행의 개수만큼 매모리 생성 1학기 c프 시간에 배운 포인터 사용, 항목크기에 행의 개수 곱하고 이중포인터에 저장한 후 이것을 이중 포인터 변수 A에 저장
      for (int j = 0; j < hang; j++) {
          A[j] = (int*)malloc(yull * sizeof(int));
      }
      for (int j = 0; j < hang; j++) { // A로 옮기기
          for (int i = 0; i < yull; i++) {
              A[j][i] = arr[j][i];
          }
      }
      int** B = (int**)malloc(yull * sizeof(int*)); //B는 뒤집은것
      for (int j = 0; j < yull; j++) {
          B[j] = (int*)malloc(hang * sizeof(int));
      }
      for (int j = 0; j < hang; j++) { //반대로 뒤집어서 B에 넣기
          for (int i = 0; i < yull; i++) {
              B[i][j] = A[j][i];
          }
      }
      printf("\nresult (%d x %d):\n", hang, yull);// 결과 출력하기
      for (int j = 0; j < yull; j++) {
          for (int i = 0; i < hang; i++) {
              printf("%3d ", B[j][i]);
          }
          printf("\n");
      } 
      for (int j = 0; j < hang; j++) free(A[j]);// 위에서 열로써 저장했기 때문에 열로 저장해서 열로 free 해제해야한다
      free(A);// 오늘 배운 부분  free로 끝내기
      for (int j = 0; j < yull; j++) free(B[j]);
      free(B);

      return 0;
  }
