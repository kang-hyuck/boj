/* Backtracking_17825, 주사위 윷놀이 */
/* 포인트
 (백트랙킹 + 시뮬레이션) 문제
 1. 다음 위치로 이동해야하는 "인덱스"를 route에 기록 해주었다
 2. 이동시, 이동할 칸이 많이 남은경우는 "지름길"로 가지 않도록 처리 해주어야함
 3. "말 정보"는 이동이 "결정" 되었을 때, 반드시 "갱신" 해주어야 한다!!
 4. "도착지점"은 사용중 표시 하면 안된다.
*/

#include <iostream>
#include <vector>
#include <algorithm>  // max()
using namespace std;

typedef struct MAL{
    int x, fin;  // 
}MAL;

MAL mal[5];
vector<int> map;  // 지도
int route[33];  // 이동해야하는 길
int moveCnt[10];  // 주사위 점수
int used[33];  // 말이 있는지
int ans;

void InitMap(void);
void DFS(int, int);
int MoveMal(int, int);

int main()
{
    int i;
    
    // 입력부
    for(i=0; i<10; i++) cin>>moveCnt[i];
    InitMap();
    
    // 실행부
    DFS(0,0);

    // 출력부
    cout<<ans;

    return 0;
}

void InitMap()
{
    int i;
    
    // 맵 점수 표시
    vector<int> temp = {13,16,19,  22,24,  28,27,26,  25,30,35};
    for(i=0; i<=20; i++) map.push_back(2*i);
    for(i=0; i<(int)temp.size(); i++) map.push_back(temp[i]);  // 21~31
    map.push_back(0); // 32
    
    // 다른길 가야하는 경우 표시
    for(i=0; i<33; i++) route[i]=i+1;  // 기본적으로 "다음인덱스"로 이동하게끔 연결 해준다
    route[5]=21;   route[23]=29; // 21번,29번 인덱스로 가야함  // 특정한 부분에서는 다른 인덱스로 이동하게끔 수정
    route[10]=24;  route[25]=29; // 24번,29번 인덱스로 가야함
    route[15]=26;  route[28]=29; // 26번,29번 인덱스로 가야함
    route[31]=20;  route[20]=32; // 20번,32번(fin) 인덱스로 가야함
    route[32]=32;  // 도착점은 자기자신으로 이동
}

void DFS(int cnt, int sum)
{
    int i, backupX;

    // 종료 조건
    if( 10 == cnt ) {ans = max(ans, sum);  return;}

    // 자식 노드 호출 (말을 선택하고, 이동시킨다)
    for(i=0; i<4; i++)
    {
        // 위치 백업
        backupX = mal[i].x;  // 이동해보기 전에 말 위치 저장 (MoveMal에서 이동을 다해보니까... 여기서 백업해준다)
    
        // 말을 이동할 수 없는 경우
        if(  1 == mal[i].fin ) continue;  // 말이 이미 도착점에 있는 경우
        if( -1 == MoveMal(i, moveCnt[cnt]) ) continue;  // 이동한 하려는 곳에 말이 있는 경우
    
        // 말을 이동할 수 있는 경우
        used[backupX] = 0;   // 이동하기 전 위치 지워줌
        if(mal[i].fin != 1) used[mal[i].x] = 1;  // 이동한 위치 사용중 표시 (종료위치가 아닌 경우만!!! 사용표시 한다)
        
        DFS(cnt+1, sum + map[mal[i].x]);
        
        used[mal[i].x] = 0;
        used[backupX] = 1;
        mal[i].x = backupX;  mal[i].fin=0;  // 말 정보 복구
    }
}

int MoveMal(int num, int cnt)
{
    int x;
    x = mal[num].x;

    // 주사위 수만큼 이동 시킨다
    while(1)
    {
        // 종료 조건
        if(cnt==0) break;
        cnt--;
        
        // 다른 길 택할 필요가 없는 경우
        x = route[x];  // 길 따라서 이동
        
        // 다른 길 택해서 이동 해야하는 경우
        if(cnt>0)if(x==5 || x==10 || x==15){x=x+1; cnt--;}  // 여기서 멈추는게 아니라면, 미리 다음 index로 이동시키고 cnt-- 해준다
    }
    
    // 해당 위치로 이동할 수 없는 경우
    if( used[x]==1 ) return -1;  // 다른 말이 해당 위치에 있는 경우
    
    // 해당 위치로 이동할 수 있는 경우
    mal[num].x = x;  // x값 갱신
    if(x==32) mal[num].fin=1;  // 도착점에 도착할 경우 도착했음을 갱신
    
    return 1;
}

