import csv
import json

def main():
    clean_rows = []    
    valid_scores = []  

    try:
        with open("students.csv", "r", newline="", encoding="utf-8-sig") as file:
            
            reader = csv.DictReader(file) #이부분을 바꿔서 쓰고 그럼 header = next(reader) 이 부분이 없어져도 된다
            
            for row in reader: 
                name = row['name'] #name = row[0] 부분이 이름값으로 찾을수 있게된다
                raw_score = row['score']#raw_score = row[1] 도 마찬가지 값으로 찾을 수 있게 된다
                
                try: 
                    score = int(raw_score)
                    
                    if score < 0 or score > 100:
                        print(f"[오류] {name}: 허용 범위 초과 ({score}점)")
                        continue 
                        
                except ValueError:
                    print(f"[오류] {name}: 숫자 변환 실패 ('{raw_score}')")
                    continue 
                
                
                clean_rows.append({'name': name, 'score': score})
                valid_scores.append(score)
                    
    except FileNotFoundError:
        print("오류: students.csv 파일이 없습니다. 먼저 파일을 만들어주세요.")
        return 

    
    with open("clean_students.csv", "w", newline="", encoding="utf-8") as file:
        fieldnames = ["name", "score"] #얘는 딕셔너리로 저장한다
        writer = csv.DictWriter(file, fieldnames=fieldnames) #이름만 바꿔준것
        
        writer.writeheader()  
        writer.writerows(clean_rows)  

    
    if valid_scores:
        total_students = len(valid_scores)
        average_score = sum(valid_scores) / total_students
        top_score = max(valid_scores)

        summary_data = {
            "total_students": total_students,
            "average_score": average_score,
            "top_score": top_score
        }
        
        with open("summary.json", "w", encoding="utf-8") as file:
            json.dump(summary_data, file, ensure_ascii=False, indent=4)
            
        print("\n[완료] 성적 정리가 성공적으로 끝났습니다!")

if __name__ == "__main__":
    main()
