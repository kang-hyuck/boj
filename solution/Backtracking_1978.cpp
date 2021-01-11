/* Backtracking_1987, 알파벳 */
/* 포인트
 현재 그 알파벳이 존재하는지. 빠른 확인을 위해서 행렬 사용했다.
 (벡터같은 곳에 담아서 for문 돌리면 시간초과 날듯..)
 자식노드를 호출하기 전에 visited[]에 자식노드에서의 문자값을 등록해주고
 다시 부모노드로 돌아왔을때 자식노드에서 사용했던 문자값을 빼내준다.
 생각 해볼점은.. 맵이 조금 더 컸다면 3차원 DP (부모노드->자식노드로 들어가는 방향에 따라
 자식노드에서 또 자식노드를 호출하는 경우의 수가 달라지므로..) 사용해야 함
*/

#include <iostream>
#include <algorithm>
using namespace std;

int R,C, ans;
char map[25][25];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0,  0, 1,-1};
int visited[30];  // 방문 확인용

void DFS(int , int, int);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int i,j;
    
    // 입력부
    cin>>R>>C;
    for(i=1; i<=R; i++)
        for(j=1; j<=C; j++)
            cin>>map[i][j];
    
    // 실행부
    visited[map[1][1]-'A']=1;  // 맨 첫번째 알파벳을 담아준다
    DFS(1,1,1);
    
    // 출력부
    cout<<ans;

    return 0;
}

void DFS(int yy, int xx, int cnt)
{
    int i, y,x;
    
	// 정답 값 갱신 (자식 노드 호출하는 곳에서. 이동가능할 경우만 호출하므로 여기서 cnt 값 비교 해도 된다)  
    ans = max(ans,cnt);
    
    for(i=0; i<4; i++)
    {
        y = yy + dy[i];   x = xx + dx[i];
        
        // 맵 벗어나는 경우
        if(y<1 || x<1 || y>R || x>C) continue;
        
        // 이미 방문한적 있는 문자라면
        if(visited[map[y][x]-'A']==1) continue;
        
        // 다음 이동 범위가 맵 내에 있는 경우
        visited[map[y][x]-'A']=1;
        DFS(y,x, cnt+1);
        visited[map[y][x]-'A']=0;  // 자식에서 부모로 돌아왔으므로 자식의 문자값에 해당되는 방문 표시를 다시 꺼내준다.
    }

}
