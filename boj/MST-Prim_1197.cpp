#include <stdio.h>
#include <vector>
#include <queue>
#include <utility>  //  pair
using namespace std;

int sum,    V,E;    //  V: 정점의 갯수,  E: 간선의 갯수

priority_queue< pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>> > pq;    //  min-priority queue
vector<pair<int,int>> node[10010];    //  index: vertex번호,    저장값: edge 정보
int visited[10010]; //  방문정보

int main()
{
    int i,  A,B,C,  popped_weight, popped_vertex;
    scanf("%d %d", &V,&E);

    //  입력부,    edge정보를 넣어준다
    for(i=0; i<E; i++)
    {
        scanf("%d %d %d", &A,&B,&C);    // 정점: A,B  가중치: C
        node[A].push_back(pair(C,B));   //  양방향 edge정보를 넣어줌,    순서:<weight,to>
        node[B].push_back(pair(C,A));
    }

    //  초기값,    pq에 초기값 넣어주기 (임의값으로 마지막 입력값을 넣어주었음)
    visited[A] = 1;
    for(i=0; i<(int)node[A].size(); i++)
    {
        pq.push( pair(node[A][i].first, node[A][i].second) );
    }

    //  실행부, pq에 edge 정보를 넣고 최소weight값을 꺼내고 누적하는 작업을 해준다.
    while( !pq.empty() )
    {
        popped_weight = pq.top().first;
        popped_vertex = pq.top().second;
        pq.pop();

        //  방문했던 node인지 확인
        if( visited[popped_vertex] == 1 )
            continue;

        visited[popped_vertex] = 1;
        sum += popped_weight;   //  누적값 계산

        //  선택된 node와 연결된 edge 정보를 pq에 넣어줌
        for(i=0; i<(int)node[popped_vertex].size(); i++)
        {
            pq.push( pair(node[popped_vertex][i].first, node[popped_vertex][i].second) );
        }

    }

    printf("%d", sum);

    return 0;
}
