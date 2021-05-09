/* DivideConquer_1074, Z */
/* 포인트
 1. DFS마다 (size x size)만큼의 종이를 탐색하는 경우가 되고, 그 종이크기 마다.. 대응되는 r,c의 좌표가 바뀐다.
    DFS마다 실행부에서 처리해주는 것이 무엇이 필요한지 고민해본다. 이 문제같은 경우는 DFS마다 ans값에 누적해주었다.
 2. 자식노드호출할 때.. 종이크기 마다 분할하며 탐색할때마다 종이에따른 y,x 상대좌표값이 다르므로..
    이것을 계산한 y,x좌표를 DFS호출 할때마다 넣어주어야한다.
*/
#include <iostream>
using namespace std;

// 전역변수
int N,r,c, ans;

// 함수선언
void DFS(int,int, int);

int main()
{
    // 입력부
    cin>>N>>r>>c;

    // 실행부
    DFS(r,c,1<<N);   // 초기크기값 2^N

    // 출력부
    cout<<ans;
    return 0;
}

void DFS(int yy,int xx, int size)
{
    // 종료조건
    if(size==1) return;   // 1x1칸 까지 나눈 경우 종료

    // 자식노드 호출 (4곳 중, r,c위치에 따른 값 정답값 누적)
    if(yy< size/2 && xx< size/2){ans += 0;  DFS(yy,xx,size/2);} // 왼쪽위에 r,c가 위치한 경우
    if(yy< size/2 && xx>=size/2){ans += 1*((size/2)*(size/2));  DFS(yy,xx-size/2,size/2);}   // 오른쪽위에 r,c가 위치한 경우
    if(yy>=size/2 && xx< size/2){ans += 2*((size/2)*(size/2));  DFS(yy-size/2,xx,size/2);}   // 왼쪽아래에 r,c가 위치한 경우
    if(yy>=size/2 && xx>=size/2){ans += 3*((size/2)*(size/2));  DFS(yy-size/2,xx-size/2,size/2);}   // 오른쪽아래에 r,c가 위치한 경우
}

