/* Simulation_16236, 아기 상어 */
/* 포인트
  1. BFS에서 일반적인 queue대신 priority_queue를 사용해서 방문 위치의 우선순위
    (1.거리,2.y좌표,3.x좌표)대로 큐에서 꺼낼 수 있도록 했다
  2. 큐에 들어가는 정보는 "상어가 방문할 노드의 정보"이다
  3. priority_queue에 1.구조체를 넣게되면 구조체 내부에서 operator연산자를 재정의 해주어야 하는데,
     2. tuple(또는 pair)를 사용하면 따로 operator 오버로딩 안하고!! 우선순위 별로 꺼낼 수 있다!!
*/
#include <iostream>
#include <queue>
#include <tuple>  // tie()
#include <string.h>  // memset()
using namespace std;

typedef struct sharkInfo{
    int y,x, size;
}sharkInfo;

sharkInfo shark;  // 상어 위치,크기 정보

// 큐는 상어가 이동하는 "위치"에 대한 노드 정보를 담는다, (큐 내의 우선순위 1.거리, 2.y좌표, 3.x좌표)
priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;  // BFS에서 "우선순위 큐" 사용

int dx[4] = {0, -1, 1, 0};
int dy[4] = {-1, 0, 0, 1};
int visited[25][25];
int map[25][25];
int N, ans, eat, eatCnt;

void Start(void);
void BFS(void);
void EatFish(int, int);
void Reset(void);

int main()
{
    int i,j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>N;
    for(i=1; i<=N; i++)
        for(j=1; j<=N; j++)
        {
            cin>>map[i][j];
            if(map[i][j]==9) shark={i,j,2};  // 큐에 상어 초기 위치 넣음
        }

    // 실행부
    Start();
    
    // 출력부
    cout<<ans;

    return 0;
}

void Start()
{
    while(1)
    {
        // 먹을 물고기 탐색 시작
        visited[shark.y][shark.x]=1;
        pq.push({0, shark.y,shark.x});
        BFS();
        
        // 종료조건
        if(eat==0) return;  // 먹은 물고기가 없다면 시뮬레이션 종료
        
        // 초기화
        eat = 0;  // 상어가 물고기 먹은 표시 초기화
        Reset();  // 방문표시, 큐 초기화
    }
}

void BFS()
{
    int i, y,x,yy,xx,cnt;

    while( !pq.empty())
    {
        // 큐에서 꺼낸다
        tie(cnt,yy,xx) = pq.top();  // priority_queue는 pq.top()에서 바로 tie()로 못묶는다... 에러 뜸
        pq.pop();
        
        // 먹을 수 있는 경우
        if(0 < map[yy][xx] && map[yy][xx] < shark.size){EatFish(yy,xx); ans+=cnt; eat=1; return;}   // 정답 갱신, eat 플래그 표시
        
        // 자식 노드 호출
        for(i=0; i<4; i++)
        {
            y = yy + dy[i];   x = xx + dx[i];
        
            // 다음 위치로 이동할 수 없는 경우
            if(y<1 || x<1 || y>N || x>N) continue;  // 맵을 벗어 나는 경우
            if(visited[y][x] == 1) continue;  // 방문한 적이 있는 경우
            if(map[y][x] > shark.size) continue;  // 상어보다 큰 경우
        
            // 다음 위치로 이동할 수 있는 경우
            visited[y][x]=1;  // 방문표시
            pq.push({cnt+1, y,x});
        }
    }
}

void EatFish(int y, int x)
{
    // 이전 상어 위치 지워줌
    map[shark.y][shark.x] = 0;
    
    // 상어 정보 갱신
    shark.y = y;  shark.x = x;  eatCnt++;
    map[y][x] = 0;  // 상어 자기 자신을 잡아먹지 않도록 0 넣어줌
    
    // 자신의 크기 만큼 먹을 경우 상어 크기 증가
    if(eatCnt == shark.size){shark.size++; eatCnt=0;}
}

void Reset()
{
    // 방문기록 초기화
    memset(visited, 0, sizeof(visited));
    
    // 큐 초기화
    while( !pq.empty() ){
        pq.pop();
    }
}
