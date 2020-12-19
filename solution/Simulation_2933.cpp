#include <stdio.h>
#include <cstring> // memset
#include <utility> // pair
#include <vector>
#include <algorithm> // sort
using namespace std;

#define f first
#define s second

int R,C,  N;
int noDown;
char map[110][110];
int visited[110][110];
int cluster[110][110];
int dx[] = {1 ,0, 0,-1};
int dy[] = {0,-1, 1, 0};
vector<pair<int,int>> v;

void Throw(int,int);
void DFS(int,int);
void ClusterDown(void);

int main()
{
    int i,j,  height;
    
    // 입력부
    scanf("%d %d", &R,&C);
    for(i=0; i<R; i++)
        for(j=0; j<C; j++)
            scanf(" %1c", &map[i][j]);
    scanf("%d", &N);
    
    // 실행부
    for(i=0; i<N; i++)
    {
        scanf("%d", &height);
        height = R-height; // 맨 아래행이 높이 1이 되도록 뒤집어준다.
        if(i%2 == 0)
            Throw(height,0);  // 왼쪽에서 던짐
        else
            Throw(height,1);  // 오른쪽에서 던짐
    }

    // 출력부
    for(i=0; i<R; i++)
    {
        for(j=0; j<C; j++)
            printf("%c",map[i][j]);
        printf("\n");
    }
    
    return 0;   
}

void Throw(int height,int dir)
{
    int i,j,y,x;
    
    // 왼쪽에서 던진 경우.
    if(dir == 0)
    {
        // 부딪히는 지점을 찾는다.
        for(i=0; i<C; i++)
            if( map[height][i] == 'x' ) break;
        
        // 부딪히지 않았을 경우 종료한다.
        if(i==C) return;
        
        // 미네랄을 부순다.
        map[height][i] = '.';
    
        // 우,상,하 순서로 dfs 돌려서 내려앉아야 하는 clustuer가 존재하는지 확인한다.
        for(j=0; j<3; j++) 
        {
            y = height+dy[j];
            x = i+dx[j];
            
            // 맵 범위 안에 있고, 미네랄이 있을 경우 DFS 실행.
            if( (y>=0 && x>=0 && y<R && x<C) && (map[y][x]=='x'))
                    DFS(y,x);
            else
                continue;
            
            // 내려앉아야 하는 Cluster가 존재한다면 처리해준다.
            if(noDown==0)
            {
                sort(v.begin(), v.end(), greater<pair<int,int>>()); // y좌표가 가장 큰 것 (맨아래 행)  순으로 정렬한다.
                ClusterDown();
                memset(cluster, 0, sizeof(cluster));
            }
            
            // 다시 사용해야 하므로 초기화 해준다.
            memset(visited, 0, sizeof(visited));
            noDown = 0;
            v.clear();
        }
        
        return;
    }
    
    // 오른쪽에서 던진 경우. (왼쪽으로 던진 경우랑 코드는 같은데, 단지 부딪히는 미네랄 확인순서, dfs순서만 다르다)
    if(dir == 1)
    {
        // 부딪히는 지점을 찾는다.
        for(i=C-1; i>=0; i--)
            if( map[height][i] == 'x' ) break;
        
        // 부딪히지 않았을 경우 종료한다.
        if(i==-1) return;
        
        // 미네랄을 부순다.
        map[height][i] = '.';
    
        // 상,하,좌 순서로 dfs 돌려서 내려앉아야 하는 clustuer가 존재하는지 확인한다.
        for(j=1; j<4; j++) 
        {
            y = height+dy[j];
            x = i+dx[j];
            
            // 맵 범위 안에 있고, 미네랄이 있을 경우 DFS 실행.
            if( (y>=0 && x>=0 && y<R && x<C) && (map[y][x]=='x'))
                    DFS(y,x);
            else
                continue;
            
            // 내려앉아야 하는 Cluster가 존재한다면 처리해준다.
            if(noDown==0)
            {
                sort(v.begin(), v.end(), greater<pair<int,int>>()); // y좌표 가장 
                ClusterDown();
                memset(cluster, 0, sizeof(cluster));
            }
            
            // 다시 사용해야 하므로 초기화 해준다.
            memset(visited, 0, sizeof(visited));
            noDown = 0;
            v.clear();
        }
        
        return;
    }
    
}

void DFS(int yy,int xx)
{
    int i, y,x;
    
    // 종료조건 (1.방문 했었다면   2.맨 아래행에 왔다면)
    if( visited[yy][xx]==1 ) return;   
    if( yy== R-1 ){noDown=1;  return;}
    
    // 방문 표시
    visited[yy][xx] = 1;
    v.push_back({yy,xx});
    
    // 자식 노드 호출
    for(i=0; i<4; i++)
    {
        y = yy + dy[i];   
        x = xx + dx[i];
        
        if( (y>=0 && x>=0 && y<R && x<C) && (map[y][x]=='x'))
            DFS(y,x);
    }
    
}

void ClusterDown()
{
    int i, y,x;
    
    // cluster 존재 위치를 저장해준다. cluster의 각 미네랄이 내려갈때 자기 cluster 위치로는 이동가능하다.
    for(i=0; i<(int)v.size(); i++)
        cluster[v[i].f][v[i].s]=1;
    
    while(1)
    {
        // cluster 좌표 정보를 하나씩 꺼내서 이동할 위치를 v에 다시 담아준다.
        for(i=0; i<(int)v.size(); i++)
        {
            y = v[i].f;
            x = v[i].s;
            
            // 이동하려는 위치가 맵을 벗어나거나 자신의 cluster에 속하지 않는 'x'를 만날경우. 종료
            if( y+1 >= R ) return;
            if( (cluster[y+1][x]==0) && (map[y+1][x] == 'x') ) return; // cluster가 아닌데 미네랄이면 멈춰야함
            
            // 이동 가능하다면 vector에 y값 증가시킨 것을 넣어준다.
            v[i].f = y+1;
        }

        // cluster가 한칸 아래로 이동하면서 존재 위치가 바뀌므로 기존 cluster 정보를 제거 해준다
        memset(cluster, 0, sizeof(cluster));
        
        // 여기에 온다면 cluster가 1칸 아래로 이동 가능하다는 의미다. v에서 위치정보를 꺼내서 map에 이동한 것을 모두 그려준다.
        for(i=0; i<(int)v.size(); i++)
        {
            map[v[i].f-1][v[i].s] = '.'; // 이전에 위치했던 곳은 지워준다.
            map[v[i].f][v[i].s] = 'x';
            cluster[v[i].f][v[i].s]=1;
        }
    }
}
