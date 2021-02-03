#include <stdio.h>
#include <utility> // pair
#include <queue>
#include <vector>
#include <cstring> // memset
using namespace std;

#define f first
#define s second

int map[110][110];
int checked[110][110]; // 1:치즈, 2:공기. "방문하지 않은 공기를 큐에 넣는다." 이 배열은 방문표시 용도. (1,2 값 큰 의미 없음. 디버깅용도.)
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};
queue<pair<int,int>> q;
vector<pair<int,int>> cheeze;
int R,C;
int ans1, ans2;

void bfs(void); // 외부 공기 정보가 들어있는 큐를 사용해서 녹여야할 치즈를 찾는다.
void remove(void); // 녹여야할 치즈를 녹이고 치즈 정보들을 비워준다.

int main()
{
    int i,j, temp;
    
    // 입력부
    scanf("%d %d", &R,&C);
    for(i=0; i<R; i++)
        for(j=0; j<C; j++)
        {
            scanf("%d", &temp);
            map[i][j]=temp;
        }
    
    // 맨 처음에 공기 위치 0,0을 큐에 담아준다.    
    checked[0][0]=2; // 공기 체크.
    q.push({0,0}); // 처음에 항상 이곳은 공기다.
    
    
    // 실행부
    while(1)
    {
        // 공기 위치에서 탐색해서, 녹일 치즈를 찾는다.
        bfs();
    
        // 녹일 치즈가 없다면 종료.
        if((int)cheeze.size() == 0 ) break;
    
        // 치즈 녹은 부분이 공기가 된다. 큐에 다 담는다.
        for(i=0; i<(int)cheeze.size(); i++)
            q.push({cheeze[i].f, cheeze[i].s});
        
        ans1++;
        ans2 = (int)cheeze.size();
        
        // 치즈 지워준다
        remove();

    }
    
    // 출력부
    printf("%d\n", ans1);
    printf("%d", ans2);
    
    
    return 0;   
}

void bfs()
{
    int i, y,x, yy,xx;
    
    while(!q.empty())
    {
        yy = q.front().f;
        xx = q.front().s;
        q.pop();
        
        for(i=0; i<4; i++)
        {
            y = yy + dy[i];
            x = xx + dx[i];
            
            if(y>=0 && x>=0 && y<R && x<C)
            {
                if(map[y][x]==0 && checked[y][x]==0) // 맵에서 0인데, 방문했던 공기가 아닐경우 큐에 넣음.(공기or구멍만나면 여기로 들어간다)
                {
                    checked[y][x]=2; // 공기 방문 표시.
                    q.push({y,x});
                }
                if(map[y][x]==1 && checked[y][x]==0) // 맵에서 1인데, 방문했던 (인접한)치즈가 아닐경우 큐에 넣음.
                {
                    checked[y][x]=1; // 치즈 방문 표시
                    cheeze.push_back({y,x}); // 방문했던 치즈(공기와 인접한 치즈, 녹여야할 치즈)를 찾았으므로 벡터에 위치를 넣는다
                } 
            }
        }
    }
}

void remove()
{
    int i, y,x;
    for(i=0; i<(int)cheeze.size(); i++)
    {
        y = cheeze[i].f;
        x = cheeze[i].s;
        
        checked[y][x]=2; // 공기로 바꿔준다
    }
    
    cheeze.clear(); // 녹일 치즈 정보 담았던 내용을 전부 비워준다.
}
