/* TreeDP_2533, 사회망 서비스(SNS) */
/* 포인트
 1. 양방향엣지로 저장해주어야한다. 단방향으로만 저장하면 트리탐색이 안될 수 있다 ([1,3], [2,3] 인 경우. 단방향으로만 저장하면 3->2로 진행 불가)
 2. 양방향엣지 사용하면, (자식노드->부모노드)로 탐색하는 경우를 막아주어야한다. 다차원 DP문제/트리DP 문제 핵심이다..
    visited에 2차원으로 early 정보를 포함시켜서 사용하면... 자식노드 호출할 때 코드가 복잡해진다..
    visited를 1차원으로 사용하는 대신 자식노드 호출할때만 자식노드->부모노드 호출못하도록 잠시 막아주는 식으로 구현한다 (DFS 끝났을때 visited 풀어주는식으로)
    풀어주어야하는 이유는... early가 0/1 2가지 경우 모두다 각각 "똑같은 노드"를 방문하기 때문이다. 다른 early값 가지는 경우 방문할 수 있도록 풀어주어야 한다.
 3. memset은 0,-1 초기화할때만 사용하는거 유의할 것..
 4. DP값 초기화하는 부분. 자기자신이 얼리어댑터인지 아닌지에 따라서 DP초기값이 다르다. 이 부분을 빼버리고 반환부에서 if문으로 더해주어도 됨(그게 더 실수 적을듯)
*/
#include <iostream>
#include <vector>
#include <algorithm> // min()
#define INF 987654321
using namespace std;

// 전역변수선언
vector<int> edge[1000010];
int DP[1000010][2];
int visited[1000010];
int N, ans;

// 함수선언
int DFS(int,int);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int from,to;

    // 입력부
    cin>>N;
    for(int i=0; i<N-1; i++){
        cin>>from>>to;
        edge[from].push_back(to);  // 양방향 엣지 저장
        edge[to].push_back(from);  // 양방향 엣지 사용, 트리탐색이므로... "부모노드 방문표시" 해주어야한다
    }
    
    // 실행부
    for(int i=1; i<=N; i++) for(int j=0; j<2; j++) DP[i][j]=INF;   // DP값 초기화
    visited[1]=1;  // 1번노드 방문표시
    ans=min( DFS(1,0), DFS(1,1) );  // root를 1번노드로 생각하고 계산.
    
    // 출력부
    cout<<ans;

    return 0;
}

int DFS(int num, int early)
{
    // 종료부
    if(DP[num][early] != INF) return DP[num][early];  // DP값이 존재하는 경우 (이미 방문해서 계산된 경우)

    // 실행부 (DP값 초기화)
    if(early==0) DP[num][early] = 0;  // 자신이 얼리어답터 아니므로 0
    if(early==1) DP[num][early] = 1;  // 자신이 얼리어답터 이므로 1  (DP값을 여기서 초기화하면, 자식노드에서 부모노드 호출해서 이 값이 누적될 수도 있다.. 따라서 visited로 막아야한다)
    
    // 자식노드 호출
    for(int i=0; i<(int)edge[num].size(); i++)
    {
        // 이동할 노드선택
        int nextNum = edge[num][i];
        
        // 이동할 수 없는 경우
        if(visited[nextNum]==1) continue;  // 방문한 적이 있는 경우 (부모/조상 노드인 경우임)
        
        // 이동할 수 있는 경우 (DP값 계산)
        visited[num]=1;  // 현재노드 방문표시 (자식노드->부모노드로 탐색하지 못하도록 막아준다. 양방향엣지라서 막아주어야한다. 막지않으면 자식DP에서 부모DP값이 누적될 수 있다)
        if(early==0) DP[num][early] += DFS(nextNum, 1);   // 자식노드가 "모두" 얼리어답터인 경우(1) 계산
        if(early==1) DP[num][early] += min( DFS(nextNum,0), DFS(nextNum,1) );   // 자식노드가 "얼리어답터아닌경우(0)/얼리어답터인경우(1)" 계산
        visited[num]=0;  // 현재노드 방문표시 제거 (early가 1/0인 경우. 각각 방문해야하므로 다시 방문하기위해서 방문표시 제거해준다.)
    }
    
    // 반환부
    return DP[num][early];  // 계산된 자신의 DP값 반환 (DP값을 초기화하지않고 여기서 if문사용해서 더해주어도 된다..)
}
