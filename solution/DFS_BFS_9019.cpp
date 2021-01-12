/* DFS_BFS_9019, DSLR */
/* 포인트
 불필요한 string 사용을 빼야한다.. 처음에 command[] 부분에도 string으로 정의했는데
 command가 자식호출하는 for문에서 매번 string끼리 비교하게 되는데 이게 시간을 엄청 잡아먹는다
 제한시간이 6초인데도 시간초과가 난거 보면 불필요한 "string 비교 부분" 최대한 사용하지 말아야함
 
*/
#include <iostream>
#include <queue>
#include <string>
#include <utility>  // pair<>
using namespace std;

int visited[10100];
queue<pair<int,string>> q;  // <값, 지나온명령어들>
int T,A,B;
char command[4] = {'D','S','L','R'};  // 명령어 저장
string ans;

void BFS(void);
void Reset(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>T;

    // 실행부
    while(T--)
    {
        cin>>A>>B;

        BFS();
        Reset();

        cout<<ans<<endl;
    }

    return 0;
}

void BFS()
{
    int i, nextVal, val;
    string str;
    char cmd;

    // 초기화 (시작 값 넣어줌)
    visited[A]=1;
    q.push({A,""});

    while( !q.empty() )
    {
        val = q.front().first;
        str = q.front().second;
        q.pop();

        // 종료조건
        if(val==B) {ans=str; return;}  // 정답에 도달할 경우. 지나온 명령어들 답에 넣어줌

        // 다음 자식 노드 탐색
        for(i=0; i<4; i++)
        {
            cmd = command[i];

            // 커맨드에 따른 다음 값 계산
            if(cmd == 'D') nextVal = (2*val)%10000;
            if(cmd == 'S') nextVal = (val==0) ? 9999 : val-1;
            if(cmd == 'L') nextVal = (val%1000)*10 + val/1000;
            if(cmd == 'R') nextVal = (val/10)%1000 + (val%10)*1000;

            // 이미 방문한 곳이라면 지나친다
            if(visited[nextVal]==1) continue;
            visited[nextVal]=1;  // 방문표시

            // 큐에 넣는다.
            q.push({nextVal, str+cmd});  // (지나온 명령어들 + 현재 사용한 명령어) 넣어줌
        }
    }
}

void Reset()
{
    int i;

    // 큐 초기화
    while(!q.empty())
    {
        q.pop();
    }

    // 방문 표시 배열 초기화
    for(i=0; i<10100; i++) visited[i]=0;
}
