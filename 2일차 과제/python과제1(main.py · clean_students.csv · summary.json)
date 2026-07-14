import csv #CSV가져오기
import json # JSON가져오기 JSON은 파이선의 딕셔너리 파일을 텍스트로 바꾸거나 반대로 할수 있음

def main(): #main함수 정의
   
    clean_rows = []    # 빈 리스트 만들기 [이름,점수]용도
    valid_scores = []  #빈 리스트 민들기 점수 계산용 리스트

    
    try: # 코드를 실행하다가 만약 오류가 생기면 except로 넘어가게 하는 코드
        with open("students.csv", "r", newline="", encoding="utf-8") as file: ##students.csv=파일명, r=다시쓰기, 두번띄어지지 않게 하기, 한글 잘 읽게하기
            reader = csv.reader(file) # csv파일을 리스트 방법으로 읽게하기
            header = next(reader)  # 첫번째줄은 형식같은 느낌으로 첫줄 다음줄로 넘기기
            
            for row in reader: # 헤더 뺀 나머지줄을 첨부터 끝까지 읽기반복
                name = row[0] # 리스트의 첫번째 나오는것을 이름으로 저장한다
                raw_score = row[1] #두번째 나오는것은 값으로 저장
                
                try: 
                    
                    score = int(raw_score) #점수를 문자형에서 정수형으로 바꾼다
                    
                    
                    if score < 0 or score > 100: #만약 음수거나 100초과라면 fstring 이용해서 대입해서 출력해서 보여준다
                        print(f"[오류] {name}: 허용 범위 초과 ({score}점)")
                        continue # for문 탈출
                    
                    
                    
                    
                except ValueError: #만약 값이 안바뀌거나 해서 변환할수 없어서 error가 뜨면
                    
                    print(f"[오류] {name}: 숫자 변환 실패 ('{raw_score}')") #이렇게 출력
                    continue # 다음 학생 데이터로 넘어가기

                clean_rows.append([name, score]) #위의 빈 리스트 뒤에 추가해준다
                valid_scores.append(score) #위의 빈리스트에 추가
                    
    except FileNotFoundError: #파일을 못찾는 에러가 뜬다면
        print("오류: students.csv 파일이 없습니다. 먼저 파일을 만들어주세요.") #이렇게 뜨기
        return #main함수 끝내기

    
    with open("clean_students.csv", "w", newline="", encoding="utf-8") as file: #위에와 같은데 w가 있어서 만약 똑같은 파일이 있다면 덮어씌우고 없다면 추가
        writer = csv.writer(file) #파일에 쓸 글쓰기 기능을 만들고 그것을 writer라 명명
        writer.writerow(["name", "score"])  #첫줄에 형식 적기
        writer.writerows(clean_rows)        #파일에 쓰기

    
    if valid_scores: # 가능한 값인지 확인
        total_students = len(valid_scores) # 총학생수 확인후 total_students변수에 저장
        average_score = sum(valid_scores) / total_students # 값을 더하고 총학생수로 나누기
        top_score = max(valid_scores) #가장 큰 값 찾고 top_score로 명명
        
        
      

        summary_data = {
            "total_students": total_students,
            "average_score": average_score, # 딕셔너리 구조로 만들기
            "top_score": top_score
        }
        
        with open("summary.json", "w", encoding="utf-8") as file: #json 파일로 저장하기
            
            json.dump(summary_data, file, ensure_ascii=False, indent=4) 
            
        print("\n[완료] 성적 정리가 성공적으로 끝났습니다!")

if __name__ == "__main__": # 이 파일을 직접 돌렸을때만 돌아가게 만드는 코드
    main()
