/* BOJ_1937, 욕심쟁이 판다 */
/* 포인트
   방문을 할 경우 그위치에서 최소한 1일은 살 수 있기 때문에
   방문한 시점에서 DP값이 최소 1이 된다. dfs()에서 자신의 DP값을 반환하기 때문에,
   자식노드 호출하는 for문에서 (자신의 DP값) = max(자신의 DP값,자식노드dfs()+1)
   로 DP값을 채웠고, 다 계산된 DP값을 함수 맨끝에서 return으로 반환 해주었다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

int map[510][510];
int DP[510][510];  // 그 위치에서 판다가 최대한 살 수 있는 일자
int dx[4] = { 1,-1, 0, 0 };
int dy[4] = { 0, 0, 1,-1 };
int n, K;

int DFS(int, int);

int main()
{
	int i, j;
	ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

	// 입력부
	cin >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			cin >> map[i][j];

	// 실행부
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
		{
			// DP값 0인 곳인 경우. (DFS로 방문한 적이 없는 위치인 경우)
			if (DP[i][j] == 0)
			{
				DP[i][j] = DFS(i, j);  //  DFS 실행시켜서 DP값 채워준다
				K = max(K, DP[i][j]);  //  DFS로 이어진 그 덩어리에서 살 수 있는 최대 요일 확인 및 답과 비교
			}
		}

	// 출력부
	cout << K;

	return 0;
}

int DFS(int yy, int xx)
{
	int i, y,x;

	// 방문한 적이 있는 경우. DP값이 이미 계산되어 있다.
	if (DP[yy][xx] >= 1) return DP[yy][xx];

	// 방문 표시
	DP[yy][xx] = 1;  // 들어온 위치에서 판다가 1일은 살 수 있다.

	// 다음 이동 위치 확인
	for (i = 0; i < 4; i++)
	{
		y = yy + dy[i];   x = xx + dx[i];

		// 맵 범위 내에 있는 경우
		if (y > 0 && x > 0 && y <= n && x <= n)
		{
			// 이동하려는 위치가 대나무가 더 많은 지역일 경우
			if (map[yy][xx] < map[y][x])
			{
				// i문으로 각 자식노드 방향에서의 max값을 DP에 저장한다. 참고로 자식노드보다 1일은 더 살 수 있음
				DP[yy][xx] = max(DP[yy][xx], DFS(y, x) + 1);
			}
		}
	}
	// 계산된 자신의 DP값 반환
	return DP[yy][xx];
}

