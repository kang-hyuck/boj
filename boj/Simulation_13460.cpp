/* Simulation_13460, 구슬탈출2  */
/* 포인트
 BFS는 "맵 갱신"하면 안된다. 큐에서 나오는 애들마다 같은 맵 정보 사용하므로.
 맵을 갱신하는 대신 BFS는  큐에 넣을 때" 자신의 위치정보"를 넣어주면 된다
 따라서 구슬 2개의 "위치정보"가 큐에 들어가주어야 한다. 그런데 큐에 넣을 때
 y,x 일일히 넣어주면 헷갈리고 귀찮으니까... 구조체로 만들어서 넣어주었다  
 시뮬레이션(구슬이동)하는 함수가 호출 될 때 이동한 결과값을 다시 위치정보에
 갱신해주어야 하므로 함수 인자값에 "포인터"를 사용하였다.
 구슬끼리 부딪힐때도 이동을 멈추어야 하므로 이동하려는 구슬 말고 다른 구슬의
 위치정보도 함수 인자에 넣어주어야 한다. 
 O에 도착하면 구슬의 위치를 맵 밖으로 빼주어야 한다 (위치 정보 갱신 필요)
 그리고.. tie() = (구조체) 형식으로는 사용할 수 없고 대신 대신 tie() = {구조체.멤버변수, 구조체.멤버변수2}; 로는 사용 가능하다
 서로의 구슬 위치에 따라서 먼저 시뮬레이션할 구슬 순서를 고려해야한다
*/
#include <iostream>
#include <queue>
#include <tuple>  // tie()
using namespace std;

typedef struct bead
{
    int y,x;
}bead;

bead  redBead, blueBead;  // 빨간구슬 정보, 파란구슬 정보

queue<tuple<bead,bead, int,int>>  q; // <빨간구슬 정보, 파란구슬 정보,   방향,카운트>
int dx[4] = {1, -1, 0, 0};  // 우,좌,하,상
int dy[4] = {0,  0, 1,-1};
int visited[15][15][15][15];  // 빨간구슬 위치, 파란구슬 위치 DP값
char map[15][15];
int N,M,  ans;

void BFS(void);
int Move(bead *, bead,  int);  // (움직이려는 구슬, 다른 구슬, 방향)  1:구슬이 'O'에 들어간경우,  0:구슬이 #,구슬 만나서 멈춘 경우

int main()
{
    int i,j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>N>>M;
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
        {
            cin>>map[i][j];
            if(map[i][j]=='R') redBead  = {i,j};   // 구조체 멤버 변수에 {,}로 값 넣어줄 수 있다.
            if(map[i][j]=='B') blueBead = {i,j};
        }
    // 초기화 (구슬 초기 위치, 4방향 넣어줌)
    visited[redBead.y][redBead.x][blueBead.y][blueBead.x]=1;
    for(i=0; i<4; i++)
        q.push({redBead,blueBead, i,1});  // 구슬의 초기 위치와 시뮬레이션 할 4방향 넣어준다.
    ans=-1;
    
    // 실행부
    BFS();
    
    //출력부
    cout<<ans;
   
    return 0;
}

void BFS()
{
    bead beadRed,beadBlue;
    int i, dir,cnt;
    int resRed,resBlue;  // beadRed, beadBlue에 대한 시뮬레이션 결과 저장.

    while( !q.empty() )
    {
        tie(beadRed,beadBlue, dir,cnt) = q.front();
        q.pop();
     
        // 종료 조건
        if(cnt >= 11){ans=-1; return;}  // 11번 이상인 경우. 큐에서 최초로 11 이상인 cnt 나오면 종료 시키면 됨
        
        // 구슬 위치에 따른 시뮬레이션 순서 정하기 (방향에 따른 빨간색 구슬, 파란색 구슬 중 먼저 이동해야할 순서 정하는 부분)
        if( (dir==0 && beadRed.x > beadBlue.x) || (dir==1 && beadRed.x < beadBlue.x) || (dir==2 && beadRed.y > beadBlue.y) || (dir==3 && beadRed.y < beadBlue.y) )
        {
            resRed  = Move(&beadRed, beadBlue, dir);  // 해당 방향으로 시뮬레이션 해본다
            resBlue = Move(&beadBlue,beadRed,  dir);
        }
        else
        {
            resBlue = Move(&beadBlue,beadRed,  dir);
            resRed  = Move(&beadRed, beadBlue, dir);
        }
        
        // 시뮬레이션 결과 확인
        if( 1 == resBlue ) continue;  // 파란 구슬이 'O'에 들어간 경우
        if( 1 == resRed  ){ans=cnt; return;}  // 빨간 구슬이 'O'에 들어간 경우   

        // 방문 한적이 있다면 큐에 안넣고 넘긴다. 큐에 불필요하게 들어가는 크기 줄이려고 사용
        if(visited[beadRed.y][beadRed.x][beadBlue.y][beadBlue.x]==1) continue;
        visited[beadRed.y][beadRed.x][beadBlue.y][beadBlue.x]=1;

        // 구슬 이동 후 특별한 결과 없는 경우 변한위치와 다음 시뮬레이션 방향 넣어줌
        for(i=0; i<4; i++)
            q.push({beadRed,beadBlue,  i,cnt+1});
    }
}

int Move(bead * beadInfo, bead beadOther,  int dir)  
{
    int y,x, yOther,xOther;
    
    // 구슬 좌표값 꺼내온다
    tie(y,x) = {beadInfo->y, beadInfo->x};  // tie(y,x) = (구조체) 는 안된다.. ㅠ.ㅠ
    tie(yOther,xOther) = {beadOther.y, beadOther.x};  // 다른 구슬 정보 가져온다.. 다른 구슬 있는 위치로 부딪힐때 멈추기위해서.
    
    // 구슬 이동
    while(1)
    {
        // 이동할 위치 갱신
        y = y + dy[dir];   x = x + dx[dir];
        
        // 이동할 위치 확인
        if(map[y][x]=='#' || (yOther==y && xOther==x) )  // 이동할 수 없는 경우 (벽 있는 경우 && 다른 구슬 있는 경우)
        { 
            beadInfo->y= y-dy[dir];  beadInfo->x= x-dx[dir];  // 이동 위치 갱신
            return 0;
        }
        if(map[y][x]=='O') // 구멍인 경우
        {
            beadInfo->y= 0;  beadInfo->x= 0;  // 구슬을 맵 밖으로 빼준다 (구슬 위치 정보 0,0으로 갱신)
            return 1;  // 구멍에 들어갈 경우
        }
    }
}
