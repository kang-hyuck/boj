/* TreeDP_1949, 우수 마을 */
/* 포인트
 1. visited를 1차원 배열로 사용했다. (자식노드>부모노드) 호출되는 경우를 막기위해서 사용했음. 우수마을인경우/아닌경우 2가지 경우 모두
    해당 노드에 방문을 해야하므로. visited를 자식노드 호출하기전에만 잠깐 표시해주고, 자식노드DFS가 종료되고 돌아온경우에는 풀어주었다.
 2. max()사용하면 우수X-우수X-우수X인 경우가 연달아서 나올 수가 없다. 중간에 우수X인 노드가 우수O인 경우 DP값이 더 크기때문에
    max()로 선택하게 된다면 가운데 노드가 우수X인 경우를 택할리가 없다.
 3. 이 경우는 우수X,우수O인 경우 2가지만 다루었는데, 만약 노드마다 선택갯수가 2가지 이상이라면, max({DP[][0], DP[][1], DP[][2], ...})
    처럼 DP값을 여러개 넣는 식으로 선택할 수 있을 듯.
 4. 노드마다 자신이 우수(1)/우수아닌(0) 경우 택할 경우 DP값을 채우는 식으로 구현했다. 자신이 우수(1)인 경우만 "자신 마을인원수" 더해주었다
 5. 정답은 최대 10억이므로 ans 자료형 int 그대로 사용하였음
*/
#include <iostream>
#include <vector>
#include <string.h>  // memset()
using namespace std;

// 전역변수선언
vector<int> edge[10010];
int people[10010];
int visited[10010];
int DP[10010][2];
int N, ans;

// 함수선언
int DFS(int, int);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int from,to;

    // 입력부
    cin>>N;
    for(int i=1; i<=N; i++) cin>>people[i];
    for(int i=0; i<N-1; i++)  // 엣지정보 입력
    {
        cin>>from>>to;
        edge[from].push_back(to);   // 양방향 엣지 저장.
        edge[to].push_back(from);   // 양방향엣지라서 (자식노드->부모노드) 호출가능성이 존재한다. 고려하고 DFS 구현해야함.
    }

    // 실행부
    memset(DP, -1, sizeof(DP));  // DP초기화
    ans = max(DFS(1,0), DFS(1,1));  // root를 1번노드로 생각하고 실행

    // 출력부
    cout<<ans;

    return 0;
}

int DFS(int num, int excellent)
{
    // 종료부
    if(DP[num][excellent] != -1) return DP[num][excellent];

    // 실행부
    DP[num][excellent] = 0;  //  DP값 초기화 (우수마을도 일단 0으로 초기화. 자식노드가 부모노드 호출시 0더함, 우수마을은 "반환부"에서 자신의 인원수 더함)

    // 자식노드 호출
    for(int i=0; i<(int)edge[num].size(); i++)   // 연결된 노드호출
    {
        // 이동할 노드 선택
        int nextNum = edge[num][i];

        // 이동할 수 없는 경우
        if(visited[nextNum]==1) continue;   // 방문했던 곳인 경우 (부모/조상 노드인 경우)

        // 이동할 수 있는 경우
        visited[num]=1;  // 방문표시 (자식노드->부모노드로 방문하지 못하도록 막음)
        if(excellent==0) DP[num][0] += max( DFS(nextNum,0), DFS(nextNum,1) );  // 현재노드가 우수마을 아닌경우 (다음마을이 우수/우수아닌 경우 중 최댓값 택함)
        if(excellent==1) DP[num][1] += DFS(nextNum,0);  // 현재노드가 우수마을인 경우 (다음마을이 우수아닌 경우 DP값만 더함)
        visited[num]=0;  // 방문표시 제거
    }

    // 반환부
    if(excellent==0) return DP[num][excellent];  // 우수마을이 아닌경우 자신의 인원수 안더함
    return DP[num][excellent] += people[num];    // 우수마을인 경우만 "자신의 인원수" 더함 (리프노드인 경우 DP[][1]값이 채워진다)
}



/* 방법2)  void 반환형 DFS를 사용하는 경우 
 *
 *  노드번호를 1번만 호출하고, 해당노드 내에서 DP[][] 값 2개를 계산하는 식으로 구현했다.
 *  int 반환형 DFS를 사용하는 경우에 비해서 노드탐색 횟수를 줄일 수 있다. (이 경우에는 excellent값에 따라서 노드번호당 2번 방문해야한다)
*/

/*
#include <iostream>
#include <vector>
using namespace std;

// 전역변수선언
vector<int> edge[10010];
int people[10010];
int visited[10010];
int DP[10010][2];
int N, ans;

// 함수선언
void DFS(int);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int from,to;

    // 입력부
    cin>>N;
    for(int i=1; i<=N; i++) cin>>people[i];
    for(int i=0; i<N-1; i++)  // 엣지정보 입력
    {
        cin>>from>>to;
        edge[from].push_back(to);
        edge[to].push_back(from);   // 양방향 엣지
    }

    // 실행부
    DFS(1);  // 1번 마을부터 탐색
    ans = max(DP[1][0], DP[1][1]);

    // 출력부
    cout<<ans;

    return 0;
}

void DFS(int num)
{
    // 실행부
    visited[num]=1;  // 방문표시
    DP[num][1] = people[num];  // 우수마을인 경우만 자신의 인원수 더함 (리프노드인 경우 DP[][1]값이 채워진다)

    // 자식노드 호출
    for(int i=0; i<(int)edge[num].size(); i++)   // 연결된 노드호출
    {
        // 이동할 노드 선택
        int nextNum = edge[num][i];

        // 이동할 수 없는 경우
        if(visited[nextNum]==1) continue;   // 방문했던 곳인 경우

        // 이동할 수 있는 경우
        DFS(nextNum);  // 자식노드 호출 (자식노드 DP값 계산)
        DP[num][0] += max(DP[nextNum][0], DP[nextNum][1]);  // 현재노드가 우수마을 아닌경우 (다음마을이 우수/우수아닌 경우 중 최댓값 택함)
        DP[num][1] += DP[nextNum][0];  // 현재노드가 우수마을인 경우 (다음마을이 우수아닌 경우 DP값만 더함)
    }
}
*/
 
