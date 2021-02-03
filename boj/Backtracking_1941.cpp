/* Backtracking_1941, 소문난 칠공주 */
/* 포인트
 (백트랙킹 + 2차원 조합 + BFS) 문제
 1. "T 자 모양 연결" 형태의 "선택"을 하려면. 2차원 "조합"을 사용해서 택할 수 있다. 따라서 DFS 사용 함
 2. 선택한 학생들 위치를 벡터에 넣고, BFS에서 큐에 학생 위치 1개만 넣고 BFS 돌려보아서 7개 택한 위치에 모두 도달하는 지로 연결상태 확인 했음
 3. 연결 상태, 선택한 그룹 수를 "전역변수" (DFS에서는 전역변수 사용가능, BFS에서는 보통 전역변수 사용 불가... 면적 크기 구할때는 BFS에서도 사용 가능.)
*/
#include <iostream>
#include <vector>
#include <tuple>
#include <queue>   // tie()
#include <string.h>  // memset()
using namespace std;

typedef struct node{
    int y, x;
}node;

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0,  0, 1,-1 };
int visited[8][8];  // 학생들끼리 연결 확인 할 때 사용
char map[8][8];
int som, yun;  // som: 이다솜파 수,  yun: 임도연파 수
int ans;
vector<node> v;  // 선택한 학생들 위치 정보 저장
queue<node> q;   // BFS에서 사용

void DFS(int, int);  // 7명 선택할 조합 구현할 때 사용할 DFS
void BFS(void);  // 7명 선택된 학생들의 인접한 연결확인 할 때 사용할 BFS
void Check(void);
void Reset(void);

int main()
{
    int i, j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    for (i = 1; i <= 5; i++)
        for (j = 1; j <= 5; j++)
            cin >> map[i][j];

    // 실행부
    DFS(1, 1);

    cout << ans;

    return 0;
}

void DFS(int yy, int xx)
{
    int i,j;

    // 시뮬레이션 조건
    if (yun + som == 7) { Check(); Reset(); return; }  // 인접해 있는지 확인

    // 자식 노드 호출
    for(i=yy; i<=5; i++,xx=1) // xx=1임 ㄷㄷ
        for (j=xx; j<=5; j++)
        {
            // 선택할 수 없는 경우
            if (yun == 3 && map[i][j] == 'Y') continue;

            // 선택할 수 있는 경우
            if (map[i][j] == 'Y') yun++;
            else if (map[i][j] == 'S') som++;
            v.push_back({ i,j });  // 선택한 학생의 위치 넣어줌

            DFS(i, j+1);  // 다음 선택할 자식노드 인덱스 넣어준다

            v.pop_back();  // 선택한 학생 빼내줌
            if (map[i][j] == 'Y') yun--;
            else if (map[i][j] == 'S') som--;
        }
}

void Check(void)
{
    int i;

    // 선택한 학생들의 위치들을 모두 1로 체크 (방문하면서 0으로 지울 것임)
    for (i = 0; i < (int)v.size(); i++)
        visited[v[i].y][v[i].x] = 1;
    q.push(v[0]);  // 1개만 큐에 담는다 (학생 위치 1개만으로 모든 학생들 위치 방문 할 수 있어야 함)

    // BFS 실행 (7명 학생 연결 확인)
    BFS();

    // 모든 학생들 위치 방문 여부 확인
    for (i = 0; i < (int)v.size(); i++)
        if (visited[v[i].y][v[i].x] == 1) return;   // 1개라도 체크가 안지워진 경우 모두 연결된 위치가 아니므로 종료

    // 연결된 경우 여기로 옴 (체크가 모두 지워진 경우)
    ans++;

    return;
}

void Reset(void)
{
    memset(visited, 0, sizeof(visited));
}

void BFS()
{
    int i, y,x,yy, xx;

    // 위치 1개만 넣은 것을 BFS 돌려서 모든 위치와 연결 되는 지 확인 (BFS 끝났을 때 각 위치마다 1로 체크한게 지워져야함)
    while (!q.empty())
    {
        tie(yy, xx) = { q.front().y, q.front().x };
        q.pop();

        for (i = 0; i < 4; i++)
        {
            y = yy + dy[i];   x = xx + dx[i];

            // 맵 벗어나는 경우
            if (y < 1 || x < 1 || y>5 || x>5) continue;
            if (visited[y][x]==0) continue;   // 1로 체크 해놓은 위치가 아닌 경우

            // 해당 방향으로 체크 해놓은 것을 지워줌
            visited[y][x] = 0;
            q.push({y,x});  // 큐에 넣어준다
        }
    }
}
