/* DFS_BFS_12851, 숨바꼭질2 */
/* 포인트
 1. 노드 방문표시(visited)를 "큐에서 꺼낼때" 하는가 or "큐에 넣기 전"에 하는가의 차이를 확인할 수 있다
    자식 노드 호출하기 위해 다음 자식 노드 값(nextX) 계산 하는 for문에서 각각의 "연산"을 하나의 "엣지"로 생각할 수 있다.
    만약 하나의 연산에서 nextX 계산해서 큐에 넣을때 방문표시(visited)를 해버리면 다른 연산에서 똑같은 nextX 계산 했을 때 큐에 안들어가게 된다.
    그러면 노드 K에 도달했을 때 "도달하는 가짓수"가 줄어들게 되므로.. 큐에 넣을 때 방문 표시를 하면 안된다.
    현재 노드에서 연산 과정 다 끝내 놓고.. 이동한 자식노드에서 큐에서 꺼낼 때 자신의 노드 값을 방문 표시 해주는 식으로 해주면 해결 가능하다
 2. K에 도달되는 큐 값을들 카운트하면, K로 도달하는 방법의 갯수를 셀 수 있다.
 3. 최초로 K에 도달했을 때의 카운트값(cnt)을 time에 저장 하고, 그 이후에 큐에서 cnt보다 큰 값이 나오게 될 때 BFS를 종료하면 된다
    참고로!! if(time!=0 && time < cnt) 에서.. 전역변수 time 초기값이 0이라서 time이 갱신 되었을 때 time<cnt를 비교 하게끔 해야된다.
*/
#include <iostream>
#include <queue>
#include <tuple>  // tie()
using namespace std;

typedef struct node {
    int X, cnt;
}node;

int visited[100010];   // 이거 사용 안하면 큐에 쌓여서 "메모리초과" 나온다..
int N, K, ans, time;
queue<node> q;

void BFS(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N >> K;

    // 실행부
    q.push({ N,0 });
    BFS();

    // 출력부
    cout << time << "\n" << ans;

    return 0;
}

void BFS()
{
    int i, nextX, X, cnt;

    while (!q.empty())
    {
        tie(X,cnt)= {q.front().X, q.front().cnt};
        q.pop();

        // 종료 조건
        if (time != 0 && time < cnt) return;   // 시간이 들어왔는데, 다음 시간 나올 경우 종료 (BFS를 종료 시킨다. 아래 조건문 보다 먼저 나와야 한다)
        if (X == K) { ans++; time = cnt; continue;}  // 방법수 증가, 걸린시간, 정답 도착시 아래 부분 실행 X

        // 연산이 하나의 "엣지"에 대응된다고 생각하면 된다.
        visited[X] = 1;

        for (i = 0; i < 3; i++)
        {
            // 다음 이동 위치 계산
            if (i == 0) nextX = X - 1;
            if (i == 1) nextX = X + 1;
            if (i == 2) nextX = 2*X;

            // 다음 이동할 값으로 이동할 수 없는 경우
            if (nextX < 0 || nextX > 100000) continue;  // 다음 이동할 값이 범위를 벗어나는 경우 넘긴다
            if (visited[nextX] == 1) continue;  // 방문한 적이 있는 경우

            // 이동 가능할 경우 큐에 넣는다
            q.push({ nextX, cnt +1 });
        }
    }
}
