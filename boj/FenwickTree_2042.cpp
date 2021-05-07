/* FenwickTree_2042, 구간 합 구하기 */
/* 포인트
 1. 펜윅트리는 "구간 합" 구할 때 사용. 메모리도 "배열크기"와 같게끔 구현한다 (세그먼트때는 4배 잡았음)
    단점은 구현은 쉽지만 구간합이 아닌 경우.. 응용적인면에서 세그먼트리에 비해 부족하다.. (예로 구간곱..)
 2. (index & -index)하면... index를 비트로 나타냈을때.. 가장 오른쪽에 먼저나오는 1값만 나온다
 3. 펜윅트리 업데이트: 가장오른쪽 1비트를 1개씩 더했을때 계산되는 트리의 "인덱스 위치"들에서의 "값"에... diff만큼 더해주면 된다.
    펜윅트리 쿼리:     가장오른쪽 1비트를 1개씩 빼주었을때 계싼되는 트리의 "인덱스 위치"들에서의 "값"을... 모두 누적하면 된다.
 4. 펜윅트리 쿼리는... "배열"의 1번인덱스부터 쿼리에 넣은 배열 "인덱스값"까지 누적값이 나오게 된다 (배열의 1~N번째 누적값) = Query(N); 
*/
#include <iostream>
using namespace std;
typedef long long ll;

int N,M,K;
ll score[1000010];
ll tree[1000010];   // 펜윅트리값 저장. 크기는 행렬갯수와 같음.

void Update(int, ll);
ll Query(int);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int a;  ll b,c;
    
    // 입력부
    cin>>N>>M>>K;
    for(int i=1; i<=N; i++){cin>>score[i];   Update(i, score[i]);}   // 펜윅트리 초기화
    
    // 실행부
    for(int i=0; i<M+K; i++){
        cin>>a>>b>>c;
        if(a==1){Update(b, c-score[b]);  score[b]=c;}  // 펜윅트리값 갱신 (기존값과 차이값 넣어줌)
        if(a==2) cout<<(Query(c)-Query(b-1))<<"\n";    // 쿼리값 출력, (c~b 합) (c~1 합) - (b-1~1 합)
    }

    return 0;
}

void Update(int index, ll diff){
    for(; index<=N; index+=(index&-index)) tree[index]+=diff;   // tree에 차이값(diff) 갱신, (index&-index)는 오른쪽에서 가장 먼저나오는 1의 위치
}
ll Query(int index){
    ll sum=0;
    for(; index>0; index-=(index&-index)) sum+=tree[index];   // tree값 누적
    return sum;
}

