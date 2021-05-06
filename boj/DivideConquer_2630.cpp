/* DivideConquer_2630, 색종이 만들기 */
/* 포인트
 1. 현재DFS 노드에서 해결하지 못하는 경우. 자식DFS에서 해결하도록 DFS를 호출하는 것이 포인트다.
 2. DFS노드에서 "해야할 일"을 "정확하게 구분"하는 것이 포인트다.
    지금 같은 경우는 2가지 일을 한다. (1)색종이가 전부 같은색인지 확인하고, (2)전부같지 않다면 4개로 쪼개서 각각 똑같은일을 한다.
	(1),(2)를 착안하고 코드를 구현하면 된다.
*/
#include <iostream>
using namespace std;

// 전역변수선언
int N, white,blue;
int map[150][150];

// 함수선언
void DFS(int,int, int);

int main()
{
    // 입력부
    cin>>N;
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) cin>>map[i][j];

    // 실행부
    DFS(0,0, N);  // (맨왼쪽위 좌표, 종이크기)

    //출력부
    cout<<white<<"\n"<<blue<<endl;

    return 0;    
}

void DFS(int yy, int xx, int size)
{

    // 실행부
    for(int i=yy; i<yy+size; i++) for(int j=xx; j<xx+size; j++)
    {
        // 색이 같은 경우
        if(map[yy][xx] == map[i][j]) continue;  // 색이 같으면 넘긴다 (아래 코드실행하지 않음)

        // 색이 다른 경우 (종이 4개로 나눔)
        DFS(yy,          xx,          size/2);  // 왼쪽,위
        DFS(yy,          xx+size/2,   size/2);  // 오른쪽,위
        DFS(yy+size/2,   xx,          size/2);  // 왼쪽,아래
        DFS(yy+size/2,   xx+size/2,   size/2);  // 오른쪽,아래
        return;  // 종료 (자식노드에서 종이카운트 된다. 여기서는 종이카운트하지 않는다. 아래 코드진행하지 않도록 종료시킨다)
    }

    // 색이 "모두" 같은 경우.
    if(map[yy][xx]==1) blue++;   // 파란종이 갯수 1증가
    if(map[yy][xx]==0) white++;  // 하얀종이 갯수 1증가
}
