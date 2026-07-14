def is_valid_code(code): #함수 정의
    if not code:
        return False #code가 아닌것 즉 빈 ""이면 false 가 된다
    if not code[0].isalpha():# code 첫글자가 알파벳이 아니라면 거짓
        return False
    
    i = 0# 약간 포인터 비슷한역할
    n = len(code)
    while i < n: # code끝까지 반복
        if not code[i].isalpha():#알파벳이 나와야하는 자리지만 안나오면 거짓
            return False
        i += 1 # 가리키는곳 확인했으면 다음거
        
        if i == n or not code[i].isdigit(): #코드가 끝나거나 알파벳 뒤에 숫자가 안나오면 거짓
            return False
        
        num_str = "" # 숫자가 두자리 이상이라면
        while i < n and code[i].isdigit(): #n까지 하나씩 더해감
            num_str += code[i]
            i += 1 #포인터 다음칸으로 이동
            
        if num_str[0] == '0':   #알파벳뒤에 0이온다면 거짓
            return False
            
    return True #다른게 다 맞다면 참


def decompress(code): #함수 정의
    if not is_valid_code(code): #위 함수가 아니라면 에러
        return "ERROR" 
    
    decompressed = "" #함수에 빈자리 만들어 두기
    i = 0 # 포인터 비슷한거
    n = len(code) # 코드 길이
    while i < n: # 끝까지 반복
        char = code[i] # 알파벳 문자형으로 저장
        i += 1 #다음거 넘어가기
        
        num_str = "" # 알파벳 뒤에오는 글자 저장
        while i < n and code[i].isdigit(): 
            num_str += code[i]#숫자를 글자형으로 저장
            i += 1# 다음거로 넘어감
            
        decompressed += char * int(num_str) #기존 decompressed 함수 값에 추가 하고 char * 숫자는 알파벳 반복
        
    return decompressed #마지막값 으로return


def compress(text): # 문자열이 비어있다면 빈문자열로 돌려줌
    if not text:
        return ""

    compressed = "" # compressed 를 비워둠
    current_char = text[0] # 문자형으로 저장
    count = 1 # 기본값을 1로 보고 몇번 반복됬는지 확인
    
    for i in range(1, len(text)): # 1부터 끝까지 비교 반복
        if text[i] == current_char: #글자가 방금 세던 문자와 같다면
            count += 1 #카운트 1 추가
        else: #세고있던 문자와 다를때
            compressed += current_char + str(count) #지금까지의 압축결과에 이어붙임
            current_char = text[i] #새로운 문자나왔으니 1부터 시작
            count = 1
    compressed += current_char + str(count) #마지막문자는 반복문에 없어서 더해줌
    
    if len(compressed) >= len(text):
        return text
    return compressed #압축결과가 더 길면 의미가 없으니까 긴지 짧은지 비교후 길다면 원래 text돌려주기





print("원하시는 문자열을 직접 키보드로 입력해 보세요!")
while True:
    print("-" * 40)
    mode = input("1: 압축하기(compress), 2: 복원하기(decompress), 3: 종료 -> ").strip()
    
    if mode == '1':
        user_text = input("압축할 문자열을 입력하세요 (예: aaaaabb): ").strip()
        print("결과:", compress(user_text))
    elif mode == '2':
        user_code = input("복원할 코드를 입력하세요 (예: a5b2): ").strip()
        print("결과:", decompress(user_code))
    elif mode == '3':
        print("프로그램을 종료합니다.")
        break
    else:
        print("잘못된 번호입니다. 1, 2, 3 중 하나를 입력하세요.")
