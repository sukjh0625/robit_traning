  #define _CRT_SECURE_NO_WARNINGS
  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>

  typedef struct point//구조체 만들기
  {
      int x;
      int y;
  } Point;//구조체 이름

  int main(void)
  {
      Point* point;// 구조체 포인터
      int count; //좌표개수
      int a;// 겉에있는 반복문에서 쓰는 변수
      int b; // 안에있는 반복문에서 쓰는 변수
      int maxnumber = 0;// 바깥쪽 좌표의 배열 번호
      int wrong = 0;// 입력 개수가 맞는가보는 변수

      double xdistance;//x거리
      double ydistance;//y거리
      double distance;//거리
      double sum;//합
      double max = 0;//거리합중에서 가장 큰 값

      while (wrong == 0)//좌표가 옳을때까지 반복
      {printf("how many coordinates would you write: ");
          scanf("%d", &count);

          if (count >= 2)//2개 이상인지 확인
          {
              wrong = 1;
          }
          else
          {
              printf("you should write more than two coordinate\n");
          }
      }
      point = (Point*)malloc(sizeof(Point) * count); //동적 할당 count개수만큼 저장할메모리
      for (a = 0; a < count; a++)//count개수만큼
      {
          printf("write %dth coordinate: ", a + 1);
          scanf("%d %d", &point[a].x, &point[a].y); // 두 수를 a번쨰 xy에 저장
      }
      for (a = 0; a < count; a++)// count 만큼
      {
          sum = 0;//거리합을 0으로 초기화
          for (b = 0; b < count; b++)//b가 인덱스 번호이다
          {
              if (a != b)//만약 좌표가 자기 자신이 아니라면
              {
                  xdistance = point[a].x - point[b].x;//x좌표 차이
                  ydistance = point[a].y - point[b].y;//y좌표 차이
              
                  distance = sqrt(
                      xdistance * xdistance +
                      ydistance * ydistance
             
                  );

                  sum = sum + distance;//계산한 거리를 현재 거리에 더하기
              }
          }
          if (a == 0) //a가 첫 좌표라면
          {
              max = sum; //첫좌표를 가정 먼 좌표로 설정
              maxnumber = a;// 배열번호도 저장
          }
          else if (sum > max)//아니라면 원래 최댓값보다 큰지 확인
          {
              max = sum;//바꾸기
              maxnumber = a;
          }
      }
      printf("maximum coordinate is(%d, %d) and sum of distances is about %.1lf.\n",
          point[maxnumber].x,
          point[maxnumber].y,
          max);

      free(point);// 동적할당 출기

      return 0;
  }
