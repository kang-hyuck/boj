/* Simulation_17837, 새로운 게임2 */
/* 포인트
 (시뮬레이션)문제
 1. "(위치,방향) 정보" 부분의 멤버 변수 값이 "확정"이 된다면. "갱신"(update) 해주어야 한다. !!! 항상 유의할 것!!!!
 2. "함수단위"로 나누어서 작성하면, 1.코드가 깔끔해지고, 2.함수 단위로 디버깅 하기 쉽다
*/
#include <iostream>
#include <deque>
#include <tuple>      // tie()
#include <algorithm>  // reverse()
using namespace std;

typedef struct MAL{
    int y,x, dir;
}MAL;

int N,K, ans,finish;    // 체스판 크기, 말의 갯수
deque<int> map[15][15];
int zone[15][15];
MAL mal[15];
int dx[5] = {0, 1,-1, 0, 0};  // 0번 더미
int dy[5] = {0, 0, 0,-1, 1};

void Start(void);
void Move(void);
int CheckRange(int, int);
int ChangeDir(int);
void UpdateInfo(int, int, deque<int>);

int main()
{
    int i,j, a,b,c;

    // 입력부
    cin>>N>>K;
    for(i=1; i<=N; i++) for(j=1; j<=N; j++) cin>>zone[i][j];
    for(i=1; i<=K; i++) {cin>>a>>b>>c;  mal[i] = {a,b,c};}
    for(i=1; i<=K; i++) map[mal[i].y][mal[i].x].push_back(i);  // map에 해당 "말 번호" 넣는다

    // 실행부
    Start();
    
    return 0;
}

void Start()
{

    while(1)
    {
        // ans 카운트
        ans++;
    
        // 말을 움직인다
        Move();
        
        // 종료 조건 확인
        if( 1==finish ) {cout<<ans; return;}
        else if( ans > 1000 ) {cout<<"-1"; return;}
    }
}

void Move()
{
    int num,i, x,y,xx,yy,dir, len,index;
    deque<int> temp;
    
    // 말 1~K번 움직인다
    for(num=1; num<=K; num++)
    {
        // 말 위치,방향 정보 가져옴
        tie(yy,xx,dir) = {mal[num].y, mal[num].x, mal[num].dir};
        
        // 말이 이동하려는 위치 계산
        y = yy + dy[dir];  x = xx + dx[dir];
        
        // 이동할 수 없는 경우 (맵을 벗어나거나 || 파란색 칸인 경우)
        if( -1 == CheckRange(y,x) || zone[y][x]==2 ){
            dir=ChangeDir(dir);  // 방향 전환
            y = yy + dy[dir];  x = xx + dx[dir];  // 전환된 방향으로 한 칸 조사
            mal[num].dir = dir;  // 방향이 바뀌었으므로. 방향정보를 갱신 해준다
            if( -1 == CheckRange(y,x) || zone[y][x]==2 ) continue; // 바뀐 방향도 이동이 불가능 한 경우 (이동X)
        }
        
        // 이동할 수 있는 경우
        len = (int)map[yy][xx].size();
        for(index=0; index<len; index++) if(map[yy][xx][index]==num) break;  // num이 위치한 index를 찾는다
        for(i=index; i<len; i++) temp.push_back(map[yy][xx][i]);  // index~마지막 원소까지 이동하려는 곳에 담아준다
        for(i=index; i<len; i++) map[yy][xx].pop_back();  // 갯수만큼 꺼낸다.
        
        // 이동하는 곳이 빨간 칸인 경우
        if(zone[y][x] == 1) reverse(temp.begin(), temp.end());  // 뒤집어 준다
        
        // 이동 하려는 곳에 담아준다
        for(i=0; i<(int)temp.size(); i++) map[y][x].push_back(temp[i]);
        UpdateInfo(y,x,temp);  // 태워져서 이동되는 모든 말들의 "위치정보"를 갱신 해준다
        temp.clear();  // 임시로 담았던 deque을 비워준다
        
        // 말이 4개 이상 쌓이면 종료임을 알린다
        if( 4 <= (int)map[y][x].size()) finish=1;
    }
}

int CheckRange(int y, int x){
    if( y<1 || x<1 || y>N || x>N) return -1;  // 범위를 벗어나는 경우 -1
    else return 1;
}

int ChangeDir(int dir){
    switch(dir){
        case 1 : return 2;
        case 2 : return 1;
        case 3 : return 4;
        case 4 : return 3;
    }
    return 0;
}

void UpdateInfo(int y, int x, deque<int> temp){
    for(auto a : temp){
        mal[a].y = y;  mal[a].x = x;
    }
}
