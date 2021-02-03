#include <iostream>
#include <queue>
#include <vector>
#include <tuple>  // tie(), tuple()
using namespace std;

int ans;
char map[10][10];
int visited[10][10][10]; // [y][x][time]. 큐 안에 같은시간,같은위치를 같는 경우 피하려고 사용함.(큐 크기 커지는거 싫어서...) time은 8이상이면 큐에서 종료되게끔해놔서 10으로 충분.
int dx[9] = {0, 0, 0, 1, 1, 1,-1,-1,-1};
int dy[9] = {0,-1, 1, 0,-1, 1, 0,-1, 1};
queue<tuple<int,int,int>> q;  // <y,x, time>

void BFS(void);
void MoveWall(void); // 벽 1칸씩 내린다.

int main()
{
    int i,j;
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);   cout.tie(NULL);
    
    // 입력부
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            cin>> map[i][j];
    
    // 실행부
    BFS();

    // 출력부
    cout<< ans;

    return 0;
}

void BFS()
{
    int i,k, y,x,yy,xx, time, num;

    q.push({7,0, 0});

    while(!q.empty())
    {
        // 현재 들어 있는 큐 크기를 담는다.
        num = (int)q.size();
        
        // 1초 마다(=현재 큐에 있는 위치 정보를 전부 확인 할 때 마다) 벽을 내린다.
        for(k=0; k<num; k++)
        {
            // 큐에서 꺼낸다
            tie(yy,xx, time) = q.front();
            q.pop();
        
            // 종료 조건.
            if(time >=8){ans=1; return;}  // 8초 이상 버틴 경우. 모든 벽들이 다 내려가므로. 무조건 도착 가능.
            if(yy==0 && xx==7){ans=1; return;} // 도착지점에 도착한 경우.
            
            // 다음위치를 큐에 넣는다.
            for(i=0; i<9; i++)
            {
                y = yy + dy[i];    x = xx + dx[i];
            
                // 다음에 이동할 위치 가능성 확인.
                if(y<0 || x<0 || y>=8 || x>=8) continue;  // 맵 밖을 벗어나는 경우 skip.
                if(map[y][x] == '#') continue;  // 이동할 곳에 벽이 있는 경우 skip.
                if(visited[y][x][time+1]==1) continue;  // 다음에 넣을 위치를 이미 다른 방향에서 접근하여 큐에 넣은 경우 skip.
                if(y!=0 && map[y-1][x]=='#') continue;  // 이동하려는 곳 바로 위에 벽돌 있으면. 벽돌내려왔을때 부딪히므로 skip.
            
                // 여기에 온다면 이동 가능한 경우다.
                visited[y][x][time+1]=1;  // 방문표시
                q.push({y,x, time+1});
            }
        }
        
        // 1초마다 벽을 내린다.
        MoveWall();
    }
}
void MoveWall(void)
{
    int i,j;
    
    for(j=0; j<8; j++)
        for(i=7; i>=0; i--)
        {
            if(i==7 && map[i][j]=='#')  // 맨 아래행이면 지워줌
                map[i][j]='.';
            else if(map[i][j]=='#')  // 맨 아래행 아니면 내려줌
            {
                map[i][j]='.';
                map[i+1][j]='#';
            }
        }
}
