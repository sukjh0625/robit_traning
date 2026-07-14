import numpy as np # numpy를 np로 부르기로 함
import matplotlib.pyplot as plt # plt로 부르기로 함
from scipy.integrate import solve_ivp # 미분방정식을 정밀 계산해주는 알고리즘 엔진을 가져옴


print("탄도 미사일 3D 시뮬레이터")



THRUST_FORCE = 400000.0  #현무2를 예시로 잡고 엔진추력을 고정시켜둠
BURN_TIME = 40.0         #현무2를 예시로 잡고 점화시간을 고정시켜둠


try:  #저번에 썼던것처럼 try를 이용해서 만약 잘못 입력하면 튕기지 않도록 만듦
    dry_mass_ton = float(input("1. 미사일 자체 무게(연료 제외)를 입력하세요 (ton 단위, 추천: 1.5): ")) #모두 예시로 현무2 사용, 소숫점 사용 가능하도록 float사용
    fuel_mass_ton = float(input("2. 탑재할 고체 연료의 무게를 입력하세요 (ton 단위, 추천: 3.0): "))
    
    launch_angle = float(input("3. 발사 각도를 입력하세요 (degree, 탄도탄 추천: 60~85): "))
    azimuth_angle = float(input("4. 방위각을 입력하세요 (degree, 추천: 0~90): "))
    v0 = float(input("5. 초기 사출 속도를 입력하세요 (m/s, 수직발사대 가스 사출 속도, 추천: 50): "))
except ValueError: #만약 오류가 나면 문장 띄우고 종료
    print("올바른 숫자를 입력해주세요. 프로그램을 종료합니다.")
    exit()


dry_mass = dry_mass_ton * 1000.0 #기본 질량을 1000으로 나눠서 톤단위로 바꾸기
fuel_mass = fuel_mass_ton * 1000.0 #연료 질량을 1000으로 나눠서 톤단위로 바꾸기


g = 9.81 #중력 고정
rho = 1.225    # 대기밀도 고정
C_d = 0.25   # 항력기준 고정
base_density = 7800  # 금속은 가중치가 있으므로 고정시켜둠

fuel_burn_rate = fuel_mass / BURN_TIME #무게가 1초당 얼마나 타는지 계산 


theta = np.radians(launch_angle) #np.radians를 사용해서 도를 라디안으로 변환
phi = np.radians(azimuth_angle)


v0_x = v0 * np.cos(theta) * np.cos(phi) #발사대 초기 속도 즉 초기 사출 속도를 분해
v0_y = v0 * np.cos(theta) * np.sin(phi)
v0_z = v0 * np.sin(theta)

init_state = [0.0, 0.0, 0.0, v0_x, v0_y, v0_z] #처음 위치와 속도를 리스트로 표기


def hyunmoo_equations(t, state): # 비행시간과 현재 위치 속도를 받아온다
    x, y, z, vx, vy, vz = state 
    v = np.sqrt(vx**2 + vy**2 + vz**2) #피타고라스 정리를 아용해서 총 속도를 구한다
    
    
    if t < BURN_TIME: #연료가 타는중이라면 위치와 백터를 연결해서 얼마나 바뀌는지 연결
        current_mass = (dry_mass + fuel_mass) - (fuel_burn_rate * t) #실시간으로 가벼워지는 무게 계산
        if v < 0.1: 
            tx, ty, tz = THRUST_FORCE * np.cos(theta) * np.cos(phi), THRUST_FORCE * np.cos(theta) * np.sin(phi), THRUST_FORCE * np.sin(theta)
        else:
            tx, ty, tz = THRUST_FORCE * (vx / v), THRUST_FORCE * (vy / v), THRUST_FORCE * (vz / v)
    else: #만약 연료가 다 떨어졌다면 힘을 못받는다는 것을 표현
        current_mass = dry_mass  
        tx, ty, tz = 0.0, 0.0, 0.0
        
    
    volume = current_mass / base_density #무게 기반으로 단면적을 계산 기준은 현무 기준으로 잡음
    radius = ((3 * volume) / (4 * np.pi)) ** (1/3)
    area = np.pi * (radius ** 2)
    
    
    current_rho = rho * np.exp(-z / 8500.0) if z > 0 else rho #대기밀도가 높아지면 낮아지므로 대략적으로 비례한다고 잡고 계산
    D = 0.5 * current_rho * C_d * area
    
    
    fx_drag, fy_drag, fz_drag = -D * v * vx, -D * v * vy, -D * v * vz #공기저항은 속도의 제곱에 비례하고 -방향으로 작용한다고 두고 계산
    
    
    ax = (tx + fx_drag) / current_mass #뉴턴 2법칙이용
    ay = (ty + fy_drag) / current_mass
    az = (tz + fz_drag) / current_mass - g#중력가속도 빼줌 위에서 정의
    
    return [vx, vy, vz, ax, ay, az] #다음 궤적 예상

def hit_ground(t, state): #만약 땅에 닿았다면 state[2]즉 y축이 0이되면 꺼짐
    return state[2]
hit_ground.terminal = True
hit_ground.direction = -1


t_span = (0, 3000) #sol변수에 고속연산 결과 저장
sol = solve_ivp(hyunmoo_equations, t_span, init_state, events=hit_ground, max_step=0.2)


t_steps = sol.t
x_coords = sol.y[0]
y_coords = sol.y[1]
z_coords = sol.y[2]

target_x = x_coords[-1]#-1이 리스트 마지막이므로 마지막 위치로 봄
target_y = y_coords[-1]
target_z = z_coords[-1]
t_flight = t_steps[-1]

burnout_idx = np.searchsorted(t_steps, BURN_TIME) #연료타는 시간을 40초로 고정해놓았기 때문에 대입 후 계산
if burnout_idx >= len(x_coords): 
    burnout_idx = -1


max_altitude = np.max(z_coords) #최고 높이 계산



print("  전략 미사일 타겟 분석 결과")

print(f"■ 설정 엔진 스펙     : 고체추진 추력 {THRUST_FORCE/1000:.1f} kN / {BURN_TIME}초 연소")
print(f"■ 발사 총 중량       : {dry_mass_ton + fuel_mass_ton:.2f} 톤 (최종 탄두 동체 무게: {dry_mass_ton:.2f} 톤)")
print(f"■ 연료 소진 시 고도   : {z_coords[burnout_idx]/1000:.2f} km")
print(f"■ 최고 정점 고도     : {max_altitude/1000:.2f} km (우주 공간 진입 후 재돌입)")
print(f"■ 총 비행 시간       : {t_flight/60:.2f} 분 ({t_flight:.1f} 초)")
print(f"■ 최종 낙하 타겟 좌표 :")
print(f"   X (전방 사거리) : {target_x/1000:.2f} km")
print(f"   Y (측방 편차)   : {target_y/1000:.2f} km")
print(f"   Z (고도)        : {target_z:.2f} m (지면 타격)")


fig = plt.subplots(figsize=(11, 8), subplot_kw={"projection": "3d"})[0]
ax = fig.gca() #화면에 11*8 화면을 띄움


ax.plot(x_coords[:burnout_idx+1]/1000, y_coords[:burnout_idx+1]/1000, z_coords[:burnout_idx+1]/1000, 
        label='Powered Ascent (Thrust ON)', color='crimson', linewidth=3) #추진 구간을 주황색으로 표시
if burnout_idx < len(x_coords) - 1:
    ax.plot(x_coords[burnout_idx:]/1000, y_coords[burnout_idx:]/1000, z_coords[burnout_idx:]/1000, 
            label='Free-Fall Ballistic Re-entry', color='darkblue', linewidth=2, linestyle='--')# 연료가 떨어졌지만 나는 부분을 남색으로 표시


ax.scatter(0, 0, 0, color='green', s=100, label='Launch Pad (Cold Launch)', marker='^')
ax.scatter(x_coords[burnout_idx]/1000, y_coords[burnout_idx]/1000, z_coords[burnout_idx]/1000, color='gold', s=120, label='Burnout', marker='o')#출발점은 초록색 삼각형, 연료 소진 지점은 노란색 원, 최종 타격 타겟 지점은 검은색 큰 별로 표시
ax.scatter(target_x/1000, target_y/1000, target_z/1000, color='black', s=200, label='Target Impact', marker='*')#w점선표시


ax.set_xlabel('X Distance (km)')#옆에 설명 붙이기
ax.set_ylabel('Y Distance (km)')
ax.set_zlabel('Altitude Z (km)')
ax.set_title(f'3D Hyunmoo-class Ballistic Missile Trajectory Simulation')
ax.legend()

plt.show() #창 띄우기