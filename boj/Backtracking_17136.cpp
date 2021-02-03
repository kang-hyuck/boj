/* Backtracking_17136, 색종이 붙이기 */
/* 포인트
 1. 1인 칸이 해결될 때까지 다음칸으로 이동하면 안된다. 해결하는 이동모양에서 "스도쿠 문제" 착안해서 positionCnt 사용해서 yy,xx계산했다
    positionCnt 사용하면 매번 DFS 내에서 2중for문으로 맵 또 돌면서 1인 곳 찾는 코드 짜야하는거 피할 수 있다 (실수할 확률 높아짐)
 2. 자식노드 호출 부분에서 "해당위치에 붙일 색종이 경우의 수"를 for문 돌면서 모두 확인 해봤다.
    해당 위치에서 붙일 수 있는지 5가지 경우를 확인한 거다. 마치 "다음위치"로 이동할 수 있는지 if문 같은 것으로 검사하는 것과 같다.
    이 경우 다른점은 "전역변수 map"에 변화를 그려놓고!!(색종이 선택한거 반영해놓고) 자식노드로 이동했다는 점이다. 그냥 이동한게 아니다.
 3. 전역변수 oneCnt를 이용해서 "DFS종료 조건"을 만들어 주었다. 무조건 DFS인자에 있는 값만으로 DFS를 종료하지 않아도 될 듯
    왜냐면 DFS 깊어질 때마다 "전역변수"인 map에 그려놓고 지나가기 때문에 똑같이 전역변수인 oneCnt 값도 갱신 해서 종료해도 된다
    종료조건(가지치기)은 많이 넣으면 넣을 수록 좋은 것 같다. 다만 "순서"를 조심해햐할 듯. 예로 ans 갱신위치가 더 앞에 있어야한다.
*/
#include <iostream>
#include <algorithm>  // min()
using namespace std;

int map[15][15];
int oneCnt;  // 1 갯수 (색종이로 붙여야 하는 곳의 갯수)
int ans;  // 사용한 색종이 갯수
int paper[5] = {5,5,5,5,5};  // 5개 존재
int paperArea[5] = {1,4,9,16,25};  // 색종이 넓이
int paperSize[5] = {1,2,3,4,5};  // 색종이 크기

void DFS(int, int);  // 해당 칸이 해결 될 때까지. 이동할 수 없다. 만약 끝까지 못가면 -1 반환하면 됌
int CanPaste(int, int, int);   // 색종이 붙일 수 있는지 확인  (확인할 위치, 색종이크기)
void PastePaper(int, int, int);   //  색종이 붙임   (붙일 위치, 색종이 크기)
void DetachPaper(int, int, int);  //  색종이 떼냄   (떼낼 위치, 색종이 크기)

int main()
{
    int i,j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    for(i=0; i<10; i++)
        for(j=0; j<10; j++)
        {
            cin>>map[i][j];
            if(map[i][j]==1) oneCnt++;
        }
    ans = -1;

    // 실행부
    DFS(0, 0);

    // 출력부
    cout<<ans;

    return 0;   
}

void DFS(int positionCnt, int cnt)
{
    int i, y,x, yy,xx;

    // 종료 조건
    if(oneCnt==0 && ans==-1){ans = cnt;}  // 정답갱신 부분
    else if(oneCnt==0 && ans != -1){ans = min(ans,cnt);}
    if(positionCnt==100) return;  // 맨 오른쪽 아래 칸에 도착한 경우
    if(ans!=-1 && ans<cnt) return;  // ans보다 색종이 사용횟수가 많다면 종료

    // 현재 위치 계산
    yy = positionCnt/10;  xx = positionCnt%10;

    // 5개 종이 각각의 경우의 수 확인
    if(map[yy][xx]==1)  // 색종이 붙여야 하는 경우 (맵이 1인 경우)
        for(i=0; i<5; i++)
        {
            // 종이 붙였을 때 오른쪽아래 모서리 위치 (왼쪽 위에서 오른쪽 아래로 진행하므로... 이 위치 범위 확인 필요)
            y = yy + i;  x = xx + i;

            // 붙일 수 없는 경우
            if(y<0 || x<0 || y>9 || x>9) continue;  // 맵 범위 벗어나는 경우
            if( paper[i] == 0 ) continue;  // 해당 색종이를 다 사용한 경우
            if( -1 == CanPaste(yy,xx,paperSize[i]) )  continue;  // 현재 위치에 해당 색종이를 붙일 수 없는 경우 (색종이 넓이 중간에 0 있는 경우)

            // 붙일 수 있는 경우
            paper[i]--;   // 해당 색종이 사용가능 갯수 감소
            PastePaper(yy,xx,paperSize[i]);   // 색종이 붙인다
            oneCnt -= paperArea[i];   // 색종이 붙여야 하는 곳 갯수 감소

            DFS(positionCnt+1, cnt+1);  // 다음 위치로 이동 및 사용한 색종이 갯수 카운트

            oneCnt += paperArea[i];  // 색종이 붙여야 하는 곳 갯수 증가
            DetachPaper(yy,xx,paperSize[i]);  // 색종이 떼낸다
            paper[i]++;  // 해당 색종이 사용가능 갯수 증가
        }
    else  // 색종이 붙일 필요 없는 곳인 경우 (맵이 0인 경우)
    {
        DFS(positionCnt+1, cnt);  // 다음위치로 이동
    }   
}

int CanPaste(int yy, int xx, int s)
{
    int i,j;

    // 색종이를 붙이려는 범위 내에 0이 있으면 -1 반환
    for(i=yy; i<yy+s; i++)
        for(j=xx; j<xx+s; j++)
            if(map[i][j]==0) return -1;

    // 색종이를 붙일 수 있는 경우
    return 1;
}
void PastePaper(int yy, int xx, int s)
{
    int i,j;

    // 색종이를 붙인다
    for(i=yy; i<yy+s; i++)
        for(j=xx; j<xx+s; j++)
            map[i][j]=0;
}

void DetachPaper(int yy, int xx, int s)
{
    int i,j;

    // 색종이를 떼어낸다
    for(i=yy; i<yy+s; i++)
        for(j=xx; j<xx+s; j++)
            map[i][j]=1;
}
