#로봇 상태 체크
robot_status = [
{"name": "mobilebot", "battery": 82, "position": (1.2, 0.5), "distance": 0.8},
{"name": "drone", "battery": 18, "position": (0.3, 1.5), "distance": 0.4},
{"name": "manipulator", "battery": 45, "position": (2.0, 1.0), "distance": 1.2},
]
# 배터리 체크 
def battery_status(battery): #함수 정의
    if battery >=60:          #if문 이용해서 배터리 상황 보여주기  
     return "배터리충분"
    elif battery >=20:
     return "배터리 주의"
    else:
     return "충전필요"

def check_obstacles(distance): #함수정의
  if distance <0.5:            #if문 이용해서 거리 재기
    return "장애물 감지"
  else:
    return "전진가능" 
  
def status_of_robot(robot): #print하기전 정의
  name= robot["name"]
  battery_check= battery_status (r ["battery"]) #위의 함수 이용해서 가져오기
  x,y= robot["position"]
  moving= check_obstacles (r ["distance"])

  print(f"[{name}]")   #위에 정의해놓은것들 다 프린트
  print(f"배터리: {battery_check}")
  print(f"위치: {x,y}")
  print(f"상태: {moving}")
  print()
    
for r in robot_status: 
  status_of_robot(r) # 로봇 상태에있는것 하나하나 r이란 변수로 알려주기
