/* Sumulation_20057, 마법사 상어와 토네이도 */
#include <iostream>
using namespace std;

int N;
int dx[4] = {-1, 0, 1, 0};  // 좌,하,우,상
int dy[4] = {0,  1, 0,-1};
int percent[10] = {2,  10,7,1,  5,  10,7,1,  2,  100};  //
int blowX[4][10]={{0,  -1,0,1,  -2,  -1,0,1,  0,  -1},  // 좌
                  {-2, -1,-1,-1,  0,  1,1,1,  2,   0},   // 하
                  {0,   1,0,-1,   2,  1,0,-1,  0,  1},  // 우
                  {2,   1,1,1,   0,  -1,-1,-1,  -2, 0}};  // 상
int blowY[4][10]={{-2,  -1,-1,-1,  0,  1,1,1,  2,   0},  // 좌
                  {0,   1,0,-1,   2,   1,0,-1,  0,  1},  // 하
                  {2,    1,1,1,  0,  -1,-1,-1,  -2, 0}, // 우
                  {0,  -1,0,1,  -2,  -1,0,1,   0,  -1}};  //  상
int map[510][510];
int ans;

void Start(void);
void BlowSand(int, int, int);

int main()
{
    int i,j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>N;
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
            cin>>map[i][j];

    // 실행부
    Start();

    // 출력부
    cout<<ans;

    return 0;
}

void Start()
{
    int i, y,x, dir,len, cnt;

    // 맨처음 위치. 중앙 부터 시작.
    y=N/2;  x=N/2;
    dir=0;  len=1;  cnt=0;  // 초기방향은 0번 index, 이동길이 처음에 1칸,  길이만큼 이동한 횟수 카운트용
    while(1)
    {
        for(i=0; i<len; i++)
        {
            // 다음칸으로 이동
            y = y+dy[dir];   x = x+dx[dir];

            // 모래 날린다.
            BlowSand(y,x, dir);

            // 토네이도 종료조건 (도착지점에 도착한 경우.. 0,0에도 먼지 있을 수 있으므로 BlowSand 뒤에 넣어준다)
            if( y==0 && x==0 ) return;
        }
        // 방향 전환
        dir=(dir+1)%4;

        // 길이만큼 움직인 경우 카운트
        cnt++;

        // 길이만큼 2번 움직인 경우
        if(cnt==2)
        {
            // 다음에 이동길이 1 증가해준다
            len++;
            cnt=0;
        }
    }
}

void BlowSand(int yy, int xx, int dir)
{
    int i, y,x;
    int sand;

    sand = map[yy][xx];  // 각각의 위치로 날라간 모래 감소량을 여기에서 갱신해주고 나중에 한꺼번에 map에 갱신해야한다

    // 9개의 위치로 모래 날린다.
    for(i=0; i<9; i++)
    {
        // 모래가 날라갈 위치 확인.
        y=yy+blowY[dir][i];  x=xx+blowX[dir][i];

        // 맵 밖으로 모래가 날라간다면.
        if( y<0||x<0 || y>=N||x>=N )
        {
            ans += (map[yy][xx]*percent[i])/100;  // 정답에 더해줌
            sand -= map[yy][xx]*percent[i]/100;  // 먼지 날라갔으므로 빼줌
            continue;
        }

        // 맵 안으로 먼지가 이동 가능하다면 이동 시켜준다
        map[y][x] += map[yy][xx]*percent[i]/100;
        sand -= map[yy][xx]*percent[i]/100;
    }

    // 9개의 위치로 모래 날린후 위치에 남아있다면 모두 a 위치에 넣어준다.
    if(sand!=0)
    {
        y = yy+blowY[dir][9];  x = xx+blowX[dir][9];

        // 맵 밖으로 모래가 날라간다면.
        if( y<0||x<0 || y>=N||x>=N )
        {
            ans += sand;
            map[yy][xx]=0;
            return;
        }

        // 맵 안으로 모래가 이동한다면.
        map[y][x] += sand;  // a 위치로 남은 먼지 담아줌
        map[yy][xx]=0;  // 남아있던 먼지 지워줌
    }
}
