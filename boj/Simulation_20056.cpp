/* Simulation_20056, 마법사 상어와 파이어볼 */
#include <iostream>
#include <vector>
using namespace std;

int N,M,K;  // N:맵 크기, M:파이어볼 갯수, K:이동 횟수
int ans;

int dx[8] = {0, 1, 1, 1,   0, -1, -1, -1};
int dy[8] = {-1,-1,0, 1,   1,  1,  0, -1};

typedef struct fireInfo
{
    int m,s,d;
}fireInfo;

vector<fireInfo> map[60][60];
vector<fireInfo> check[60][60];  // 파이어볼 (이동, 쪼개진 것)을 여기에서 처리하고 결과를 map에 옮겨 그릴 것임.

void Start(void);
void MoveFire(int, int);
void BreakFire(int, int);

int main()
{
    int i,j,k, tmp1,tmp2,tmp3,tmp4,tmp5;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>> N >> M >> K;
    for(i=0; i<M; i++)
    {
        // 맵의 해당 위치 벡터에 파이어볼 넣어줌
        cin >>tmp1>>tmp2>>tmp3>>tmp4>>tmp5;
        map[tmp1][tmp2].push_back({tmp3,tmp4,tmp5});
    }
    
    // 실행부
    Start();
    
    // 출력부
    for(i=1; i<=N; i++)
        for(j=1; j<=N; j++)
            if(!map[i][j].empty())
                for(k=0; k<(int)map[i][j].size(); k++)
                    ans += map[i][j][k].m;
    cout<<ans;
 
    return 0;
}

void Start()
{
    int i,j,k;

    while( K-- )
    {
        // 파이어볼 이동
        for(i=1; i<=N; i++)
            for(j=1; j<=N; j++)
            {
                // 파이어볼 있는 경우 이동
                if( !map[i][j].empty() ) MoveFire(i,j);
            }
        
        // 파이어볼 이동 끝난후. 파이어볼 2개 이상인 곳 확인.
        for(i=1; i<=N; i++)
            for(j=1; j<=N; j++)
            {
                // 파이어볼 갯수가 2개 이상인 경우
                if( 2 <= (int)check[i][j].size() ) BreakFire(i,j);
            }
        
        // 파이어볼 정보 갱신 한것을 map에 넣어준다. check 다음실행때 사용할거라 비워준다.
        for(i=1; i<=N; i++)
            for(j=1; j<=N; j++)
            {
                map[i][j].clear();  // map에 있는 것부터 비운다
                if(!(int)check[i][j].empty())  // check에 있는 것을 map에 옮겨준다
                    for(k=0; k<(int)check[i][j].size(); k++)
                        map[i][j].push_back(check[i][j][k]);
                check[i][j].clear();  // check에 있는거 비운다
            }
    }
}

void MoveFire(int yy, int xx)
{
    int y,x, m,s,d;
    fireInfo fire;
    
    // 위치에 들어있는 파이어볼 모두 꺼내서 이동 시켜준다.
    while(!map[yy][xx].empty())
    {
        // 파이어볼 정보 하나 꺼낸다
        fire = map[yy][xx].back();
        map[yy][xx].pop_back();
        
        m = fire.m;  s = fire.s;  d = fire.d;
        y = yy;   x = xx;
        
        // 파이어볼 이동 시킨다. 방향으로 속력 만큼 1씩 이동 해준다
        while(s--)
        {
            y = y+dy[d];  x = x+dx[d];
            
            // 맵 벗어나는 경우. 맵의 1과 N 부분이 연결되어 있으므로 넘어간다.
            if( y<1 ) y=N;
            else if( y>N ) y=1;
            if( x<1 ) x=N;
            else if( x>N ) x=1;
        }
        
        // 최종 위치에 파이어볼 넣어준다. check에 넣어놓고 나중에 map에 한꺼번에 갱신할 것임
        check[y][x].push_back({m, fire.s, d});
    }

}

void BreakFire(int yy, int xx)
{
    int i, m,s,d,ans1,ans2;
    m=0; s=0; d=0; ans1=0; ans2=0;
    
    
    // 쪼갠 파이어볼들의 새로운 질량,속력,방향 계산
    for(i=0; i<(int)check[yy][xx].size(); i++)
    {
        m += check[yy][xx][i].m;
        s += check[yy][xx][i].s;
        if(check[yy][xx][i].d%2 != 0) ans2=1; // 1: 홀수방향만 있는 경우가 아님을 의미
        if(check[yy][xx][i].d%2 != 1) ans1=1; // 1: 짝수방향만 있는 경우가 아님을 의미
    }
    m=m/5;
    s=s/(int)check[yy][xx].size();
    if(ans1==0 || ans2==0) d=0; // 홀수,짝수 방향만 있는 경우가 있었다면. 방향값 0으로. (나중에 2씩 더할 거임)
    else d=1; // 홀수,짝수 방향만 있는 경우가 아니였다면 방향값 1로 
    
    // 파이어볼 정보 갱신
    check[yy][xx].clear();  // 기존 파이어볼 정보 전부 지워줌
    if(m==0) return;  // 질량 0 이면 소멸 후 종료
    
    // 4개 나눠서 넣어줌
    for(i=0; i<4; i++)
    {
        check[yy][xx].push_back({m,s,d});    
        d=d+2;
    }   
}

