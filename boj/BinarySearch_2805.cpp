/* BinarySearch_2805, 나무 자르기 */
/* 포인트
 1. 그림을 그려야한다. 그리고 시뮬레이션함수값이 "true"일때, left,right 중 무엇을 옮길 것인지 생각해야한다.
    그 이유는 마지막에 정답위치에서 left==right가 되는데, 이때 시뮬레이션함수의 반환값에 따라서 left,right 중 우리가 이동하도록
    설정한 기리킴이 이동하게 된다. 종료조건 left>right에서 ans에 담을때. left==right 이후에 "이동하도록 지정한 가리킴의 이전값"을
    ans에 담아주어야 한다.
 2. 그림 예시)   left----------mid----★---right
                  |                   |          
                  ---함수반환값 true----
    이런식으로 구성이 된다면. 우리가 찾고싶은 "정답지점"은. 함수반환값이 (true->false)가 되기 시작하는 ★ 지점이다.
    mid값이 시뮬레이션함수 인자로 사용되고, "해당범위" 안에 mid값이 위치한경우 모두 left가 이동(mid+1위치로)하게 된다.
    함수반환값이 ture인 경우는 문제에따라서. 또는 어떻게 구성하느냐에따라서 범위에 right를 포함해서 시작하냐. 바뀔 수 있을 듯.
*/
#include <iostream>
using namespace std;
typedef long long ll;

// 전역변수
ll N,M, ans;
ll tree[1000010];

// 함수선언
void BinarySearch();
bool CanTakeTree(ll);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>N>>M;
    for(int i=0; i<N; i++) cin>>tree[i];

    // 실행부
    BinarySearch();

    // 종료부
    cout<<ans;

    return 0;
}

void BinarySearch()
{
    ll left=1,  right=1000000000,   mid;   // 변수초기화
    bool res;  // 시뮬레이션결과 저장

    // 실행부
    while(1)
    {
        // 인덱스 이동  (left, right 중 1개)
        mid = (left+right)/2;    // 중간인덱스 계산 (자를높이, 시뮬레이션에서 사용)
        res = CanTakeTree(mid);  // 시뮬레이션 실행
        if( res) left  = mid+1;
        if(!res) right = mid-1;

        // 종료조건
        if(left>right){ans=left-1; return;}   // 정답에서. left==right일때. 시뮬레이션돌리면 left가 1번 더 이동하므로. left-1이 답이다.
    }
}

bool CanTakeTree(ll cutVal)
{
    ll sum=0;

    // 실행부
    for(int i=0; i<N; i++) if(tree[i]>cutVal) sum+=(tree[i]-cutVal);

    // 반환부
    if(sum>=M) return true;  // 원하는만큼 나무를 취할 수 있는 경우  (left 이동 )
    return false;            // 원하는만큼 나무를 취할 수 없는 경우  (right 이동)
}
