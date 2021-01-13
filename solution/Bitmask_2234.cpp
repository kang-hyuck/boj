/* Bitmask_2234, 성곽 */
/* 포인트
 (완전탐색 + BFS + 비트마스크) 문제
  1. DFS,BFS로 "집합(덩어리) 갯수" 구할 때는 2중 for문 이용해서 호출
  2. DFS,BFS로 "면적 크기" 구할 때는 "호출하는 자식 노드 갯수" 카운트하면 됨 (전역변수 cnt 사용했음)
  3. 큐에 넣을 조건에서. 자신의 위치에서만 벽의 유/무를 판단하여 넣으므로. 벽을 허물 때 "자신의 위치에서만" 허물면 된다
  4. DFS의 완전탐색 같은 경우는. 자식노드를 계속 호출해가다가 특정 조건에 도달할 경우 원하는 행동을 이행하는데,
     지금 이 문제 처럼 BFS의 완전탐색 같은 경우는 자식노드마다 4방향 벽을 다 부수고 BFS 돌리는 것을 반복했기에
     똑같은 집합(덩어리) 내에서 중복된 BFS 호출을 계속 하는 경우가 너무 많음.. 막상 BFS 이용한 완전탐색은 시간초과 날꺼 같아서 생각하기 쉽지 않은듯..
*/
#include <iostream>
#include <queue>
#include <tuple>  // tie()
#include <string.h>  // memset()
using namespace std;

typedef struct node {
    int y, x;
}node;

int n, m,  ans, roomCnt, cnt;  // cnt: 면적(노드) 갯수 카운트
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, -1, 0, 1 };
int visited[55][55];
int map[55][55];
queue<node> q;

void BFS(void);
void Reset(void);

int main()
{
    int i, j, k;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> n >> m;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            cin >> map[i][j];

    // 실행부
    for (i = 1; i <= m; i++)   // DFS,BFS로 덩어리 갯수 구할 때는 2중 for문으로 호출
        for (j = 1; j <= n; j++)
        {
            // 이미 방문한 영역인 경우 (넘긴다)
            if (visited[i][j] == 1) continue;

            // 방문한 영역이 아닌 경우 (queue에 넣고 BFS 실행)
            roomCnt++;   // 방 갯수 카운트
            visited[i][j] = 1;
            q.push({ i,j });
            BFS();
            cnt = 0;  // 다시 사용해야 하므로 비운다
        }

    cout << roomCnt <<endl;   // 1의 답
    cout << ans << endl;  // 2의 답

    // 3의 답 계산
    ans = 0;  // ans 초기화
    Reset();  // visited, cnt 초기화 (자주 사용해서 함수로 만듬)
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            for (k = 0; k < 4; k++)   // 각 칸에서 4방향 벽을 1개씩 허물고 BFS로 면적값 확인한다 (완전탐색)
            {
                // 벽 없으면 넘긴다
                if (!(map[i][j] & (1 << k))) continue;

                // 벽 있는 경우
                map[i][j] &= ~(1 << k);  // 벽 허문다,  (!!! 자신의 위치에 있는 벽만 부셔도 된다.. BFS안에서 자신의 벽 유/무를 기준으로 큐에 넣기 때문에.)
                visited[i][j] = 1;  // 방문표시
                q.push({ i,j });  // 큐에 현재 위치 넣어준다
                BFS();  // BFS 호출, 벽을 허물고나서 자신과 연결된 면적만 확인함
                map[i][j] |= (1 << k);  // 탐색 끝나고 벽 다시 복구한다
                Reset();  // visited,cnt 초기화, Reset을 맨 위보다 벽없는 경우 넘기는 부분 뒤에 놓아야 시간 속도 이득
            }

    cout << ans << endl;  // 3의 답

    return 0;
}

void BFS()
{
    int i, y,x,yy,xx;

    while (!q.empty())
    {
        tie(yy, xx) = { q.front().y, q.front().x};
        q.pop();

        // 탐색한 노드 갯수 카운트
        cnt++;
        ans = max(ans, cnt);  // 최대 면적 값 갱신

        // 다음 자식노드 호출 
        for (i = 0; i < 4; i++)
        {
            y = yy + dy[i];   x = xx + dx[i];

            // 다음 위치로 이동할 수 없는 경우
            if (y<1 || x<1 || y>m || x>n)  continue;  // 맵 범위 벗어나는 경우
            if (visited[y][x] == 1) continue;  // 방문한 적이 있는 경우
            if (map[yy][xx] & (1 << i)) continue;  // 이동하려는 방향으로 벽이 있는 경우 (현재위치 기준)

            // 이동할 수 있는 경우
            visited[y][x] = 1;   // 방문표시
            q.push({ y,x });   // 큐에 넣어준다
        }
    }
}

void Reset()
{
    // 면적(노드) 갯수 카운트 초기화
    cnt = 0;

    // visited 초기화
    memset(visited, 0, sizeof(visited));
}
