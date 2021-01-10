/* DP_12865, 평범한 배낭 */
/* 포인트
 2차원 DP 문제. i행이 1~i번째 물건들 사용할 경우, j가 가방의 수용 가능한 무게 의미.
 i번째 물건의 "무게" 보다 가방의 수용 가능한 크기j가 작은 경우는 i번째 물건을
 사용하지 못하므로 i-1번째 물건을 사용하여 수용 가능한 크기 j 가방 사용할 경우
 최대 가치값인 DP[i-1][j] 값을 DP[i][j]에 그대로 담아주면 된다.
 반복문에서 j크기가 커져서 i번째 물건을 사용가능 하게 되는 경우는
 i번째 물건을 사용했으므로 나머지남은 크기 j-(i번째 무게) 부분을 0~i-1번째 무게로
 채울 수 있는 경우랑 비교하면 된다. DP[i-1][j-(i번째 무게)] + (i번째 가치)
*/
#include <iostream>
#include <utility>  // pair<>
#include <algorithm>
using namespace std;

int DP[110][100010];  // 물품 x 무게
int N, K;
pair<int, int> item[110];  // <W,V>

int main()
{
    int i,j;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N >> K;
    for (i = 1; i <= N; i++)
        cin >> item[i].first >> item[i].second;

    // 실행부
    for(i=1; i<=N; i++)
        for (j=1; j<=K; j++)   // j: 가방의 담을 수 있는 무게
        {
            // DP값 갱신 (i번째 물건을 담을 수 있게 되는 경우 max값 확인해봐야함 / i번째 물건 담을 수 없는 경우는 i-1번째 물건 담았을때 최댓값 넣으면 됨)
            if (j - item[i].first >= 0)  // i번째 아이템의 무게를 담을 수 있는 가방이 나올때 부터 경우의수 2개 중에서 확인해서 DP값 갱신
                DP[i][j] = max(DP[i - 1][j], item[i].second + DP[i - 1][j - item[i].first]);
            else  // 그런 경우가 아니라면 i-1번째 물건 담았을때 최댓값을 가져와서 넣어주면 됨
                DP[i][j] = DP[i - 1][j];
        }

    // 출력부
    cout << DP[N][K];

    return 0;
}
