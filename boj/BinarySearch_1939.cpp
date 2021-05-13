/* BinarySearch_1939, 중량제한 */
/* 포인트
 1. left,right인덱스 이동을 BFS결과에 따라 이동시키면 된다.
 2. DFS사용하면 안될듯... 섬의 갯수가 매우커서 메모리초과 나올 수 있을 것 같다..
 3. 항상 실수하기 좋은점... BFS종료조건이 "여러개" 있다면 (이 경우는 아니지만..) 종료조건 "순서"에 따라서 정답이 다를 수 있다.. 실수하기 좋음
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>  // memset()
using namespace std;

typedef struct node{
    int num, weight;   // node = {노드번호,중량제한}
}node;

// 전역변수
int visited[10010];  // 방문표시 용도
vector<node> edge[10010];   // [노드번호]={<연결된노드번호,중량제한>, ...}
int N,M, ans, startSum,endSum;

// 함수선언
void BinarySearch();
bool BFS(int);   // DFS로 연결확인성 확인하면 안될듯... 섬 갯수가 100000개라서.. 깊이가 깊어서 메모리초과 날수도 있을듯..

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int A,B,C;

    // 입력부
    cin>>N>>M;
    for(int i=0; i<M; i++){cin>>A>>B>>C;  edge[A].push_back({B,C});   edge[B].push_back({A,C});}  // 엣지정보 저장
    cin>>startSum>>endSum;  // "연결가능성" 확인할 섬 2개 저장.

    // 실행부
    BinarySearch();

    // 출력부
    cout<<ans;

    return 0;
}

void BinarySearch()   // start,end연결이가능한 "최대중량값"을 이분탐색으로 찾는다.
{
    int left=1,   right=1000000000,   mid;
    bool res;

    // 실행부
    while(1)
    {
        // 실행부
        mid = (left+right)/2;  // 중간값 계산
        res = BFS(mid);        // 시뮬레이션결과 저장 (중간값 이용)

        // 인덱스 이동  (left,right 중 1개 이동)
        if( res) left  = mid+1;
        if(!res) right = mid-1;       

        // 종료조건
        if(left>right){ans=left-1;  return;}   // 정답에서. left==right가 되는데, 인덱스이동 부분에서 left가 1번 더 이동하게 된다.
    }
}

bool BFS(int val)
{
    int num, nextNum, weight;
    queue<int> q;

    // 초기화
    memset(visited, 0, sizeof(visited));  // 방문표시 초기화
    visited[startSum]=1;  // 방문표시
    q.push(startSum);   // 출발노드 넣는다.

    // 실행부
    while(!q.empty())
    {
        num = q.front();
        q.pop();

        // 종료조건
        if(num==endSum) return true;  // 도착한 경우

        // 다음노드 이동
        for(int i=0; i<(int)edge[num].size(); i++)
        {
            nextNum = edge[num][i].num;   weight = edge[num][i].weight;

            // 이동할 수 없는 경우
            if(visited[nextNum]==1) continue;  // 방문한 적이 있는 경우
            if(weight < val) continue;         // 다리중량제한 보다 옮기려는 중량이 큰경우 (무너지므로 이동불가)

            // 이동할 수 있는 경우
            visited[nextNum]=1;  // 방문표시
            q.push(nextNum);     // 큐에 넣는다
        }
    }

    // 도착할 수 없는 경우 (start -> end로)
    return false;
}
