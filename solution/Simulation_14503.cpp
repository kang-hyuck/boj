/* Simulation_14503, 로봇 청소기 */
/* 포인트
 (시뮬레이션) or (DFS) 문제
 1. DFS와 비슷하게 "현재위치"(yy,xx)와 "조사할 위치"(y,x)를 사용해서 while()문 안에서 if문으로 "다음 위치"로 갈 수 있는지 없는 지 확인 하는 작업을 해야한다
   시뮬레이션에서 "이동 위치"를 DFS에서 "자식 노드"라고 생각하면 된다.
 2. for문에서 4방향 어느곳으로도 이동하지 못한 경우..를 확인하기 위해서 "변수 clear"를 flag처럼 사용 했다.
 3. DFS로 풀 때.. 자식노드 호출하는 곳에서. DFS호출 후 뒤에 "break"으로 다 끊어버리면 나중에 "정답"을 찾아서 종료되면서 부모노드로 올라갈 때 부모노드에서도 자식노드를 더 호출 안하고 종료함
*/
#include <iostream>
using namespace std;

int N,M, ans;
int dx[4] = { 0, 1, 0,-1};
int dy[4] = {-1, 0, 1, 0};
int cleared[55][55];
int map[55][55];

int CanBack(int, int, int);

int main()
{
    int i,j, y,x,yy,xx,dir,temp, clear;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>N>>M;
    cin>>yy>>xx>>dir;
    for(i=0; i<N; i++)
        for(j=0; j<M; j++)
           cin>>map[i][j];

    // 실행부
    ans=1;  cleared[yy][xx]=1;  // 시작 위치부터 카운트
    while(1)
    {
        // 변수 초기화
        clear=0;  // 4방향 탐색 중... 청소가능한 위치로 이동 했는지 확인용도. 4방향 중 청소한 곳 없으면 뒤로 갈 수 있는지 확인
    
        // 4방향 이동 가능성 확인 (dir: 현재방향,  yy,xx: 현재위치,  y,x: 조사할 위치)
        for(i=0; i<4; i++)
        {
            // 조사할 방향 선택
            dir= (dir-1)>=0 ? (dir-1):3;  // 현재 바라보고 있는 방향의 "왼쪽 방향"으로 갱신 (for문이 4번 도니까.. 원래 바라보던 방향으로 돌아간다)
            y=yy+dy[dir];  x=xx+dx[dir];  // 바라보고 있는 방향의 "위치"를 계산
            
            // 해당 방향으로 이동할 수 없는 경우
            if(y<0 || x<0 || y>=N || x>=M) continue;  // 맵을 벗어나는 경우
            if(cleared[y][x]==1)  continue;  // 청소를 한 경우
            if(map[y][x]==1) continue; // 벽인 경우
            
            // 해당 방향으로 이동할 수 있는 경우
            cleared[y][x]=1;  // 해당 위치 청소 표시
            ans++;  // 청소한 칸 수 증가
            yy = y;  xx = x;  // 해당 위치로 이동
            clear=1; // 4방향 중 한 곳을 청소 했음을 의미
            break;  // 4방향 탐색을 빠져나오고 이동한다
        }
        
        // 4방향 이동 하지 못한 경우
        if(clear==0 && CanBack(yy,xx,dir)==1)  // 뒤로 갈 수 있는 경우
        {
            // 이동 방향 선택 (이동하면서 "dir 방향"은 유지 되어야 한다.. dir값 바뀌면 안됨)
            temp=(dir+2)%4;  // 바라보는 방향과 뒷 방향은 index 2 차이.
            
            // 이동 (뒷 방향으로)
            yy=yy+dy[temp];  xx=xx+dx[temp];
        }
        else if(clear==0 && CanBack(yy,xx,dir)==0)  // 뒤로 갈 수 없는 경우
        {
            break;  // 시뮬레이션 종료
        }
    }

    // 출력부
    cout<<ans;

    return 0;
}

int CanBack(int y, int x, int dir)
{
    // 뒷 방향 선택
    dir = (dir+2)%4;
    
    // 조사할 위치 선택
    y = y + dy[dir];   x = x + dx[dir];
    
    // 뒤로 이동 가능성 유/무
    if(y<0 || x<0 || y>=N || x>=M) return 0;  // 맵을 벗어나는 경우
    if(map[y][x]==1)  return 0;  // 벽이면 이동 불가
    else return 1;  // 벽이 아니면 이동 가능
}

