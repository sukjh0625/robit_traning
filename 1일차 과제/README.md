books = {} # 빈 딕셔너리
book_order = []  # 등록 순서 기록용
borrowed_records = {}  # 어떤 사람이 어떤 책을 빌려갔는지 대출현황 저장


def handle_add(args):#args 리스트 정의
    """add 책이름 수량""" # 이런식으로 쓰면된다 알려주는것
    if len(args) != 2: #만약 2개가 아니라면 error코드 띄우기
        print("ERROR: Invalid arguments for add")
        return

    book_name, qty_str = args #2개의 인자를 book과 qty로 나누어 담기
    if not qty_str.isdigit():  #문자열로 들어온 숫자 사이에 문자가 있다면 error표시하고 끝내기
        print("ERROR: Quantity must be a non-negative integer")
        return

    qty = int(qty_str) #검증이 끝났으면 정수형으로 바꾸고 
    if qty < 0: #음수라면 끄기 error코드 띄우고 끄기
        print("ERROR: Quantity must be a non-negative integer") 
        return

    if book_name not in books: #만약 리스트에 없는 책이라면 수량을 0에서 하나씩 추가하고, 리스트에 있다면 뛰어 넘는다
        books[book_name] = 0
        book_order.append(book_name)

    books[book_name] += qty #수량을 책이름 뒤에 더해준다


def handle_borrow(args): #borrow뒤에 들어오는 인자가 2개 라면 밑의 코드에서 각각 나눠주거나 만약 아니라면 error띄움
    """borrow 사용자 책이름"""
    if len(args) != 2:
        print("ERROR: Invalid arguments for borrow")
        return

    user, book_name = args

    if book_name not in books:
        print("ERROR: Book does not exist")
        return

    if books[book_name] <= 0: #재고 없는경우
        print("ERROR: Out of stock")
        return

    if user in borrowed_records and book_name in borrowed_records[user]:  #빌린사람이 또 못빌리게 만드는 코드
        print("ERROR: User already borrowed this book")
        return

    books[book_name] -= 1 #다 통과했으니까 대출 진행
    if user not in borrowed_records: #만약 처음 빌리는거라면 
        borrowed_records[user] = set() #set()하나 만들어줌
    borrowed_records[user].add(book_name) #이런 형식으로 저장


def handle_return(args):    #인자가 2개라면 
    """return 사용자 책이름"""
    if len(args) != 2:
        print("ERROR: Invalid arguments for return")
        return

    user, book_name = args #각각 할당

    if user not in borrowed_records or book_name not in borrowed_records[user]: #실제로 대출중인 책만 반납
        print("ERROR: This book was not borrowed by the user")
        return

    books[book_name] += 1   #빌린 책 수량 하나씩 추가
    borrowed_records[user].remove(book_name) #대출목록에서 책 제거
    
    if not borrowed_records[user]: #해당 사용자 완전히 제거
        del borrowed_records[user]


def handle_status(args): #인자가한개인지 확인하고 변수에 할당
    """status 책이름"""
    if len(args) != 1: #존재안하면 error
        print("ERROR: Invalid arguments for status")
        return

    book_name = args[0] #존재안하면 error
    if book_name not in books:
        print("ERROR: Book does not exist")
    else:
        print(books[book_name]) # 아니면 수량 조회해서 출력


def handle_user(args): # 인자가 사용자인지 확인하고 아니면 error
    """user 사용자"""
    if len(args) != 1:
        print("ERROR: Invalid arguments for user")
        return

    user = args[0] # 대출기록이 없거나 빌린 책 개수가 0개라면 empty 뜨게하기
    if user not in borrowed_records or len(borrowed_records[user]) == 0:
        print("EMPTY")
    else:
        print(" ".join(borrowed_records[user])) #책이름 공백 한칸 두고 하나의 문자열로 합침


def handle_list(args): # 명령어 뒤에는 아무런 인자도 있으면 안된다
    """list"""
    if len(args) != 0:
        print("ERROR: Invalid arguments for list")
        return

    for book in book_order: #저장해둔 순서 리스트 돌면서 리스트 하나씩 출력
        print(f"{book} {books[book]}")


def main(): # 계속 반복
    while True:
        try:
            line = input().strip() #공백제거 
        except EOFError: #아니면 error
            break

        if not line:
            continue

        tokens = line.split() #리스트를 공백 기준으로 쪼개기
        command = tokens[0] #첫번쨰값 명령어
        args = tokens[1:] # 명령어에 전달할 리스트

        if command == "Exit": #무한루프 탈출
            break
        elif command == "add":
            handle_add(args)
        elif command == "borrow":
            handle_borrow(args)
        elif command == "return":
            handle_return(args)
        elif command == "status":
            handle_status(args)
        elif command == "user":
            handle_user(args)
        elif command == "list":
            handle_list(args)
        else:
            print("ERROR: Unknown command")

한줄한줄씩 다 뜯어서 분석 해 본결과 코드는 오류가 없이 잘돌아갔다. 분석해서 이해한 내용을 직접 주석에 다 달아보았다. 하지만 조금 더 간단하게 표현해보기 위해서 import sys 를 제거 해 보았다.
그런데 실제로 실행 시켜 보니 아무런 설명이 없어서 무엇을 쳐야하는지 햇갈릴 수도 있겠다는 생각이 들어서 사용자가 이해하기 쉽게
def main():
    # 💡 [추가] 프로그램 시작할 때 터미널에 사용법 한글로 친절하게 출력하기
    print("==================================================")
    print("      [ 명령어 기반 도서 대출 관리 시스템 ]")
    print("==================================================")
    print(" 사용 가능한 명령어 예시:")
    print("  1. 책 등록 : add [책이름] [수량]    (예: add Python 5)")
    print("  2. 책 대출 : borrow [이름] [책이름] (예: borrow Chulsoo Python)")
    print("  3. 책 반납 : return [이름] [책이름] (예: return Chulsoo Python)")
    print("  4. 재고 확인 : status [책이름]      (예: status Python)")
    print("  5. 대출 현황 : user [이름]          (예: user Chulsoo)")
    print("  6. 전체 목록 : list")
    print("  7. 프로그램 종료 : Exit")
    print("==================================================")
이 코드를 추가해 보았다
