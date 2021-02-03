/* DFS_BFS_2589, 보물섬 */
/* 포인트
 기본적인 BFS 문제/
 ios_base::sync_with_stdio(0) 사용해놓고 scanf() 절대로 사용하지 말자 !! ios_base::sync_with_stdio()를 지울 것
*/
#include <iostream>  // ios_base::sync_with_stdio() 사용해놓고.. scanf()사용하면 에러는 안뜨는데.. 입력을 이상하게 받는다 같이사용하지 말것
#include <stdio.h>  // cin으로 받아도 되는데, 그렇게 구현하면 열방향 index가 0부터 시작하게 된다..
#include <string.h>  // memset()
#include <queue>
#include <tuple>  // tuple()
using namespace std;

typedef struct node{
    int y,x,cnt;
}node;

queue<node> q;
int R,C, ans;
int dx[4]={1, -1, 0, 0};
int dy[4]={0,  0, 1,-1};
int visited[55][55];
char map[55][55];

void BFS(void);
void Reset(void);

int main()
{
    int i,j;

    // 입력부
    cin>>R>>C;
    for(i=1; i<=R; i++)
        for(j=1; j<=C; j++)
            scanf(" %1c", &map[i][j]);   // 행단위로 입력 받으면 됨

    // 실행부
    for(i=1; i<=R; i++)
        for(j=1; j<=C; j++)  // 모든 위치에서. BFS 돌려서 "최대 멀리 이동 할 수 있는 거리"를 
        {            
            // 육지가 아닌 경우 (바다인 경우)
            if(map[i][j]=='W') continue;

            // 육지인 경우 (BFS 시작)
            visited[i][j]=1;  // 방문 표시
            q.push({i,j,0});  // 큐에 넣어줌
            BFS();
            if(ans==18) cout<<i<<","<<j<<endl;

            // 큐 초기화, 방문 기록 초기화
            Reset();
        }

    // 출력부
    cout<<ans;

    return 0;
}

void BFS()
{
    int i, y,x, yy,xx,cnt;

     while(!q.empty())
    {
        tie(yy,xx,cnt) = {q.front().y, q.front().x, q.front().cnt};
        q.pop();

        // 정답 갱신
        if(ans<cnt) ans = cnt;

        // 자식 노드 호출
        for(i=0; i<4; i++)
        {
            y = yy + dy[i];   x = xx + dx[i];

            // 다음 위치를 방문 할 수 없는 경우
            if(y<1 || x<1 || y>R || x>C) continue;  // 맵을 벗어나는 경우
            if(map[y][x] == 'W') continue;  // 바다인 경우
            if(visited[y][x] == 1) continue;  // 방문한 적이 있는 경우

            // 다음 위치를 방문 할 수 있는 경우
            visited[y][x] = 1;  // 방문표시
            q.push({y,x,cnt+1});  // 큐에 넣어줌
        }
    }
}

void Reset()
{
    // 방문 초기화
    memset(visited, 0, sizeof(visited));

    // 큐 초기화
    while(!q.empty())
    {
        q.pop();
    }
}
