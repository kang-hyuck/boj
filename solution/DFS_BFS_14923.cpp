/* DFS_BFS_14923, 미로탈출 */
/* 포인트
 (BFS) 문제
 1. 벽을 부순 상태, 안부순 상태를 나누어서 BFS 큐에 넣어주었다
 2. 자식노드 호출 부분에서 상태에 따라 이동할 수 있는(=큐에 담을 수 있는) 조건문 부분을 고려해야한다
*/
#include <iostream>
#include <queue>
#include <tuple>
using namespace std;

typedef struct node{
    int y,x, state,cnt;  // state - 0:벽 안 부순 상태,  1:벽 1개 부순 상태
}node;

int N,M, ans;
int Hx,Hy, Ex,Ey;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0,  0, 1,-1};
int map[1010][1010];
int visited[1010][1010][2];  // 0:벽 안 부순 상태,  1:벽 1개 부순 상태
queue<node> q;

void BFS(void);

int main()
{
    int i,j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>N>>M;
    cin>>Hy>>Hx;
    cin>>Ey>>Ex;  // 문제가 이상함 ㄷㄷ x,y 역할이 반대다.. 이렇게 해야 정답
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
            cin>>map[i][j];   

    // 실행부
    ans=-1;  // BFS에서 목적지에 도착하지 못하고 종료되면 이 값 반환 됌
    q.push({Hy,Hx,0,0});  // 초기 위치 큐에 넣어줌
    BFS();

    // 출력부
    cout<<ans;

    return 0;   
}

void BFS()
{
    int i,  y,x,yy,xx, state,cnt;

    while(!q.empty())   
    {
        tie(yy,xx,state,cnt) = {q.front().y, q.front().x, q.front().state, q.front().cnt};
        q.pop();

        // 종료 조건
        if(yy==Ey && xx==Ex){ans=cnt; return;}  // 목적지에 도달하면 BFS 종료

        // 다음 자식 노드 호출
        for(i=0; i<4; i++)
        {
            y = yy + dy[i];   x = xx + dx[i];

            // 다음 위치에 이동할 수 없는 경우
            if( y<1 || x<1 || y>N || x>M) continue;  // 맵을 벗어나는 경우
            if( visited[y][x][state] == 1) continue;  // 방문한 적이 있는 경우
            if( map[y][x] == 1 && state == 1) continue;  // 이동 하려는 곳이 벽인데, 벽을 부순적이 있는 경우

            // 다음 위치로 이동할 수 있는 경우
            if( map[y][x] == 1 && state == 0 ) // 이동하려는 곳이 벽 && 벽 부순적 없는 경우
            {
                // 다음 위치로 이동
                visited[y][x][state+1]=1;  // 방문표시
                q.push({y,x,state+1,cnt+1});  // 큐에 넣어줌 (상태 변화) 
            }
            else if( map[y][x] == 0 ) // 이동하려는 곳이 길인 경우 (자기 상태값 유지)
            {
                // 다음 위치로 이동
                visited[y][x][state]=1;  // 방문표시
                q.push({y,x,state,cnt+1});  // 큐에 넣어줌    
            }   
        }
    }
}
