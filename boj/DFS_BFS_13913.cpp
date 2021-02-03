/* DFS_BFS_13913, 숨바꼭질4 */
/* 포인트
 (BFS) 문제
 1. 방문 경로를 벡터로 큐에 저장하지 않고 (메모리 초과날 수 있다), "전역변수"인 "방문확인 배열"에 이전 위치 값을 저장해서 처리 했다
    BFS로 큐에서 꺼내면 저 방문하는 경우의 큐가 나오게 되므로, 방문배열에 먼저 나오는 순으로 이전 위치 값을 저장하고 방문배열 값이 0이 아니면 큐에 넣지 않으면 된다
 2. visited 값을 초기값 0으로 그대로 사용했는데, "0을 방문했던 경우"와 "방문하지 않았던 경우" 2가지 의미가 겹쳐버려서.. 한 번 틀렸다
    따라서 "방문하지 않았던 경우"를 visited 값 -1이라고 가정해서 사용해야한다. 따라서 memset으로 -1 값으로 초기화 했음
 3. 출력할 때 stack 사용한 경우에 비해서 vector 사용하는 경우가 속도가 2배 가까이 더 빠른 것을 확인했다..
*/
#include <iostream>
#include <queue>
#include <string.h>  // memset()
#include <tuple>  // tie()
#include <vector>
using namespace std;

typedef struct node{
    int x,cnt;
}node;

queue<node> q;
int visited[100010];
int N,K, ans;

void BFS(void);
void Print(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>N>>K;
    
    // 실행부
    memset(visited, -1, sizeof(visited));  // 초기값 0을 그대로 사용해버리면 (0을 방문한 경우)랑 의미가 겹쳐서 안된다...
    BFS();
    
    // 출력부
    Print();
    
    return 0;   
}

void BFS()
{
    int i, x, xx,cnt;
    
    // 초기값 넣음
    visited[N]=-2;  // 초기 위치의 방문 값 -2 넣어줌
    q.push({N,0});
 
    while(!q.empty())
    {
        tie(xx,cnt) = {q.front().x, q.front().cnt};
        q.pop();
        
        // 종료 조건
        if(xx==K){ans=cnt; return;}

        // 자식 노드 호출
        for(i=0; i<3; i++)
        {
            if(i==0) x = xx-1;
            if(i==1) x = xx+1;
            if(i==2) x = 2*xx;
            
            // 다음 위치로 이동할 수 없는 경우
            if(x<0 || x>100000) continue;  // 범위를 벗어나는 경우
            if(visited[x] != -1) continue;  // 방문한 적이 있는 경우
            
            // 다음 위치로 이동할 수 있는 경우
            visited[x]=xx;  // 이동하려는 위치의 방문 배열에 이전에 있었던 위치 값을 저장 해준다
            q.push({x,cnt+1});
        }
    }
}

void Print()
{
    vector<int> s;
    int i, a,len;
    
    // 시간 출력
    cout<<ans<<"\n";
    
    // 스택에 이전 위치를 추적하여 담는다
    a = K;  // 스택 초기 값
    while(a != -2 )
    {
        // 스택에 넣어준다
        s.push_back(a);
        
        // 이전 위치로 이동
        a = visited[a];
    }
    
    // 스택에 이전 위치를 꺼내서 출력
    len = (int)s.size();
    for(i=len-1; i>=0; i--)
        cout<<s[i]<<" ";
}
