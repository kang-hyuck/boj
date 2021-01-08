/* Two-Pointer_1806, 부분합 */
#include <iostream>
#include <algorithm>  // min()
using namespace std;

#define INF 987654321

int A[100010];
int N,S, sum,ans;

int main()
{
    int i, low,high;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>> N >> S;
    for(i=0; i<N; i++) cin>> A[i];
    high=0;  low=0;  ans=INF; // 큰 값 넣어줌

    // 실행부
    while(1)
    {
        // low,high 이동
        if     (sum>=S && low<N) sum -= A[low++];
        else if(sum <S && high<N) sum += A[high++];
        else break; // low,high 둘 다 이동 할 수 없다면 종료

        // 이동 결과 확인
        if(sum>=S) ans = min(ans, high-low);
    }

    // 출력부
    if(ans==INF)cout<<"0";
    else cout<< ans;

    return 0;
}
