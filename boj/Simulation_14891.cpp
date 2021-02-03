/* Simulation_14891, 톱니바퀴 */
/* 포인트
  DFS 내에서 "자식호출"을 다 하고 나서 부모 톱니바퀴를 회전 시켜야한다.
  현재 톱니바퀴 에 닿아있는 극성 N/S에 따라서 옆에 톱니바퀴의 회전여부 및 방향이 결정되기 때문이다.
  따라서 자식의 회전 여부 및 방향이 다 결정되고 나서(자식 호출이 끝나고나서), 부모 톱니바퀴를 Roate() 해주었다
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <deque>
using namespace std;

deque<int> dq[5];
int visited[5];
int K, ans;

void Start(void);
void DFS(int, int);
void Rotate(int, int);
int MakeDir(int, int, int, int);

int main()
{
    int i,j,  temp, weight;
    //ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    for(i=1; i<=4; i++)
        for(j=0; j<8; j++)
        {
            scanf("%1d", &temp);
            dq[i].push_back(temp);
        }

    // 실행부
    Start();

    // 출력부
    weight=1;
    for(i=1; i<=4; i++)
        {ans += weight*dq[i][0];  weight *= 2;}  // 12시 방향 값 전부 더함
    cout<<ans;

    return 0;
}

void Start()
{
    int num,dir;

    // 회전 횟수 저장
    cin>>K;

    while(K--)
    {
        // 바퀴 번호, 회전 방향
        cin>>num;   cin>>dir;

        // 회전 시작
        visited[num]=1;
        DFS(num, dir);

        // 방문 기록 초기화
        memset(visited, 0, sizeof(visited));
    }
}

void DFS(int num, int dir)
{
    int i, nextNum,nextDir;

    // 종료 조건
    if(dir==0) return;  // 회전 하지 않는 경우

    // 다음 자식 노드 호출
    for(i=0; i<2; i++)
    {
        // 다음 바퀴 번호
        if(i==0) nextNum = num + 1;
        if(i==1) nextNum = num - 1;

        // 다음 바퀴 번호로 이동할 수 없는 경우
        if(nextNum<1 || nextNum>4) continue;  // 바퀴 번호 범위를 벗어나는 경우
        if(visited[nextNum] == 1)  continue;  // 방문한 적이 있는 경우

        // 다음 바퀴의 회전 방향 계산
        nextDir = MakeDir(i, num, nextNum, dir);   // (오른쪽/왼쪽, 현재 바퀴, 다음 바퀴, 현재 회전 방향)

        // 다음 바퀴 번호로 이동할 수 있는 경우
        visited[nextNum]=1;
        DFS(nextNum, nextDir);
    }

    // 회전 (!!! 현재 톱니의 "상태"에 따라서. "양쪽 자식 노드 모두" 회전 방향 정보가 계산 되므로. 자식노드의 회전 정보 부터 결정 된 뒤, 현재 톱니를 회전 시켜야함)
    Rotate(num, dir);
}

int MakeDir(int i, int num, int nextNum, int dir)
{
    if(i==0)  // 다음 바퀴가 오른쪽에 있는 경우
    {
        // 회전 하지 않는 경우
        if(dq[num][2] == dq[nextNum][6]) return 0;
    }
    if(i==1)  // 다음 바퀴가 왼쪽에 있는 경우
    {
        // 회전 하지 않는 경우
        if(dq[num][6] == dq[nextNum][2]) return 0;
    }

    // 회전 하는 경우 (옆에 바퀴는 현재 바퀴의 반대방향으로 회전함)
    return -1*dir;
}

void Rotate(int num, int dir)
{
    int temp;

    if(dir==1)  // 시계방향으로 회전하는 경우
    {
        // 뒤에서 꺼낸다
        temp = dq[num].back();
        dq[num].pop_back();

        // 앞으로 넣는다
        dq[num].push_front(temp);
    }

    if(dir==-1)  // 반시계방향으로 회전하는 경우
    {
        // 앞에서 꺼낸다
        temp = dq[num].front();
        dq[num].pop_front();

        // 뒤로 넣는다
        dq[num].push_back(temp);
    }
}

