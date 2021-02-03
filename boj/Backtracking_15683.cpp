/* Backtracking_15683, 감시 */
/* 포인트
  1. "방향에 대한 상태"를 R,L,U,D "비트맵" 활용 했다
     (테트로미노는 "칸"의 위치를 알아야 해서.. 3차원 배열 사용해서 인덱스를 다 써주었는데,
     이 경우는 y,x 위치가 아니라서 3차원 배열을 사용해도 되고 비트맵을 사용해도 된다)
  2. 배열[cctv 종류][방향 경우의 수] 로 2차원 배열을 사용하였다.
     "방향의 경우의 수" 부분이 cctv의 종류마다 달라서 vector 사용했다
  3. map에다가 cctv가 감시하는 부분을 그렸다가 "지우는 과정"에서 다른 cctv에서
     감시하는 부분까지 지워질 수 있다. 그래서 지우는 과정은. 지우는 대신 맵을 "복원" 하는식으로 처리했다
  4. DFS의 인자로 들어가는 경우
   - 1.그래프에서 이동시, 고유의 노트를 표현 하기 위한 값
   - 2.(~까지 선택/~까지 해결) 해야 하는 경우. 갯수를 넣어줌
*/
#include <iostream>
#include <vector>
#include <tuple>  // tie()
using namespace std;

#define R (1<<0)
#define L (1<<1)
#define U (1<<2)
#define D (1<<3)

typedef struct cctv{
    int y,x, num;
}cctv;

// 2차원 사용 - [cctv종류][방향] = (방향상태)
vector<int> cctvDir[6] = {
    {},                     // 0 (더미)
    {R, L, U ,D},           // 1번 cctv
    {R|L,  U|D},            // 2번 cctv
    {R|U,  U|L,  L|D,  D|R},// 3번 cctv
    {R|U|L,  U|L|D,  L|D|R,  D|R|U},  // 4번 cctv
    {R|U|L|D}               // 5번 cctv
};
vector<cctv> cctvInfo;

int dx[4] = {1,-1,  0, 0};  // R,L,U,D
int dy[4] = {0, 0, -1, 1};
int map[15][15];
int N,M,  ans;

void DFS(int);
void DrawMap(cctv, int);
void CheckAns(void);
void BackupMap(int [15][15]);   // 2차원 배열 [][15]임을 의미
void RestoreMap(int [15][15]);

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
            if(map[i][j]==0) ans++;  // 0 갯수 카운트
            if(map[i][j]!=0 && map[i][j]<=5)  cctvInfo.push_back({i,j, map[i][j]});  // CCTV 정보 저장
        }
    
    // 실행부
    DFS(0);  // 선택한 갯수 0

    // 출력부
    cout<<ans;

    return 0;
}

void DFS(int cnt)
{
    int i, num;
    int backup[15][15] = {0,};

    // 종료 조건
    if(cnt==(int)cctvInfo.size()){CheckAns(); return;}  // cctv 모두 선택해서 그릴 때마다 정답 확인 및 종료
    
    // 다음 자식 노드 호출
    num = cctvInfo[cnt].num;  // 현재 cctv의 번호 저장
    for(i=0; i<(int)cctvDir[num].size(); i++)   // 해당 cctv의 조사방향 경우의 수 만큼 각각 그렸다가/지웠다가 반복 해준다
    {
        BackupMap(backup);
        DrawMap(cctvInfo[cnt],  cctvDir[num][i]);  // (해당 cctv 위치정보, cctv 방향 경우의 중 택한 것 1개, 맵에 9 그림)
        DFS(cnt+1);
        RestoreMap(backup);
    }
}

void DrawMap(cctv cctv1, int dir)
{
    int i, y,x,yy,xx;

    tie(yy,xx) = {cctv1.y, cctv1.x};
    
    // 포함된 방향정보에 따른 이동
    for(i=0; i<4; i++)
    {
        // 초기위치
        y = yy;  x = xx;
    
        // 해당 방향이 포함 된 경우
        if( (1<<i) & dir ) 
        {
            while(1)
            {
                // 이동할 위치 계산
                y = y + dy[i];   x = x + dx[i];
            
                // 해당 위치로 이동할 수 없는 경우
                if(y<1 || x<1 || y>N || x>M)  break;  // 맵을 벗어나는 경우
                if(map[y][x]==6) break;  // 벽인 경우
                
                // 해당 위치로 이동할 수 있는 경우
                if(1<=map[y][x] && map[y][x]<=5) continue;  // cctv인 경우 맵에 안그린다
                map[y][x] = 9;    // 맵에 그려준다
            }
        }
    }
}

void CheckAns()
{
    int i,j, cnt=0;
    
    // map에서 0인 곳을 센다
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
            if(map[i][j]==0) cnt++;

    // 정답(ans) 값 갱신
    ans = min(ans,cnt);
}

void BackupMap(int backup[15][15])
{
    int i,j;
    
    // map 정보를 backup에 저장한다
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
            backup[i][j] = map[i][j];
}

void RestoreMap(int backup[15][15])
{
    int i,j;
    
    // backup 정보를 map에 저장한다
    for(i=1; i<=N; i++)
        for(j=1; j<=M; j++)
            map[i][j] = backup[i][j];
}
