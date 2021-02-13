/* 원판 돌리기 */
/* 포인트
 1. "원"을 덱으로 구현하면, 0번 index랑 마지막 index가 서로 이어져 있음을 착안 해야한다.
 2. 범위 조사할 때. 같은 원 내에서는 이어져 있으므로 지울 수 있는 지  확인 해야한다
*/

#include <iostream>
#include <deque>
#include <string.h>  // memset()
using namespace std;

int N,M,T,  xi,di,ki,  removeFlag, ans;
deque<int> pan[55];
int map[55][55];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0,  0, 1,-1};

void Start(void);
void Rotate(int, int, int);
void Remove(void);
void Check(int, int);
void Average();

int main()
{
    // 입력부
    int i,j, temp;
    
    cin>>N>>M>>T;
    for(i=1; i<=N; i++) for(j=0; j<M; j++){cin>>temp;  pan[i].push_back(temp);}  // 1~N 원판에 번호 넣는다
        
    // 실행부
    Start();
    
    // 출력부
    for(i=1; i<=N; i++) for(j=0; j<M; j++) ans += pan[i][j];
    cout<<ans;
    
    return 0;
}

void Start()
{
    int i;

    while(T--)
    {
        // 회전 해야하는 정보 받는다
        cin>>xi>>di>>ki;
        
        // 회전
        for(i=xi; i<=N; i+=xi)  Rotate(i, di, ki);  // i번째 판을 di방향으로 ki칸 회전
        
        // 인접한 숫자 지우기
        Remove();
        
        // 초기화
        memset(map, 0, sizeof(map));
    }
}

void Rotate(int num, int dir, int cnt){
    int temp;
    
    // 회전
    while(cnt--){
        if(dir==0){ temp = pan[num].back();  pan[num].pop_back();  pan[num].push_front(temp);}  // 시계방향
        else{ temp = pan[num].front();  pan[num].pop_front();  pan[num].push_back(temp);}  // 반시계방향
    }
}

void Remove()
{
    int i,j;

    // 모든 위치를 돌면서 지울 수 있는 숫자를 찾는다 (pan에 값 갱신 해야하는 부분 찾기)
    for(i=1; i<=N; i++) for(j=0; j<M; j++) Check(i,j);

    // 플래그 값 초기화
    removeFlag=0;

    // 판마다 돌면서 지워야 하는 부분을 지워준다 (pan에 값 갱신하는 부분)
    for(i=1; i<=N; i++){  
        // 원소들 조사 및 제거
        for(j=0; j<M; j++) if(map[i][j]!=0){removeFlag=1; pan[i][j]=0;}
    }
    
    // 판에서 지울 숫자가 있는 경우
    if(1==removeFlag) return;
    
    // 판에서 지울 숫자가 없는 경우
    Average();  // 평균 값 갱신        
}

void Check(int yy, int xx)
{
    int i,y,x,  val;

    // 현재 위치의 "값" 선택
    val = pan[yy][xx];

    // 4방향 조사
    for(i=0; i<4; i++)
    {
        // 조사할 위치 선택
        y = yy+dy[i];  x = xx+dx[i];
        
        // 범위를 벗어나는 경우 (반대쪽도 확인 해야한다)
        if( y<1 || x<0 || y>N || x>=M){
            if(y<1) continue; 
            else if(y>N)  continue;  // 다른 판으로 넘어가는 방향으로는 index 넘어가도 조사 하지 않는다
            else if(x<0)  x=M-1;   // 옆으로는 index 넘어가면 같은 판에서 서로 이어져 있으므로. (원이니까... ) 조사해야한다
            else if(x>=M) x=0;
        }
    
        // 지울 것임을 표시 해준다
        if(val!=0 && pan[y][x]==val){removeFlag=1;  map[y][x]=1;  map[yy][xx]=1;}  // !!! val이 0인 경우는 removeFlag 1하면 안된다!!
    }
}

void Average()
{
    int i,j, sum=0, cnt=0;
    double avg;

    // 모든 숫자를 더한다
    for(i=1; i<=N; i++) for(j=0; j<M; j++){sum += pan[i][j];  if(pan[i][j]!=0) cnt++; }
    
    // 평균 구함
    avg = (double)sum/(double)cnt;
    
    // 평균이랑 비교해서 +1,-1 해줌
    for(i=1; i<=N; i++) for(j=0; j<M; j++){if(pan[i][j]==0)continue;  if(pan[i][j]>avg)pan[i][j]--; else if(pan[i][j]<avg) pan[i][j]++;}
}
