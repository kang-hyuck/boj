/* Simulation_20055, 컨베이어 벨트 위의 로봇 */
#include <iostream>
#include <deque>
#include <utility>  // pair<>
using namespace std;

#define f first
#define s second

int N,K;
int ans;
deque<pair<int,int>> dq;  // <내구도, 로봇 유/무>

void Start();
void MoveRobot(int);

int main()
{
    int i, temp;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>> N >> K;
        for(i=0; i<2*N; i++)
    {
        cin>>temp;
        dq.push_back({temp,0});
    }

    // 실행부    
    Start();

    // 출력부
    cout<<ans;

    return 0;
}

void Start()
{
    int i, cnt;
    pair<int,int> popped;

    while(1)
    {
        ans++; // 단계 진행 횟수 증가
        cnt=0; // 시뮬레이션 후 내구도 0 갯수 카운트시 사용
            
        // 내려가는 위치에 로봇 있을 경우 바닥으로 로봇 내려줌 (컨테이너 돌기 전에 내려줘야한다)
        if(dq[N-1].s==1) dq[N-1].s=0;
            
        // 컨테이너 이동
        popped = dq.back(); // 2N 번째 컨테이너(인덱스는 2N-1번)를 맨앞으로 넣을 것임
        dq.pop_back();
        dq.push_front(popped);
        
        // 로봇 있는곳 움직임 (내려가는 위치부터. 왼쪽방향으로 이동하면서 검사한다. 로봇이 오른쪽으로 이동하므로.)
        for(i=N-1; i>=0; i--)
            if(dq[i].s==1) MoveRobot(i);        
           
        // 올라가는 위치에 로봇 올린다
        if(dq[0].f!=0 && dq[0].s==0) {dq[0].s=1; dq[0].f--;}
            
        // 내구도 0 갯수 검사
        for(i=0; i<2*N; i++)
            if( dq[i].f == 0 ) cnt++;
        
        // 종료 조건 확인 (0갯수 K개 이상인지 확인)
        if(cnt>=K) return;
    }
}

void MoveRobot(int i)
{
    // 로봇이 이동하지 못하거나 내려가는 위치인 경우.
    if(i==N-1) {dq[i].s=0; return;}  // 로봇 있는 곳이 내려가는 위치였다면 로봇을 내려준다.  
    if(dq[i+1].s != 0 || dq[i+1].f == 0) return; //  (오른쪽에 로봇이 있거나 || 오른쪽 내구도가 0이면 종료)

    // 로봇이 이동 할 수 있는 경우 오른쪽으로 이동 해준다.
    dq[i+1].s = 1;  // 오른쪽으로 이동, 로봇표시
    dq[i].s=0;  // 자기 우치에 있던 로봇 표시 삭제
    dq[i+1].f--; // 오른쪽 내구도 지움
}

