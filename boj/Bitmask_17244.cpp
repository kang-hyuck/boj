/* Bitmask_17244, 아맞다우산 */
/* 포인트
 X로 다 똑같이 표현되는 물건들을 "구분 될 수 있도록" 바꾸어 주어야 한다.
 Bitmask를 사용하려면. 각 bit 위치마다 고유의 구분 값을 가지므로. 다 똑같은
 X도 고유한 문자값으로 구분해주어서 고유한 bit 위치에 상태정보가 표현 될 수 
 있도록 바꾸어 주어야 하는게 핵심이다.
 map에 'a'+(숫자)로 a~e를 만들어주어서 각각의 물건이 고유한 물건이 되도록 바꾸어주었다.
 물건 보유 상태에 따라서 방문 표시(visited)를 다르게 해주는 것도 포인트. 
*/
#include <iostream>
#include <queue>
#include <tuple>  // tie()
using namespace std;

char map[55][55];
char visited[55][55][35];  // 물건 갯수 최대 5개 -> 물건 보유 상태 최댓값 2^5=32
int dx[4]={1, -1, 0, 0};
int dy[4]={0,  0, 1,-1};
queue<tuple<int,int,int,int>> q;  // y,x,state, cnt

int N,M;  // 가로,세로
int ans, itemCnt, item;  //  물건 갯수, 물건 갯수 상태 표현

void BFS(void);

int main()
{
    int i,j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>N>>M;
    for(i=1; i<=M; i++)
        for(j=1; j<=N; j++)
        {
            cin>>map[i][j];
            if(map[i][j]=='S'){q.push({i,j,0,0}); visited[i][j][0]=1;}  // 시작위치 큐에 넣어준다
            if(map[i][j]=='X'){map[i][j] = 'a'+ itemCnt;  item |= (1<<(itemCnt++));}  // 물건을 a,b,c,d,e 순으로 맵에 표시, item 변수에 해당 비트 표시 해준다.
        }

    // 실행부
    BFS();

    // 출력부
    cout<<ans;

    return 0;
}

void BFS()
{
    int i, y,x, yy,xx, st,cnt;

    while(!q.empty())
    {
        tie(yy,xx,st,cnt) = q.front();
        q.pop();

        // 종료 조건
        if(map[yy][xx]=='E' && item==st){ans=cnt; return;}   // 출구에 도착 && 물건을 주어진 만큼 모두 보유한 경우

        for(i=0; i<4; i++)
        {
            y = yy + dy[i];  x = xx + dx[i];

            // 다음 위치로 이동할 수 없는 경우
            if(y<1 || x<1 || y>M || x>N) continue;  // 맵 벗어나는 경우 넘긴다 (이거 안넣으면 E에 벽이 없는데, 물건을 다 갖지 않은 상태라면...  맵 인덱스 벗어나서 이동할 수 있음)
            if(map[y][x]=='#') continue;  // 벽인 경우 넘긴다
            if(visited[y][x][st]==1) continue;  // 방문 했던 경우 넘긴다

            // 방문표시 
            visited[y][x][st]=1;

            // 큐에 넣는다
            if('a'<=map[y][x] && map[y][x] <= 'a'+4)  // 물건일 경우 (물건은 최대 5개 이하다)
                q.push({y,x, st | (1<<(map[y][x]-'a')),cnt+1});  // 물건 챙긴 상태를 표시 해줌
            else
                q.push({y,x, st,cnt+1});
        }
    }
}
