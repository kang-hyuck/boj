#include <stdio.h>
#include <cstring>
#include <utility> // pair
#include <vector>
using namespace std;

#define f first
#define s second

char map[12][6];
int visited[12][6];
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};
int ans, cnt, blockbreak; // ans:정답, cnt:뿌요갯수, blockbreak:뿌요터짐 유/무
vector<pair<int,int>> v;

void dfs(int, int, char);  // 뿌요 연결 갯수 확인
void remove(void);  // 연결된 뿌요 제거 (dfs로 탐색할때 v에 뿌요 위치 저장 하던 것 이용 했음)
void down(void); // 공중에 있는 뿌요 발견시 내림

int main()
{
    int i,j;
    
    // 입력부
    for(i=0; i<12; i++)
        for(j=0; j<6; j++)
            scanf(" %c", &map[i][j]);


    // 실행부
    while(1)
    {
        for(i=0; i<12; i++)
        {
            for(j=0; j<6; j++)
                if(map[i][j]!='.') // 뿌요가 존재한다면 dfs로 연결상태를 확인한다.
                {
                    memset(visited, 0, sizeof(visited));
                    v.clear();
                    visited[i][j]=1;
                    cnt = 1; // 뿌요 갯수 카운트, 4개 이상이면 터트림
                    v.push_back({i,j}); // 뿌요 체크하는 블락의 위치들을 여기에 넣어 두었다가 4개 이상이면 지울때 사용할 것임
                    dfs(i,j, map[i][j]);
                    if(cnt >= 4)
                    {
                        blockbreak=1; // 뿌요가 터졌음을 표시해준다.
                        remove(); // 터져야할 뿌요들 제거해준다. v를 여기서 사용한다.
                    }            
                }
        }
        down(); // 처음에 4개이상 모여있는 뿌요들 다 터지고... 그다음에 여기서 떨어뜨릴 뿌요를 확인하여 내려준다.
        if(blockbreak==0) break; // 4개이상 모여서 터진 뿌요가 없었다면. 시뮬레이션 종료.
        else ans++; // 있었다면 연쇄횟수 증가.
        blockbreak=0;
    }


    // 출력부
    printf("%d",ans);
    

    return 0;
}


void dfs(int yy, int xx, char c)
{
    int i, y,x;
    
    for(i=0; i<4; i++)
    {
        y = yy + dy[i];
        x = xx + dx[i];
    
        if(y>=0 && x>=0 && y<12 && x<6)
        {
            if( c == map[y][x] && visited[y][x] == 0 )
            {
                v.push_back({y,x});
                visited[y][x]=1;
                cnt++;
                dfs(y,x, c);
            }
        }
    }
}

void remove()
{
    int y,x;
    
    while( !v.empty() )
    {
        y = v.back().f;       
        x = v.back().s;
        v.pop_back();
        
        map[y][x]='.';
    }
}

void down()
{
    int i,j, y;
    for(j=0; j<6; j++) // 열방향으로. 맨아랫행 부터 확인해서. 내려가야할 뿌요 있으면 while문으로 하나씩 끝까지 내린다.
    {
        for(i=10; i>=0; i--) // 밑에서 부터 내린다. 10부터 보면 된다.. 맨 바닥에 있는 뿌요는 내려갈곳이 없으므로.
        {
            if( map[i+1][j]=='.' && map[i][j]!='.' ) // 밑에 뿌요가 없는, 공중에 떠있는 뿌요 발견시.
            {
                y = i;
                while(1) // 쭉 내린다
                {
                    if( y==11 ) break; // 맨 밑에 오면 멈춤
                    if( map[y+1][j]!='.' ) break; // 아래 뿌요있으면 멈춤
                    
                    map[y+1][j] = map[y][j];  // 아래 칸에 뿌요이동
                    map[y][j] = '.'; // 뿌요 지나온 곳 지워준다.
                    y++; // 아랫행 인덱스로 이동.
                }
            }
        }
    }
}
