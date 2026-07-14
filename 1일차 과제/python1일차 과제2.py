def add_log(robot_name, battery, logs=[]):#logs=[]는 처음 값이 logs에 저장되서 유지되므로 logs=None으로 바꿔준다
 #if logs is None:
  # logs = [] 을 사용해줘서 바뀔때마다 새값이 들어오게 한다
 log = robot_name + " battery: " + battery # 문자열과 숫자는 더할수 없으므로 log = f"{robot_name} battery: {battery}"로 바꾸어 준다
 logs.append(log)
 return logs


print(add_log("frontbot", 80))
print(add_log("rearbot", 50))
print(add_log("armbot", 20))
