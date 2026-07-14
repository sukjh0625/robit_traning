my_list = [] #주된 저장소
lines = [] #임시 저장소

while True: # break전까지는 계속 반복하기
    line = input() 
    if line == "":  #아무것도 치지않고 엔터 두번치면 끝내기
        break
    lines.append(line) #적은것을 lines 뒤에 저장하기


for user_input in lines: # lines있던 것들 하나씩 user_input에 넣기
    parts = user_input.split() # 띄어쓰기를 기준으로 쪼개기
        
    cmd = parts[0] #커맨드에 저장 첫번째 단어

   
    if cmd == "append": #만약 커맨드가 append라면 그냥 my_list뒤에 붙이기
        my_list.append(parts[1])

    
    elif cmd == "insert": #만약 insert 라면 
        index = int(parts[1]) #위치 확인하고 정수형으로 바꾼뒤에
        value = parts[2]  #뭐넣을건지 확인하고
       
        if 0 <= index <= len(my_list): #리스트 보다 작아야하고 0보단 크거나 같아야 하기때문에
            my_list.insert(index, value) # 위치에 맞는 값 넣기
        else: 
            print("인덱스 범위를 벗어났습니다.") #아니면 알려주기

   
    elif cmd == "remove":
        value = parts[1]
        
        if value in my_list: #만약 값이 리스트에 있다면 지우기
            my_list.remove(value)
        else:
            print(f"'{value}'은(는) 리스트에 존재하지 않습니다.") # 아니면 알려주기

    
    elif cmd == "pop": 
        
        if not my_list: #이미 아무것도 없으면 안된다 말하기
            print("리스트가 비어있어 pop을 수행할 수 없습니다.")
        else:
            if len(parts) > 1:#범위 확인해주기 아까 insert랑 같은 원리 len이용해서 값의 수 확인
                index = int(parts[1])
                
                if 0 <= index < len(my_list):
                    my_list.pop(index)
                else:
                    print("인덱스 범위를 벗어났습니다.")
            else:
                my_list.pop()

    
    elif cmd == "len": #len이용하고 my_list개수 세기
        print(len(my_list))

    elif cmd == "print":
        print(my_list)

    elif cmd == "clear":
        my_list.clear()