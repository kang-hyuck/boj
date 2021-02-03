/* Two-Pointer_2470, 두 용액 */
#include <iostream>
#include <vector>
#include <algorithm>  // sort()
using namespace std;

#define INF 2000000010  // INF값이 20억 보다 커야한다
int ans_low, ans_high;
int N,  ans;
vector<int> v;

void TwoPointer(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    int i, temp;
    v.reserve(100010);

    // 입력부
    cin >> N;
    for (i = 0; i < N; i++) { cin >> temp; v.push_back(temp); }
    ans = INF;
    sort(v.begin(), v.end());  // 투 포인터 사용하려면 정렬 사용 필수

    // 실행부
    TwoPointer();

    // 출력부
    cout << v[ans_low] << " " << v[ans_high];

    return 0;
}

void TwoPointer()
{
    int low, high;
    int sum;

	// low, high 초기 index 설정
    low = 0;   high = v.size() - 1;

    while (1)
    {
        // 원소 더하기 (low, high가 지정하고 있는 원소의 "현재 위치"라서. 맨 초기 값부터 확인하려고 low,right 이동 하기 전에 먼저 확인 해준다)
        sum = v[low] + v[high];
        if (ans > abs(v[low] + v[high])) // 절댓값 씌운 값이 최소라면 갱신
        {
            ans = abs(v[low] + v[high]);
            ans_low = low;   ans_high = high;  // 정답 low,hig값 넣어준다
        }

        // low, high 이동 (low는 hig 왼쪽까지만 이동 가능, high는 low 오른쪽 까지만 이동 가능)
        if      (sum <= 0 && v[low]  < 0 && low  < high-1) low++;  // 두 원소 덧셈 결과가 음수면 low를 움직인다
        else if (sum >  0 && v[high] > 0 && high > low+1 ) high--; // 두 원소 덧셈 결과가 양수이면 high를 움직인다
        else break;
    }
}
