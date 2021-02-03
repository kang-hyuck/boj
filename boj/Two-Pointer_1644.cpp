/* Two-Pointer_1644, 소수의 연속합 */
#include <iostream>
#include <math.h>  // sqrt()
#include <vector>
using namespace std;

int N, sum, ans;
int prime[4000010];
vector<int> v;  // 소수 담는다

void MakePrime(void);  // 소수 만드는 함수
void TwoPointer(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N;

    // 실행부
    MakePrime();
    TwoPointer();

    // 출력부
    cout << ans;

    return 0;
}

void MakePrime()
{
    int i, j;

    // 초기화 (모두 소수라고 가정)
    prime[1] = 0;  // 1은 소수가 아니라고 가정
    for (i = 2; i <= N; i++)  prime[i] = 1;  // 2이상은 모두 소수라고 가정

    // 소수 찾기 (배수인 애들 모두 지운다. 이러면 소수인 애들만 1값 남는다)
    for (i = 2; i <= sqrt(N); i++)  // 2 ~ sqrt(N) 까지만 확인.
    {
        // 소수가 아니라면 넘김
        if (prime[i] == 0) continue;

        // 소수라면 배수들을 모두 지움 (자기자신 부터 지우면 안됀다..)
        for (j = 2*i; j <= N; j += i) prime[j] = 0;
    }

    // 소수인 애들 vector에 담기
    for (i = 1; i <= N; i++)
        if (prime[i] == 1) v.push_back(i);
}

void TwoPointer()
{
    int low, high;
    int size;

    low = 0;  high = 0;
    size = (int)v.size();  // 소수 들어있는 vector 크기

    while(1)
    {
        // low, high 이동
        if      (sum >= N && low  < size) sum -= v[low++];    // 왼쪽 이동
        else if (sum <  N && high < size) sum += v[high++];   // 오른쪽 이동
        else  break;  // low, high 둘 다 이동할 수 없다면

        // 이동 결과 확인 (더한값이 숫자와 같으면 정답수 카운트)
        if (sum == N)  ans++;
    }
}
