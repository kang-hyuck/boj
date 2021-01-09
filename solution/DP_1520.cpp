/* DP_1520, 내리막 길 */
/* 포인트
	DP값 전부 -1로 초기화.
	( DFS로 방문한적 없는 경우도 0, 아무 방향으로도 이동못하는 경우도 0 으로 겹칠 수 있기 때문.)

	DP 초기값을 -1로 지정 해주어야 한다. 
	DP 초기값으로 0 값을 그대로 사용하면 (지나온 곳 제외하고)3방향
	어느 곳으로도 도착점에 도달하지 못하는 경우랑 동일하게 0 값을 갖는다.
	따라서 다른 경로를 통해서 이 노드에 또 들어올 경우 3방향으로 똑같은 
	탐색을 또 시도할 수가 있다... 이게 쌓이면 DP 사용했어도 시간초과 난다
*/
#include <iostream>
using namespace std;

int M, N;  //세로,가로
int map[510][510];
int DP[510][510];  // 자신의 자식노드를 통해서 도착지까지 갈 수 있는 경우의 수 저장
int ans;

int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int dfs(int, int);

int main()
{
	int i, j;
	ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

	// 입력부
	cin >> M >> N;
	for (i = 1; i <= M; i++)
		for (j = 1; j <= N; j++)
			cin >> map[i][j];

	// 실행부
	for (i = 1; i <= M; i++)
		for (j = 1; j <= N; j++)
			DP[i][j] = -1;
	ans = dfs(1, 1);

	// 출력부
	cout << ans;

	return 0;
}

int dfs(int yy, int xx)
{
	int i, y, x, ret;
	ret = 0;

	// 종료 조건
	if (M == yy && N == xx) return 1;  // 도착지에 도달한 경우
	if (DP[yy][xx] >= 0) return DP[yy][xx];  // 지나온 적이 있는 경우

	// 방문 표시 (DP 초기값 -1 이다)
	DP[yy][xx] = 0;

	// 다음 경로 이동
	for (i = 0; i < 4; i++)
	{
		y = yy + dy[i];   x = xx + dx[i];

		// 다음 이동 범위 확인
		if (y > 0 && x > 0 && y <= M && x <= N)
		{
			// 내리막길인 경우 이동
			if (map[yy][xx] > map[y][x])
			{
				// 자식노드들의 반환값을 현재 노드 DP에 저장
				DP[yy][xx] += dfs(y, x);
			}
		}
	}
	// 현재 노드의 DP값 반환
	return DP[yy][xx];
}

