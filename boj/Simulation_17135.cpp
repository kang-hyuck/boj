#include <stdio.h>
#include <queue>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int map[20][20];
int visited[20][20][3]; //  visited[][][궁수인덱스]
int used[20];   //  궁수가 적을 택했는지 유/무 표시
int dx[3] = {-1,0, 1};  //  {왼쪽,위,오른쪽} 순으로 탐색
int dy[3] = {0,-1, 0};  //  아래 방향은 탐색할 필요가 없다
int mapBackup[20][20];
int N,M,D,  num,removeCnt,ans;  //  N:행, M:열, D:거리
queue<pair<pair<int,int>, pair<int,int>>> q;    //  <cnt,아처위치,  y,x>
queue<pair<int,int>> qEnemy;    //  궁수가 쏠 적을 담는다
vector<int> archer; //  궁수의 위치를 넣는다 (벡터 원소는 M행에서 3개를 뽑는 조합을 이룬다, dfs에서 조합이 만들어짐)

void dfs(int);  //  완전탐색용 dfs
void bfs(void); //  궁수가 공격할 적을 택한다 (qEnemy에 넣는다, 자신에게 가장 가깝고 왼쪽에 있는 적을 택함, 궁수가 서로 똑같은 적을 택할 수 도 있음)
void removeEnemy(void); //  공격한 적을 없앤다 (qEnemy에서 꺼내서 지워주고 카운트 한다)
void moveDown(void);    //  적이 아래로 한칸 이동한다
int checkFinish(void);  //  게임이 끝났는지 확인한다 (적이 아예 없는지 검사)
void resetMap(void);    //  맵을 처음상태로 돌려준다 (완전탐색 1가지 경우가 끝나고 다시 다른경우를 탐색하기 위해)
void resetVisited(void);    //  방문기록,used정보(적을 택한 궁수 정보)를 지워준다

int main()
{
    int i,j;
    scanf("%d %d %d", &N,&M,&D);
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
        {
            scanf("%d", &map[i][j]);
            mapBackup[i][j] = map[i][j];
        }
    
    dfs(1); //  아처의 열 위치 index는 1부터 M까지 이므로 1로시작
    
    printf("%d", ans);
    
    return 0;   
}

void dfs(int index)
{
    int i;

    if( num==3 )
    {
        while(1)
        {
            bfs();  //  여기서 쏠 적을 qEnemy에 담아준다
            removeEnemy();  //  여기서 qEnemy에 있는 적을 쏜다 (중복을 알아서 피해주고 removeCnt 증가시켜줌)
            moveDown();
            if( checkFinish() )
            {
                ans = max(ans,removeCnt);
                removeCnt=0;
                resetMap();
                resetVisited();
                break;
            }
            resetVisited();
        }
    }
    
    for(i=index; i<=M; i++)
    {
        num++;   
        archer.push_back(i);
        
        dfs(i+1);   //  dfs(1~M+1)
        
        num--;
        archer.pop_back();
    }
    
}



void bfs()
{
    int i,  cnt,archInd,xx,yy,x,y;
    pair<pair<int,int>, pair<int,int>> popped;
    
    // 아처 위치의 바로 윗칸을 큐에 다 넣어준다
    for(i=0; i<(int)archer.size(); i++)
    {
        visited[N][archer[i]][i] = 1;
        q.push({ {1,i}, {N,archer[i]} });   
    }
    
    while( !q.empty() )
    {
        popped = q.front();
        q.pop();
        
        cnt = popped.first.first;
        archInd = popped.first.second;
        yy = popped.second.first;
        xx = popped.second.second;
    
        if( (map[yy][xx]==1)&&(used[archInd]==0) )
        {
            used[archInd] = 1;
            qEnemy.push({yy,xx});
            continue;
        }
        else if(used[archInd]==1)
            continue;   //  이미 앞전 큐에서 아처가 공격할 얘를 택했으므로.. 기존에 들어있던 큐는 무시하게 함
        
        for(i=0; i<3; i++)
        {
            x = xx + dx[i];
            y = yy + dy[i];

            
            if( (x>=1)&&(y>=1)&&(x<=M)&&(y<=N) )
            {
             
                if( (visited[y][x][archInd]==0)&&(cnt+1<=D) )
                {
                    visited[y][x][archInd] = 1;
                    q.push({{cnt+1,archInd},{y,x}});
                }
            }
        }
    }
}

void moveDown()
{
    int i,j;   
    
    for(i=N; i>=0; i--)
        for(j=1; j<=M; j++)
        {
            if(i==N)
                map[i][j]=0; 
            else if( map[i][j] == 1 )
            {
                map[i+1][j]=map[i][j];
                map[i][j]=0;
            }
        }
}
int checkFinish()
{
    int i,j;   
    
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
            if(map[i][j]==1)
                return 0;
    return 1;
}
void resetMap()
{
    int i,j;
    
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
            map[i][j]=mapBackup[i][j];
}
void resetVisited()
{
    int i,j,k;
    
    for(k=0; k<3; k++)
        for(i=1; i<=N; i++)
            for(j=1; j<=M; j++)
                visited[i][j][k]=0;
    
    for(i=0; i<20; i++)
        used[i]=0;
}
void removeEnemy()
{
    int x,y;
    pair<int,int> popped;
    
    while( !qEnemy.empty() )
    {
        popped = qEnemy.front();
        qEnemy.pop();
        
        y = popped.first;
        x = popped.second;
        
        if(map[y][x]==1)
        {
            map[y][x]=0;
            removeCnt++;
        }
    }
}
