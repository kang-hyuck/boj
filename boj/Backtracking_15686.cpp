/* Backtracking_15686, 치킨 배달 */
/* 포인트
 (백트랙킹) 문제
 DFS로 "조합"을 구현 한다
*/
#include <iostream>
#include <vector>
#include <stdlib.h>  // abs()
#include <tuple>  // tie()
#include <algorithm>
using namespace std;

#define INF 987654321

typedef struct node{
    int y,x;
}node;
typedef struct nodeHouse{
    int y,x, dist;
}nodeHouse;

vector<node> chick;
vector<nodeHouse> house;
vector<int> sel;  // <치킨집 위치 index> 저장

int N,M, ans;
int map[55][55];

void DFS(int, int);
int CalDist();

int main()
{
    int i,j;
    
    // 입력부
    cin>>N>>M;    
    for(i=0; i<N; i++)
        for(j=0; j<N; j++)
        {
            cin>>map[i][j];
            
            // 집인 경우
            if(map[i][j] == 1) house.push_back({i,j,INF});  // 집 위치,거리 INF로 저장
            
            // 치킨집인 경우
            if(map[i][j] == 2) chick.push_back({i,j});  // 치킨집 위치 저장   
        }

    // 실행부
    ans = INF;
    DFS(0,0);

    // 출력부
    cout<<ans;

    return 0;
}

void DFS(int index, int cnt)
{
    int i;

    // 치킨집 M개 선택한 경우
    if(cnt == M){ans = min(ans, CalDist());  return;}
    if(index >= (int)chick.size()) return;

    
    // 치킨집 M개 선택 못한 경우 (자식 노드 호출)
    for(i=index; i<(int)chick.size(); i++)
    {
        // i번째 치킨집을 선택
        sel.push_back(i);
        
        DFS(i+1, cnt+1);  // 자식 노드 호출
        
        // i번째 치킨집을 꺼냄
        sel.pop_back();
    }
}

int CalDist()
{
    int i,j, yHouse,xHouse,dist, yChick,xChick, ret=0;

    // 각 집 마다 거리 계산
    for(i=0; i<(int)house.size(); i++)
    {
        // 집 정보 가져옴
        tie(yHouse,xHouse,dist) = {house[i].y, house[i].x, house[i].dist};
        
        // 집의 치킨 거리 찾음 (각 치킨집 위치 가져와서 계산)
        for(j=0; j<(int)sel.size(); j++)  // 선택된 치킨집의 (인덱스) 가져온다
        {
            tie(yChick,xChick) = {chick[sel[j]].y, chick[sel[j]].x};  // 치킨집 = 치킨집 벡터[인덱스]
            
            // 치킨 거리 계산
            dist = min(dist, abs(yHouse - yChick) + abs(xHouse - xChick));
        }
        
        // 계산된 치킨 거리 누적 (집 1개마다 계산된 치킨 거리 더해줌)
        ret += dist;
    }

    // 계산된 값 반환
    return ret;
}

