#include <iostream>
#include <cstring>  // memset()
#include <vector>
#include <tuple>
#include <algorithm> // max()
using namespace std;

int N,M, num,t;
int map[310][310];
int visited[310][310];
int dx[4]={1,-1, 0, 0};
int dy[4]={0, 0, 1,-1};
vector<tuple<int,int,int>> v;  // <y, x, 0을 마주친 면 갯수>

void DFS(int,int);

int main()
{
    int i,j, yy,xx, down;
    
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>N>>M;
    for(i=0; i<N; i++)
        for(j=0; j<M; j++)
            cin>>map[i][j];
    
    
    // 실행부
    while(1)
    {        
        // DFS 실행
        for(i=0; i<N; i++)
            for(j=0; j<M; j++)
                if(map[i][j]!=0 && visited[i][j]==0)  // 높이 0 아닌데 방문 안한 빙하라면.
                {
                    num++; // 덩어리 횟수 카운트
                    visited[i][j]=1;
                    DFS(i,j);
               }       
        // 년도 증가
        t++;
        
        // 종료 조건, 출력부
        if(num>=2){cout<<t-1; return 0;}  // 녹인게 2 덩어리 이상이였다면. 전년도 출력.
        else if(num==0){cout<<"0"; return 0;}  // 녹일게 더이상 없는데. 위에 종료 조건에 안들어갔다면 0이다.
        
        // 빙하 높이 모두 갱신. (녹여준다)
        for(i=0; i<(int)v.size(); i++)
        {
            tie(yy,xx,down) = v[i];
            map[yy][xx] = max(map[yy][xx]-down, 0);  // 높이 음수 되는 경우 피하려고.
        }
        
        // 변수 값 초기화. 다시 사용해야 하니까.
        memset(visited, 0, sizeof(visited));
        v.clear();
        num=0;
    }
    
    return 0;
}

void DFS(int yy,int xx)
{
    int i, y,x, cnt;
    cnt=0;
    
    // 자식 노드 호출
    for(i=0; i<4; i++)
    {
        y=yy+dy[i];  x=xx+dx[i];
        
        // 종료조건
        if(y<0 || x<0 || y>=N || x>=M) continue;  // 맵을 벗어나는 경우 skip
        if(map[y][x]==0){cnt++; continue;}  // 이동하려는 곳이 0이면 cnt증가 후 skip
        if(visited[y][x]==1) continue;  // 방문 했던 경우 skip.
        
        // 자식 노드 호출.
        visited[y][x]=1;
        DFS(y,x);
    }
    
    // 빙하를 녹여야 하는 위치,높이 저장. 한꺼번에 갱신해서 그려주어야 한다. 그래야 0인 면 갯수 제대로 파악.
    v.push_back({yy,xx, cnt});
}
