/* DFS_BFS_6593, 상범 빌딩 */
/* 포인트
 그냥 3차원 맵에서의 BFS 문제.
 참고로 3중 for문으로 입력받을때 층이 가장 밖에 있는 for문에 있어야한다.
*/
#include <iostream>
#include <queue>
#include <tuple>  // tie()
using namespace std;

int L,R,C, ans;
int dx[6]={1, -1, 0, 0, 0, 0};
int dy[6]={0,  0, 1,-1, 0, 0};
int dz[6]={0,  0, 0, 0, 1,-1};
int visited[35][35][35];
char map[35][35][35];  // R,C, 층
queue<tuple<int,int,int,int>>  q;   // y,x,L, cnt

void BFS(void);
void Reset(void);

int main()
{
    int i,j,k;

    while(1)
    {
        // 입력부
        cin>>L>>R>>C;

        // 시뮬레이션 종료 조건
        if(L==0 && R==0 && C==0) break;
        for(k=1; k<=L; k++)   // for문에서 "층"이 가장 바깥 쪽에 있어야함.. 간과하기 쉽다
            for(i=1; i<=R; i++)
                for(j=1; j<=C; j++)
                {
                    cin>>map[i][j][k];
                    if(map[i][j][k]=='S'){visited[i][j][k]=1; q.push({i,j,k,0});}  // 시작점일 경우 큐에 넣어줌
                }

        // 실행부
        BFS();

        // 출력부
        if(ans != 0)
            cout<<"Escaped in "<<ans<<" minute(s).\n";
        else
            cout<<"Trapped!\n";

        // 초기화 작업 (다음 시뮬레이션에서 사용해야 하므로)
        Reset();
    }

    return 0;
}

void BFS()
{
    int i, y,x,z, yy,xx,zz, cnt;

    while( !q.empty() )
    {
        tie(yy,xx,zz,cnt) = q.front();
        q.pop();

        if(map[yy][xx][zz]=='E'){ans=cnt; return;}

        for(i=0; i<6; i++)
        {
            y = yy + dy[i];   x = xx + dx[i];   z = zz + dz[i];

            // 맵 범위 벗어나는 경우
            if(y<1 || x<1 || z<1 || y>R || x>C || z>L) continue;

            // 방문한 적이 있는 경우
            if(visited[y][x][z]==1) continue;

            // 벽인 경우
            if(map[y][x][z]=='#'){visited[y][x][z]=1; continue;}

            // 이동 가능한 경우 큐에 넣어줌
            visited[y][x][z]=1;
            q.push({y,x,z, cnt+1});
        }
    }
}

void Reset()
{
    int i,j,k;

    // 정답 값 초기화
    ans=0;

    // 큐 비워줌
    while(!q.empty())
    {
        q.pop();
    }

    // 방문 배열 초기화
    for(i=1; i<=R; i++)
        for(j=1; j<=C; j++)
            for(k=1; k<=L; k++)
                visited[i][j][k]=0;
}
