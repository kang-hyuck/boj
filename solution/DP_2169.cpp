/* DP_2169, 로봇 조종하기 */
/* 포인트
 부모노드에서 자식노드로 위치에 진입할 때 부모노드에서 자식노드로 향했던 방향 정보가
 필요하다. 그 방향에따라 자식노드에서 또 자식노드 호출할 때 호출될 수 있는 자식노드의 경우의 수가 달라지기 때문.
 자식 노드에서 반환하는 값들 중 최댓값을 자신의 map값에 더해서 자신의 DP에 저장한다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

#define NEGINF -987654321  // DP 값을 최솟값 초기화할 값. -1000*1000*100 보다 작아야 함

int dx[3] = { -1,1,0 }; // 좌,우,하
int dy[3] = { 0, 0,1 };
int map[1010][1010];
int DP[1010][1010][3];  // 위치에서. N,M 까지 도달하는데 생성되는 누적값 중 최댓값 저장
int visited[1010][1010];  // 어느방향으로 위치에 접근했든지 간에 공통으로 방문 유무를 확인해야한다
int N, M;

int DFS(int, int, int);

int main()
{
    int i, j, k;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N >> M;
    for (i = 1; i <= N; i++)
        for (j = 1; j <= M; j++)
        {
            cin >> map[i][j];
            for(k=0; k<3; k++)
            DP[i][j][k] = NEGINF;  // DP를 가장 최솟 값으로 초기화
        }

    // 출력부
    cout << max(DFS(1, 1, 1), DFS(1,1,2));

    return 0;
}

int DFS(int yy, int xx, int dir)
{
    int i, y, x;
    int maxChildDP = NEGINF;  // 자식 노드들 호출할 때 가장 큰 값을 갖는 자식 노드 DP값 택하려고. 걔를 현재 DP에 더할꺼다

    // 종료 조건
    if (yy == N && xx == M) return DP[yy][xx][dir] = map[yy][xx];  // N,M에 도달할 경우 그곳의 값 반환
    if (DP[yy][xx][dir] != NEGINF) return DP[yy][xx][dir]; // 계산이 끝난 곳이라면 계산값 반환

    // 자식호출 조건
    for (i = 0; i < 3; i++)
    {
        y = yy + dy[i];  x = xx + dx[i];

        // 다음 이동할 곳이 맵 벗어나는 경우
        if (y<1 || x<1 || y>N || x>M) continue;

        // 방문한 곳이였다면 못간다
        if (visited[y][x] == 1) continue;

        // 이동할 수 있다면
        visited[yy][xx]=1;  // 부모 방문 표시 넣어줌.
        maxChildDP = max(maxChildDP, DFS(y, x, i));
        visited[yy][xx] = 0;  // 부모 방문 표시 지워줌.
    }
    // 자식 값중 가장 큰 값을 자신의 맵 값에 더해서 반환
    return DP[yy][xx][dir] = map[yy][xx] + maxChildDP;
}
