/* Backtracking_15684, 사다리 조작 */
/* 포인트
 (백트랙킹 + 시뮬레이션 + 2차원 조합) 문제
 1. 2차원 조합을 구현해야 하므로 DFS()의 인자에 자식 노드가 조사를 시작할 yy,xx 좌표를 채워 넣어준다
    (주의) 자식노드 호출 하는 2중 for문에서, 처음 "열"방향 for문에서 인자로 받은 xx 값부터 자식노드를 조사하지만,
    "열"방향 for문(j문)이 끝나고 "행"방향 for문(i문)으로 한번 들어오고 나서 다시 "열"방향 for문(j문)으로 들어갈 때 j값은 "0부터" 시작해야한다.
    따라서 "행"방향 for문(i문) 끝부분에.. "i++, xx=0"으로 적어주어서 i문 들어왔다가 j문 들어갈 경우부터는 j가 0부터 시작하게 했음
 2. 사다리 왼쪽,오른쪽... 각각 1,-1을 넣어주어서.. 시뮬레이션 할 때 0이 아닌값 있으면 자신의 x값에 그 값을 더하게 해서 움직여 주었다
    이렇게 사다리 1개 만들 때마다 배열에 값 2개 적어넣어주면.. DFS로 자식노드 호출할 때 적어주어야 할게 많아져서 귀찮지만..
    시뮬레이션 구현 하는 부분이 편해져서 장점이라고 할 수 있다..
 3. 사다리 3개 초과로 사용하는 경우는 조사할 필요가 없다.. 여기까지 올 경우 기존 ans에 있는 -1 or 정답 값을 반환하면 됨
 4. DFS 안에서... cnt값에 상관없이 "시뮬레이션"함수를 호출하게 해서.. 사다리 갯수 0,1,2,3개 인 경우 모두 시뮬레이션으로 확인하게 했다.
*/
#include <iostream>
#include <algorithm>
using namespace std;

int map[35][15];
int N, M, H; // 세로선의 수, 가로선의 개수, 세로선 위에 가로선을 놓을 수 있는 
int ans;

void DFS(int, int, int);
int Start(void );

int main()
{
    int i,j, a,b;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N >> M >> H;
    for (i = 1; i <= M; i++)
    {
        cin >> a >> b;
        map[a][b] = 1;    // 사다리 왼쪽을 1
        map[a][b+1] = -1; // 사다리 오른쪽을 -1  (양쪽에 값을 이렇게 넣어주는게 시뮬레이션 구현할 때 편하다)
    }
    ans = -1;

    // 실행부
    DFS(1,1, 0);

    // 출력부
    cout << ans;

    return 0;
}

void DFS(int yy, int xx, int cnt)
{
    int i, j, res;

    // 종료 조건
    if (cnt > 3) return;  // 사다리 갯수가 3개 보다 크면 종료

    // 시뮬레이션 시작 (0,1,2,3개 놓은 경우 전부 시뮬레이션 해본다)
    res = Start();

    // 시뮬레이션 결과 확인
    if (res == 1 && ans == -1) ans = cnt;  // ans가 맨 초기값일 경우 ans에 cnt 넣어줌
    else if (res == 1) { ans = min(ans, cnt); return;}   // 이미 현재 사다리 연결이 성공적인데.. 아래로 내려가서 사다리 더 연결한 것 확인할 필요가 없다... 정답 조건 아님..

    // 자식 노드 호출  (2차원 배열에서 "조합" 구현할 때.. 처음에는 j가 xx에서 시작하지만 i 반복문 돌 때 xx가 다시 0부터 시작해야한다.. 따라서 i반복문에 "xx=0"를 넣어준다)
    for (i = yy; i <= H; i++,xx=0)  // "조합" 구현해야 하므로, 부모 노드에서 자식 노드에서 사다리 그릴 시작 위치를 준다(yy,xx) 여기서 부터 그리면 됨
        for (j = xx; j <= N - 1; j++)   // 사다리 "왼쪽"을 기준으로 j를 움직이므로 N-1 까지만 이동
        {
            // 사다리 그릴 수 없는 경우
            if (map[i][j] != 0 || map[i][j+1] != 0) continue;  // 사다리 왼쪽||오른쪽 연결이 있는 위치인 경우 넘긴다

            // 사다리 그릴 수 있는 경우
            map[i][j] = 1;  map[i][j + 1] = -1;   // 사다리 왼쪽,오른쪽을 그린다
            DFS(i, j + 1, cnt+1);   // 자식 노드 호출 (이중for문 가장 안 쪽이 "열"이므로, 자식 노드에서는 부모노드 보다 열 방향으로 1 앞서서 그리면 된다)
            map[i][j] = 0;  map[i][j + 1] =  0;   // 조사 끝나고 부모노드로 돌아올 경우, 사다리 그렸던거 지워준다
        }
}

int Start()
{
    int i, y,x;

    // 1~N 조사
    for (i = 1; i <= N; i++)
    {
        // 시작 위치 (맨 위에서 부터)
        y = 1;  x = i;  // 숫자 i의 시작 위치

        // 내려 가기 시작
        while (1)
        {
            // 종료 조건
            if (y > H) break; // 맨 아래 도착한 경우 (참고로 H행 까지 사다리 놓을 수 있다, 따라서 H 보다 클 때 break)

            // 이동 하기
            if (map[y][x] != 0) x = x + map[y][x];  // 사다리 있는 경우. 좌,우로 이동
            y = y + 1;  // 아래로 내려감
        }

        // 내려온 결과 확인, 시작 번호와 다른 번호로 내려 왔다면 -1 반환
        if (x != i) return -1;
    }
    // 모든 번호 (1~N)이 자신의 번호로 내려왔다면 1 반환
    return 1;
}
