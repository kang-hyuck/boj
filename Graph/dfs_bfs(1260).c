#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

void dfs(int);
void bfs(void);

vector<int> connected[10010];
queue<int> q;
int visited[1010][2];   //  0:dfs에서 사용    1:bfs에서 사용

int N,M,V;   // N:정점 갯수  M:간선 갯수  V:시작 정점 번호


int main()
{
    int i,  a,b;
    scanf("%d %d %d", &N,&M,&V);
    
    
    // 입력부
    for(i=0; i<M; i++)
    {
        scanf("%d %d", &a,&b);
        connected[a].push_back(b);  //  양방향 edge이므로
        connected[b].push_back(a);
    }
    
    // 정렬 (연결된 노드중 낮은 노드 번호부터 꺼내야 하므로)
    for(i=0; i<N; i++)
        sort(connected[i].begin(), connected[i].end());
    
    
    //dfs
    dfs(V);
    
    printf("\n");
    
    //bfs
    bfs();


    return 0;
}



void dfs(int node)
{
    int i;

    if(visited[node][0] == 1)
        return;
    
    visited[node][0] = 1;
    printf("%d ", node);
    
    for(i=0; i<(int)connected[node].size(); i++)
        dfs(connected[node][i]);

    return;
}


void bfs()
{
    int i,  popped;

    //  초기값
    visited[V][1] = 1;
    q.push(V);


    while( !q.empty() )
    {
        popped = q.front();
        q.pop();
        
        printf("%d ", popped);
        
        for(i=0; i<(int)connected[popped].size(); i++)
        {
            if( visited[connected[popped][i]][1] == 0 )
            {
                visited[connected[popped][i]][1] = 1;
                q.push(connected[popped][i]);
            }
        }
    }
    
    return;
}

