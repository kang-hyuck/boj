/* SegmentTree_1725, 히스토그램 */
/* 포인트
 (세그먼트트리) + (이분탐색) 문제
 1. 이분탐색 사용시 "구분할 기준"으로 인덱스를 사용하기 위해서 "세그먼트트리"에서 "가장낮은 높이의 인덱스"를 저장한다.
 2. 이분탐색 사용시 left 부분 인덱스에서.. (index_s, mid-1)이 들어가야한다. mid-1 대신 mid 넣으면 안됨.. 그렇게되면 가장낮은 높이로 mid가 계속 지정된다
    현재인덱스범위에서 "가장낮은인덱스"를 제외하고 나머지 인덱스부분을 (왼쪽,오른쪽)으로 나누어서 탐색해야하므로.
 3. 쿼리탐색시.. 찾고자하는 인덱스가 양쪽 어딘가 1곳에는 존재할테니.. left,right 중 적어도 1개는 정상 인덱스를 반환한다
 4. 결국에는 이분탐색시 분할기준인덱스 선택할때 쿼리사용하려고 세그먼트트리를 만든거다..
 5. 이분탐색을 "DFS"로 구현한거다 (while로 구현하는 것 보다... DFS로 구현하는 것이 응용적인 측면에서 유리)
*/

#include <iostream>
#include <algorithm>  // min(),max()
using namespace std;

typedef long long ll;

// 전역변수선언
int N;
ll height[100010];  // 넓이가 long long 타입이여야 하므로 높이도 long long으로 지정해줌. 넓이최대크기가 (10억 * 100,000) 이므로.
ll tree[400040];    // 세그먼트트리 크기. 적당히 높이길이 4배 지정해주었음

// 함수선언
ll Init(int, int,int);
ll Query(int, int,int, int,int);
ll Area(int,int);   // 분할정복

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>N;   // 사각형갯수 저장
    for(int i=0; i<N; i++) cin>>height[i];   // 높이값 저장

    // 실행부
    Init(1, 0,N-1);  // 세그먼트트리 초기화

    // 출력부
    cout<<Area(0,N-1)<<"\n";
}

ll Init(int num, int index_s, int index_e)
{
    // 종료부
    if(index_s == index_e) return tree[num] = index_s;   // 리프노드 초기화 ([트리번호] = 인덱스 저장)

    // 자식노드 호출
    int mid   =  (index_s + index_e)/2;
    ll  left  =  Init(num*2,    index_s, mid    );  // 짝수번호 탐색
    ll  right =  Init(num*2+1,  mid+1,   index_e);  // 홀수번호 탐색

    // 반환부
    return tree[num] = (height[left] <= height[right]) ? left : right;   // 왼쪽,오른쪽 중 낮은높이의 "인덱스" 저장
}

ll Query(int num, int index_s, int index_e, int index_ts, int index_te)
{
    // 종료부
    if(index_s >  index_te || index_e <  index_ts) return -1;         // "현재노드의 인덱스범위"가 "탐색인덱스"를 포함하지 않는 경우
    if(index_s >= index_ts && index_e <= index_te) return tree[num];  // "현재노드의 인덱스범위"가 "탐색인덱스"를 완전히 포함하는 경우

    // 자식노드 호출
    int mid   =  (index_s + index_e)/2;
    ll  left  =  Query(num*2,    index_s, mid,     index_ts, index_te);  // 짝수번호 탐색
    ll  right =  Query(num*2+1,  mid+1,   index_e, index_ts, index_te);  // 홀수번호 탐색

    // 반환부
    if(left==-1)  return right;
    if(right==-1) return left;   // 둘 중 1개는 무조건 "정상인덱스"를 갖는다. 탐색인덱스 범위가 둘 중 1개에는 반드이 있을테니.
    return (height[left] <= height[right]) ? left : right;   // 작은높이를 갖는 "인덱스" 반환
}

ll Area(int index_s, int index_e)
{
    // 종료부
    if(index_s >  index_e) return 0;    // 인덱스범위를 벗어나는 경우
    if(index_s == index_e) return 1*height[index_s];   // 리프노드 도착한경우 (너비*높이 반환)

    // 자식노드 호출
    int mid   =  Query(1, 0,N-1, index_s, index_e);    // "분할정복 기준" 계산. 현재 인덱스범위에서 "가장낮은 높이의 인덱스" 값 반환
    ll  left  =  Area(index_s,  mid-1  );  // 가장낮은높이 기준 "왼쪽" 탐색   (mid-1이 들어가야한다. mid넣으면 왼쪽에서 가장낮은높이로 mid가 계속 선택된다..)
    ll  right =  Area(mid+1,    index_e);  // 가장낮은높이 기준 "오른쪽" 탐색

    // 실행부
    ll area = (index_e-index_s+1)*height[mid];     // 현재노드의 "최소넓이"계산 (너비*높이)

    // 반환부
    return max({area,  left,  right});   // 3개의 값 중 "최댓값" 출력 (현재범위, 왼쪽범위, 오른쪽범위)에서의 "최소넓이" 중 "최대넓이" 택한것임
}
