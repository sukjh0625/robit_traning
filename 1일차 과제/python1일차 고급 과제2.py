import sys


books = {}
book_order = [] 
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

    if book_name not in books:
        print("ERROR: Book does not exist")
        return

    if books[book_name] <= 0:
        print("ERROR: Out of stock")
        return

    if user in borrowed_records and book_name in borrowed_records[user]:
        print("ERROR: User already borrowed this book")
        return

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

    if user not in borrowed_records or book_name not in borrowed_records[user]:
        print("ERROR: This book was not borrowed by the user")
        return

    books[book_name] += 1
    borrowed_records[user].remove(book_name)
    
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
        print(" ".join(borrowed_records[user]))


def handle_list(args):
    """list"""
    if len(args) != 0:
        print("ERROR: Invalid arguments for list")
        return

    for book in book_order:
        print(f"{book} {books[book]}")


def main():
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

    while True:
        try:
          
            line = input("명령어 입력 >>> ").strip()
        except EOFError:
            break

        if not line:
            continue

        tokens = line.split()
        command = tokens[0]
        args = tokens[1:]

        if command == "Exit":
            print("프로그램을 종료합니다.")
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
