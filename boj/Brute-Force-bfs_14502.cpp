#include <stdio.h>
#include <utility>  //  pair
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

/****************************************************************************
벽 3개를 세울 때.. 1번째 벽, 2번째 벽, 3번째 벽 사이에는
dfs에서 호출순서에 따라 부모함수, 자식함수로 나뉘어 지는데..
이것을 착안해서 이중for문에서 벽세울때... 중복되는 경우를 빼주어야
시간초과를 없앨 수 있다.

예)
두번째 벽이 첫번째 벽이 지나온 경우를 다시 가는 경우:  001110 -> 001101 -> 10101
어차피 맨왼쪽 자리는 첫번째 벽이 처음에 세워졌던 곳인데.. 위의 상황처럼 두번째 벽이
다시 거기서부터 채워질 이유가 없다... 이렇게 중복되어 버리는 경우를 피하기 위해서!!

"1,2,3번째 벽사이에는 부모,자식호출 관계가 있다"는 것을 착안하면 된다

따라서 인자로 par_y, par_x 로 부모벽이 세워진 위치를 파악하고,
compare함수!! 에서 자식의 벽이 세워져도 되는 위치인지 판단 하도록 한다.
(부모벽 보다 x값이 크거나, y값이 크면 자식벽이 세워져도 된다.. OR)

이렇게 해야 시간초과를 피할 수 있다.
(사실 N,M이 8x8 밖에 안되서 시간초과가 안날 수도 있을 것 같긴 함)
*****************************************************************************/

void dfs(int ,int, int);
void copy_map(void);
void reset_map(void);
void bfs(void);
void count(void);
void input_virus(void);
int compare(int, int, int, int);    //  이게 이 문제의 핵심 (벽3개 위치의 중복된 경우의 수를 피할 수 있음)

int visited[15][15];
int map[15][15];
int map_backup[15][15];
int dx[4] = {1,-1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int N,M,    max_cnt;    //  N:세로,  M:가로
queue<pair<int,int>> q;     // <y,x>
vector<pair<int,int>> virus;    //  reserve 어떻게 쓰더라?

int main()
{
    int i,j,    input;

    scanf("%d %d", &N,&M);

    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
        {
            scanf("%d", &input);
            map[i][j] = input;
            if(input == 2)
                virus.push_back(pair(i,j)); //  virus 위치 저장
        }

    dfs(0,1,1);

    printf("%d", max_cnt);

    return 0;   
}

void dfs(int num,   int par_y, int par_x)
{
    int i,j;

    if(num == 3)
    {
        copy_map();
        input_virus();  //  queue에 virus 위치를 넣어줌
        bfs();
        count();
        reset_map();

        return;
    }

    for(i=1; i<=N; i++)
    {
        for(j=1; j<=M; j++)
        {
            if((map[i][j] == 0)&&(compare(par_y,par_x, i,j)))
            {
                map[i][j] = 1;
                dfs(num+1, i,j);
                map[i][j] = 0;         
            }
        }
    } 
}

void copy_map()
{
    int i,j;

    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
            map_backup[i][j] = map[i][j];
}

void reset_map()
{
    int i,j;

    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
        {
            map[i][j] = map_backup[i][j];
            visited[i][j] = 0;
        }
}

void bfs()
{
    pair<int,int> popped;
    int i,  yy,xx,  y,x;

    while( !q.empty() )
    {
        popped = q.front();
        q.pop();

        yy = popped.first;
        xx = popped.second;

        for(i=0; i<4; i++)
        {
            y = yy + dy[i];
            x = xx + dx[i];

            if( (x>=1)&&(y>=1)&&(x<=M)&&(y<=N) )
            {
                if( (visited[y][x]==0)&&(map[y][x]==0) )
                {
                    visited[y][x] = 1;
                    map[y][x] = 2;
                    q.push(pair(y,x));
                }
            }
        }
    }
}

void count()
{
    int i,j,    cnt; 
    cnt = 0;

    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
        {
            if( map[i][j] == 0 )
                cnt++;
        }

    max_cnt = max(max_cnt, cnt);  
}

void input_virus()
{
    int i,  y,x;
    for(i=0; i<(int)virus.size(); i++)
    {
        y = virus[i].first;
        x = virus[i].second;
        q.push(pair(y,x));
    }
}

int compare(int y, int x, int yy, int xx)
{    
    if( y<=yy ) return 1;
    if( x<=xx ) return 1;
    return 0;
}
