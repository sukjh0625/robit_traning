import sys

# 데이터를 관리할 전역 변수 (또는 딕셔너리/리스트)
# 책 정보: { 책이름: 남은수량 } -> 등록 순서 유지를 위해 list 명령 시 dict.keys() 활용
books = {}
book_order = []  # 등록 순서 기록용

# 대출 정보: { 사용자: 세트(대출 중인 책 이름들) }
borrowed_records = {}


def handle_add(args):
    """add 책이름 수량"""
    if len(args) != 2:
        print("ERROR: Invalid arguments for add")
        return

    book_name, qty_str = args
    if not qty_str.isdigit():
        print("ERROR: Quantity must be a non-negative integer")
        return

    qty = int(qty_str)
    if qty < 0:
        print("ERROR: Quantity must be a non-negative integer")
        return

    if book_name not in books:
        books[book_name] = 0
        book_order.append(book_name)

    books[book_name] += qty


def handle_borrow(args):
    """borrow 사용자 책이름"""
    if len(args) != 2:
        print("ERROR: Invalid arguments for borrow")
        return

    user, book_name = args

    # 1. 책이 존재하는지 확인
    if book_name not in books:
        print("ERROR: Book does not exist")
        return

    # 2. 수량이 남아있는지 확인
    if books[book_name] <= 0:
        print("ERROR: Out of stock")
        return

    # 3. 같은 사용자가 같은 책을 이미 대출 중인지 확인
    if user in borrowed_records and book_name in borrowed_records[user]:
        print("ERROR: User already borrowed this book")
        return

    # 대출 처리
    books[book_name] -= 1
    if user not in borrowed_records:
        borrowed_records[user] = set()
    borrowed_records[user].add(book_name)


def handle_return(args):
    """return 사용자 책이름"""
    if len(args) != 2:
        print("ERROR: Invalid arguments for return")
        return

    user, book_name = args

    # 실제로 대출 중인 책인지 확인
    if user not in borrowed_records or book_name not in borrowed_records[user]:
        print("ERROR: This book was not borrowed by the user")
        return

    # 반납 처리
    books[book_name] += 1
    borrowed_records[user].remove(book_name)
    
    # 사용자의 대출 목록이 비었다면 key 삭제
    if not borrowed_records[user]:
        del borrowed_records[user]


def handle_status(args):
    """status 책이름"""
    if len(args) != 1:
        print("ERROR: Invalid arguments for status")
        return

    book_name = args[0]
    if book_name not in books:
        print("ERROR: Book does not exist")
    else:
        print(books[book_name])


def handle_user(args):
    """user 사용자"""
    if len(args) != 1:
        print("ERROR: Invalid arguments for user")
        return

    user = args[0]
    if user not in borrowed_records or len(borrowed_records[user]) == 0:
        print("EMPTY")
    else:
        # 대출 목록 출력 (정렬 여부가 없다면 편의상 공백 구분 출력)
        print(" ".join(borrowed_records[user]))


def handle_list(args):
    """list"""
    if len(args) != 0:
        print("ERROR: Invalid arguments for list")
        return

    if not book_order:
        # 등록된 책이 없을 때 조건이 없으므로 빈 줄 혹은 안내 (요구사항엔 등록 순서대로 출력만 명시)
        return

    for book in book_order:
        print(f"{book} {books[book]}")


def main():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        if not line:
            continue

        tokens = line.split()
        command = tokens[0]
        args = tokens[1:]

        if command == "Exit":
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


if __name__ == "__main__":
    main()
