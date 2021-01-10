/* DP_17070, 파이프 옮기기1 */
/* 포인트
 방향에 따른 3차원 DP로 풀었다.
 rotateDir을 2차원 배열로 잡기에는 뒤에 원소가 2개, 3개인 경우로 달라서.
 vector 배열로 잡아서 해결했다. rotateDir은 DFS 안에서 다음 자식노드 호출할때
 다음 자식 노드로 이동 가능한 "방향의 dx,dy의 index"를 담아 놓았다
 다음 자식노드 호출하려고 할 때. 현재 노드의 방향 dir에 따라서 달라지므로.
 rotateDir 이용해서 해결한거다. 얘를 불러다가 dx,dy의 index 안에 넣으면 됌

 DP를 -1로 초기화 해야한다. 0값을 그대로 사용 하는 경우 못움직이는 경우 DP값이 0 이랑
 방문안한경우(자식노드 확인해봐야하는 경우)도 0이 되어서 DP 의미가 사라진다.
 현재 노드에서의 DP값은 자식 노드들의 모든 DP 결과 누적값이다.

 파이프 오른쪽 끝부분을 기준으로y,x 이동했다. 얘가 N,N에 도달하면 1 반환
 하면 된다. 그러면 올라가면서 다른 자식 노드들이랑 누적되어서 최종 부모노드에게로 가게됨.
*/
#include <iostream>
#include <vector>
using namespace std;

int map[20][20];
int DP[20][20][3];  // DP[y][x][방향]
int dx[3] = { 1,0,1 };  // 우,하,대각
int dy[3] = { 0,1,1 };
vector<int> rotateDir[3] = { {0,2}, {1,2}, {0,1,2} };  // 방향에 따른 회전 가능 방향들 {우,대각},{하,대각},{우,하,대각}
int N;

int DFS(int, int, int);  // (y,x,방향)

int main()
{
	int i, j, k;
	ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

	// 입력부
	cin >> N;
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			cin >> map[i][j];

	//// DP값 -1로 초기화 한다.. N,N으로 못가는 경우(0)이랑 구분하기 위해서 -1로 초기화
	for (i = 1; i <= N; i++)
		for (j = 1; j <= N; j++)
			for (k = 0; k < 3; k++)
				DP[i][j][k] = -1;

	// 출력부
	cout << DFS(1, 2, 0);  // (1,1, 우)

	return 0;
}

int DFS(int yy, int xx, int dir)
{
	int y,x;

	// 종료 조건
	if (yy == N && xx == N) return 1;  // 도착점에 도착한 경우
	if (DP[yy][xx][dir] != -1) return DP[yy][xx][dir];

	// 방문표시
	DP[yy][xx][dir] = 0;

	for (auto i : rotateDir[dir])  // 방향에 따라 각 회전방향조사 (파이프 오른쪽끝 위치 기준)
	{
		y = yy + dy[i];   x = xx + dx[i];

		// 범위 밖에에 있는 경우
		if (y < 1 && x < 1 && y > N && x > N) continue;  // 다른 회전 방향 조사 하도록 continue로 빠져나간다
		
		// 파이프 끝에 벽이 있는 경우
		if (map[y][x] == 1) continue;

		// 대각선 방향인 경우. 파이프 오른쪽 끝의 왼쪽,위 부분도 벽 있는지 추가 확인
		if (i == 2 && (map[y][x - 1] == 1 || map[y - 1][x] == 1) ) continue;  // ㅠ.ㅠ ||이랑 && 이랑 같이 쓰면 위험하다.. 괄호 안치면 결과 다름

		// 이동 가능한 경우
		DP[yy][xx][dir] += DFS(y, x, i);  // 회전 방향별로 자식노드 호출하고 자신 DP에 저장
	}
	// 계산끝난 자기 DP 값 반환한다.
	return DP[yy][xx][dir];
}

