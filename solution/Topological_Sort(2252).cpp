#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

vector<int> node[32010];
int indegree[32010];
priority_queue<int, vector<int>, greater<int> > pq;     // 최대 pq (오름차순),    * pq의 default값은 내림차순이다

int N,M;    // N: 학생수,  M: 비교 횟수

int main()
{
    int i,  A,B,  popped,nxt;
    scanf("%d %d", &N, &M);

    // 입력부 (1.edge넣기, 2.in-degree증가, 3.in-degree 0인 값 pq에 넣기)
    for(i=0; i<M; i++)
    {
        scanf("%d %d", &A, &B);
        node[A].push_back(B);   //  A에서 B로 향하는 edge 넣어줌 (A->B)
        indegree[B]++;          //  in-degree 증가
    }   
    for(i=1; i<=N; i++)
    {
        if( indegree[i] == 0 )
            pq.push(i);
    }

    // 실행부 (1.pq에서 in-degree 0인 값 꺼내고 출력, 2.여기서 향하는 node 모두 in-degree 감소, 3.in-degree 0이면 pq에 넣기)
    while( !pq.empty() )
    {
        popped = pq.top();
        pq.pop();

        printf("%d ", popped);

        for(i=0; i<(int)node[popped].size(); i++)
        {
            nxt = node[popped][i];
            indegree[nxt]--;
            if( indegree[nxt] == 0 )
                pq.push(nxt);
        }
    }
}
