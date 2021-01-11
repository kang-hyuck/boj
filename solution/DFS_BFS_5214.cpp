/* DFS_BFS_5214, 환승 */
/* 포인트
  많은 edge에 인한 메모리 초과를 피해야 한다. 노드들 사이의 edge를 모두 표현해서 이어주는 것 보다
  중간에 경유지 역할을 하는 새로운 노드(이 경우 하이퍼 터미널)를 만들어서 
  노드들을 이어준다면 edge 갯수를 줄일 수 있다. edge가 너무 많아서 메모리 부족할 경우 고려 가능
  하이퍼 터미널은 우리가 역이라고 가정한거라서.. 지나온 역 카운트할 때 포함하면 안된다
  자식 호출할때 for문에서. cnt를 cnt++로 증가시키면 안된다. 자식 호출할때마다 사용할 변수라서
  그렇게하면 for문 돌때마다 cnt값이 증가되어 버리므로.. 큐에 넣을때 cnt+1 식으로 사용하자
  BFS는 어차피 가장 빨리 도착하는 경로를 따라온 경우 종료되므로. visited[]로 먼저 노드에 올 경우
  다시 큐에 안넣도록 하는게 큐에 들어가는 불필요한 재방문 경로 줄일 수 있다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <utility>  // pair<>
using namespace std;

int N, K, M,  ans;
vector<int> station[102010];
queue<pair<int,int>> q;  // <현재위치,카운트> 저장. 이 경우 위치는 "노드번호"
int visited[102010];

void BFS(void);

int main()
{
	int i, j, temp;
	ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

	// 입력부
	cin >> N >> K >> M;
	for(i=N+1; i<=N+M; i++)   // 하이퍼 터미널을 "역"으로 생각해서. index를 N+1 ~ N+M 까지 부여.
		for (j = 0; j < K; j++)
		{
			cin >> temp;
			station[i].push_back(temp);  // 하이퍼 터미널에 모든 node 연결
			station[temp].push_back(i);  // node를 하이퍼 터미널에 연결
		}
	ans = -1;

	// 실행부
	BFS();

	// 출력부
	cout << ans;

	return 0;
}

void BFS()
{
	int i, num,cnt, nextNum;
	pair<int,int> popped;

	// 초기화. (1번 노드부터 시작)
	visited[1] = 1;
	q.push({ 1,1 });

	while (!q.empty())
	{
		popped = q.front();
		q.pop();

		num = popped.first;
		cnt = popped.second;

		// 도착할 경우
		if (num == N) {ans = cnt;  return;}

		// 다음 노드 탐색
		for (i = 0; i < (int)station[num].size(); i++)
		{
			nextNum = station[num][i];

			// 방문한 곳일 경우 넘긴다
			if (visited[nextNum] == 1) continue;

			// 방문표시
			visited[nextNum] = 1;

			// 다음 노드가 하이퍼 터미널이 아닐 경우만 지나온 역 횟수 카운트
			if (nextNum <= N)
				q.push({ nextNum, cnt + 1 });  // cnt는 항상 이렇게 +1 형태로 적어주자. 자식들이 공통으로 사용하는 변수다.
			else
				q.push({ nextNum, cnt });
		}
	}

	return;
}

