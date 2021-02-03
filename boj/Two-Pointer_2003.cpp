/* Two-Pointer_2003, 수들의 합2 */
#include <iostream>
using namespace std;

int A[10010];
int N,M, sum,ans;

int main()
{
    int i,  low,high;

    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>> N >> M;
    for(i=1; i<=N; i++) cin>>A[i];
    low=1;  high=1;

    // 실행부
    while(1)  // 마지막 원소가 M보다 커서 high 값이 N+1인데 low가 여전히 이동해야 될 수 있음.. 따라서 while()문에 high<=N 조건 넣으면 안됌
    {
        // low, high 중 1개 이동 (이동조건 && index범위)
        if     (sum>=M && low<=N)  sum -= A[low++];  // 합이 M보다 크고 && 뺄 수 있는 index가 남은 경우 (합이 M과 같을 경우 high를 증가 시켜버리면 low쪽 경우의 수 확인 못하고 종료될 수 있다. 따라서 low를 증가시킨다)
        else if(sum <M && high<=N) sum += A[high++];  // 합이 M보다 작고 && 더할 수 있는 index가 남은 경우
        else break; // low,high 둘 다 더 이상 이동할 수 없는 경우

        // 이동한 결과 확인 (합이 M일 경우 카운트)
        if(sum==M) ans++;
    }

    // 출력부
    cout<<ans;

    return 0;
}
