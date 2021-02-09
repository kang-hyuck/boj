/* Bruteforce_17779, 게리맨더링 2 */
/* 포인트
  (브루트 포스)문제
  1. 대각선 그릴 때, for(i=x,j=y;  .... )이런 식으로 i,j 2개를 이동 가능
  2. 5구역 안에 채울때 BFS못쓰는 경우 있다. d1=1 or d2=1인 경우 대각선으로 못채움
   따라서, for(i=x,j=y,  ...)으로 대각선 따라서 이동하면서, k=1~...변수 하나 더 이용해서 "열"방향 인덱스에 더해주었다 !!!
*/

#include <iostream>
#include <string.h>  // memset()
#include <algorithm>  // sort(배열이름, 배열이름 + 배열크기)
using namespace std;

#define INF 987654321

int map[25][25];
int zone[25][25];
int N, ans;

void Start(void);
void Divide(int, int, int, int);
int CanDraw(int, int, int, int);
void CalAns(void);
void Reset(void);

int main()
{
    int i,j;

    // 입력부
    cin>>N;
    for(i=1; i<=N; i++)
        for(j=1; j<=N; j++)
            cin>>map[i][j];

    // 실행부
    ans=INF;
    Start();

    // 출력부
    cout<<ans;

    return 0;
}

void Start()
{
    int i,j,d1,d2;

    // 맵을 돌면서, 모든 위치에서 구역을 만들어본다 (브루트 포스)
    for(i=1; i<=N; i++)
        for(j=1; j<=N; j++)
            for(d1=1; d1<=N; d1++)
                for(d2=1; d2<=N; d2++)
                {
                    // 구역을 나눌 수 없는 경우
                    if( -1 == CanDraw(j,i,d1,d2) ) continue;
                    
                    // 구역을 나눌 수 있는 경우
                    Divide(j,i,d1,d2);  // zone 정보를 만든다
                
                    // 계산부
                    CalAns();  // zone 정보를 활용해서 구역의 (최댓값-최솟값) 계산

                    // 초기화
                    Reset();  // zone 정보 초기화
                }
    return;
}

int CanDraw(int y, int x, int d1, int d2){
    if( (x+d1+d2)>N || (y+d2)>N || (y-d1)<1 ) return -1;   // 맵을 벗어나는 경우
    else return 1;  // 맵을 벗어나지 않는 경우
}

void Divide(int y, int x, int d1, int d2)
{
    int i,j,k;

    // 5구역 나누기
    zone[x][y] = 5;
    for(i=x,j=y;  i<=x+d1&&j>=y-d1;  i++,j--) zone[i][j]=5;  // (왼쪽,위) 대각선
    for(i=x,j=y;  i<=x+d2&&j<=y+d2;  i++,j++) zone[i][j]=5;  // (오른쪽,위) 대각선
    for(i=x+d1,j=y-d1;  i<=x+d1+d2&&j<=y-d1+d2;  i++,j++) zone[i][j]=5;  // (왼쪽,아래)   대각선
    for(i=x+d2,j=y+d2;  i<=x+d1+d2&&j>=y-d1+d2;  i++,j--) zone[i][j]=5;  // (오른쪽,아래) 대각선

    // 5구역 채우기 ( (왼쪽,위) 대각선,  (오른쪽,아래) 대각선의 y방향으로 k=1~...를 더해준 곳에 5 채워 넣으면 된다)
    for(i=x+1,j=y-1;  i<=x+d1&&j>=y-d1;  i++,j--) for(k=1;  j+k<=N;  k++){if(zone[i][j+k]!=5)zone[i][j+k]=5;  else break;}
    for(i=x+d1,j=y-d1;  i<x+d1+d2&&j<y-d1+d2;  i++,j++) for(k=1;  j+k<=N;  k++){if(zone[i][j+k]!=5)zone[i][j+k]=5;  else break;}
    
    // 1~4구역 채우기
    for(i=1; i<=x+d1-1; i++)    for(j=1; j<=y; j++)   if(zone[i][j]==0) zone[i][j]=1;  // 1구역
    for(i=1; i<=x+d2; i++) for(j=y+1; j<=N; j++) if(zone[i][j]==0) zone[i][j]=2;  // 2구역
    for(i=x+d1; i<=N; i++) for(j=1; j<=y-d1+d2-1; j++)if(zone[i][j]==0) zone[i][j]=3;  // 3구역
    for(i=x+d2; i<=N; i++) for(j=y-d1+d2; j<=N; j++)if(zone[i][j]==0) zone[i][j]=4;  // 4구역
}

void CalAns()
{
    int i,j;
    int sum[6]={0,};

    // zone에 해당되는 map값 누적
    for(i=1; i<=N; i++) for(j=1; j<=N; j++) sum[zone[i][j]] += map[i][j];  // zone이 1~5까지 있으므로, 인덱스가 1~5까지 들어간다

    // 정렬 (오름차순)
    sort(sum, sum+6);   // 배열 "크기" 만큼 더하면 됨

    // 정답 갱신
    ans = min(ans, sum[5]-sum[1]);  // 0번 zone은 없으므로 sum[0]은 더미다
}

void Reset(){
    memset(zone, 0, sizeof(zone));  // zone 정보 지워줌
}

