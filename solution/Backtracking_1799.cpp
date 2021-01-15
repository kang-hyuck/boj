/* Backtracking_1799, 비숍 */
/* 포인트
(백트래킹 + 2차원 조합) 문제
 1. 시간초과를 피해야 한다. 흑,백 칸에 있는 비숍은 서로 잡을 수 없음을 착안해서 각각의 경우 최대 비숍 갯수를 DFS로 구한뒤 더한다
*/
#include <iostream>
#include <algorithm>
using namespace std;

int dx[2] = {1, -1};  // 맨 위에 비숍부터 아래 방향으로만 확인하면 된다.
int dy[2] = {1,  1};
int map[15][15];
int N, ans, maxCnt;

void DFS(int, int, int, int);
int Start(int);

int main()
{
    int i, j, ans_odd;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N;
    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 1) maxCnt++;  // 놓을 수 있는 갯수 카운트
        }
    ans = 0;

    // 실행부
    DFS(1, 1, 0, 3);  // 흑(3) 칸에 비숍 놓을 수 있는 최대 갯수 확인
    ans_odd = ans;   ans = 0;  // 흑(3) 칸의 DFS 결과를 ans_odd에 담아두고 ans 초기화 후 다시 백(2) 칸의 경우 실행
    DFS(1, 1, 0, 2);  // 백(2) 칸에 비숍 놓을 수 있는 최대 갯수 확인

    // 출력부
    cout << (ans_odd + ans);  // 흑,백 각각의 경우 칸에서 놓을 수 있는 최대 비숍 갯수를 더해서 출력

    return 0;
}

void DFS(int yy, int xx, int cnt, int mode)
{
    int i, j;

    // 종료조건
    if (cnt > maxCnt/2 + 1) return;  // 놓을 수 있는 갯수 넘어서 들어오면 종료 (흑,백 칸 반반씩 나누었으므로.. maxCnt/2 + 1 까지만 확인)
    if (Start(mode) == -1) return;  // 이미 서로 잡을 수 있는 비숍이 있다면... 아래에서 자식 호출(추가 비숍 생성)을 더 할 필요가 없음

    // 비숍이 서로 잡히지 않는 경우
    ans = max(ans, cnt);  // 최대 비숍 갯수 갱신

    // 자식 호출
    for (i = yy; i <= N;  i++,xx=0)  // 2차원 조합이라서 i++ 뒤에 xx=0 넣어줌
        for (j = xx; j <= N; j++)
        {
            // 비숍을 놓을 수 없는 자리인 경우
            if (map[i][j] == 0) continue;
            if (mode == 3 && i%2 == 1 && j%2 == 0) continue;  // (흑,3) 홀수행, 짝수열
            if (mode == 3 && i%2 == 0 && j%2 == 1) continue;  // (흑,3) 짝수행, 홀수열
            if (mode == 2 && i%2 == 1 && j%2 == 1) continue;  // (백,2) 홀수행, 홀수열
            if (mode == 2 && i%2 == 0 && j%2 == 0) continue;  // (백,2) 짝수행, 짝수열

            // 비숍을 놓을 수 있는 자리인 경우
            map[i][j] = mode;   // 비숍을 놓는다
            DFS(i, j + 1, cnt + 1, mode);
            map[i][j] = 1;
        }
}

int Start(int mode)
{
    int i, j, k;
    int y, x;

    // 맵 전체를 돌면서 비숍 있는 경우 아래 대각선 방향으로 이동하면서 잡을 수 있는 비숍 있는지 확인
    for(i=1; i<=N; i++)
        for (j = 1; j <= N; j++)
        {
            // 비숍 없으면 넘긴다
            if (map[i][j] == 0 || map[i][j] == 1 || map[i][j] != mode)  continue;

            // 비숍 있는 경우 2방향으로 시뮬레이션 실행
            for (k = 0; k < 2; k++)
            {
                // 초기 위치 넣어줌
                y = i;  x = j;

                while (1)
                {
                    y = y + dy[k];   x = x + dx[k];

                    // 다음 위치 이동 가능성 확인
                    if (y<0 || x<0 || y>N || x>N) break;  // 맵 밖을 벗어나는 경우
                    if (map[y][x] == mode) return -1;  // 잡을 수 있는 비숍이 있는 경우 종료
                }
            }
        }
    // 비숍이 서로 잡히지 않는 경우 1 반환
    return 1;
}



/* 시간 초과난 코드 (처음에 고안한 코드.. 숫자 작을 때는 다 맞음)


#include <iostream>
#include <algorithm>
using namespace std;

int dx[2] = {1, -1};  // 맨 위에 비숍부터 아래 방향으로만 확인하면 된다.
int dy[2] = {1,  1};
int map[15][15];
int N, ans, maxCnt;

void DFS(int, int, int);
int Start(void);

int main()
{
    int i, j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N;
    for (i = 1; i <= N; i++)
        for (j = 1; j <= N; j++)
        {
            cin >> map[i][j];
            if (map[i][j] == 1) maxCnt++;  // 놓을 수 있는 갯수 카운트
        }
    ans = 0;

    // 실행부
    DFS(1, 1, 0);

    // 출력부
    cout << ans;

    return 0;
}

void DFS(int yy, int xx, int cnt)
{
    int i, j;

    // 종료조건
    if (cnt > maxCnt)  return;  // 놓을 수 있는 갯수 넘어서 들어오면 종료
    if (Start() == -1) return;  // 이미 서로 잡을 수 있는 비숍이 있다면... 아래에서 자식 호출(추가 비숍 생성)을 더 할 필요가 없음

    // 비숍이 서로 잡히지 않는 경우
    ans = max(ans, cnt);  // 최대 비숍 갯수 갱신

    // 자식 호출
    for (i = yy; i <= N;  i++,xx=0)
        for (j = xx; j <= N; j++)
        {
            // 비숍을 놓을 수 없는 자리인 경우
            if (map[i][j] == 0) continue;

            // 비숍을 놓을 수 있는 자리인 경우
            map[i][j] = 2;   // 비숍을 놓는다 (2로 표현)
            DFS(i, j + 1, cnt + 1);
            map[i][j] = 1;
        }
}

int Start()
{
    int i, j, k;
    int y, x;

    // 맵 전체를 돌면서 비숍 있는 경우 아래 대각선 방향으로 이동하면서 잡을 수 있는 비숍 있는지 확인
    for(i=1; i<=N; i++)
        for (j = 1; j <= N; j++)
        {
            // 비숍 없으면 넘긴다
            if (map[i][j] == 0 || map[i][j] == 1)  continue;

            // 비숍 있는 경우 4방향으로 시뮬레이션 실행
            for (k = 0; k < 2; k++)
            {
                // 초기 위치 넣어줌
                y = i;  x = j;

                while (1)
                {
                    y = y + dy[k];   x = x + dx[k];

                    // 다음 위치 이동 가능성 확인
                    if (y<0 || x<0 || y>N || x>N) break;  // 맵 밖을 벗어나는 경우
                    if (map[y][x] == 2) return -1;  // 잡을 수 있는 비숍이 있는 경우 종료
                }
            }
        }
    // 비숍이 서로 잡히지 않는 경우 1 반환
    return 1;
}
*/



