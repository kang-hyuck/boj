/* TreeDP_15681, 트리와 쿼리 */
/* 포인트
 1. 쿼리가 1e5 이고, 정점수가 1e5이기때문에. 1e10연산까지 나올 수 있다. 따라서 DP로 풀어야한다.
 2. DFS방문시 DP값을 0으로 초기화 해도, 자식노드 호출하는 과정에서 현재노드(부모노드)의 DP값이 바뀐다.
    그렇게되면, (자식노드->부모노드) 호출 되어서 자식노드 DP값에 부모노드DP값 누적되는 것을 막아주어야한다. visted 사용해야한다.
 3. ★"root노드가 무엇이냐"에 따라서 "모든 트리DP값"이 바뀐다... 생각없이 쿼리받은 순서대로 DFS 호출했다가 한번 틀림 ㅠ.ㅠ
    맨처음에 root노드를 기준으로 DFS를 호출해주어야 DP값이 제대로 만들어진다.
*/
#include <iostream>
#include <vector>
#include <string.h>  // memset()
using namespace std;

// 전역변수선언
vector<int> edge[100010];
int visited[100010];
int DP[100010];
int N,R,Q, ans;

// 함수선언
int DFS(int);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int from,to,query;

    // 입력부
    cin>>N>>R>>Q;
    for(int i=0; i<N-1; i++){  // 엣지정보 저장
        cin>>from>>to;
        edge[from].push_back(to);  // 양방향 엣지로 저장해야한다.. 문제가 그럼 ㅠ
        edge[to].push_back(from);
    }

    // 실행부
    memset(DP, -1, sizeof(DP));
    DFS(R);  // root 정점갯수 포함된 값 출력.
    for(int i=0; i<Q; i++){  // 쿼리 갯수만큼 실행
        cin>>query;
        cout<<DP[query]<<"\n"; 
    }

    return 0;
}

int DFS(int num)
{
    // 종료부
    if(DP[num] != -1) return DP[num];

    // 실행부 (DP값 초기화)
    DP[num]=0;  // 자식노드호출할 때 DP값이 0에서 누적되면서 바뀐다. 따라서 visited로 막아주어야한다. DP값 초기화 한것으로 못막음

    // 자식노드 호출
    for(int i=0; i<(int)edge[num].size(); i++)
    {
        // 이동할 노드번호
        int nextNum = edge[num][i];

        // 이동할 수 없는 경우
        if(visited[nextNum]==1) continue;  // 넘긴다 (부모/조상 노드인 경우)

        // 이동할 수 있는 경우
        visited[num]=1;  // 방문표시. (자식노드->부모노드) 탐색하지 못하도록 막는다.
        DP[num] += DFS(nextNum);  // 자식노드에서의 DP값 누적 (여기서 부모의 DP값이 바뀌므로.. 자식노드->부모노드 호출하면 안됨)
        visited[num]=0;  // 방문표시 제거
    }

    // 반환부 (DP값 반환)
    return DP[num] += 1;  // 자기자신 정점갯수 1 포함시켜서 반환
}
