/* SegmentTree_11505, 구간 곱 구하기 */
/* 포인트
 Update함수가 포인트다. "리프노드"부터 값을 업데이트하고나서, 후위호출부분(함수 맨끝부분)에서 (왼쪽,오른쪽) 노드값을 곱해주는 식으로.
 부모노드값들을 갱신해주었다. 자식노드 -> 부모노드 순으로 값을 업데이트 한거다.
*/

#include <iostream>
#define MOD 1000000007
using namespace std;
typedef long long ll;

// 전역변수
int N,M,K;
ll score[1000010];  // 점수값
ll tree[4000010];   // 세그먼트트리값

// 함수선언
ll Init(int, int,int);
ll Query(int, int,int, int,int);
void Update(int, int,int, int, ll);

int main()
{
    ll a,b,c;
    
    // 입력부
    cin>>N>>M>>K;
    for(int i=0; i<N; i++) cin>>score[i];  // 점수값 입력
    
    // 실행부
    Init(1, 0,N-1);  // 세그먼트트리 초기화
    for(int i=0; i<M+K; i++)
    {
        cin>>a>>b>>c;
        
        // 트리값갱신(a==1) || 트리값출력(a==2)
        if(a==1) Update(1, 0,N-1, b-1,c);
        if(a==2) cout<<Query(1, 0,N-1, b-1,c-1)<<endl;
    }
    
    return 0;   
}

ll Init(int num, int index_s, int index_e)
{
    // 종료부
    if(index_s==index_e) return tree[num]=score[index_s];  // 노드 끝에 도달한 경우 (시작인덱스==끝인덱스)
    
    // 자식노드 호출
    int mid  =  (index_s + index_e)/2;
    ll left  =  Init(num*2,    index_s,  mid    );   // 짝수노드 탐색
    ll right =  Init(num*2+1,  mid + 1,  index_e);   // 홀수노드 탐색
    
    // 반환부
    return tree[num] = (left*right) % MOD;
}

ll Query(int num, int index_s, int index_e, int index_ts, int index_te)
{
    // 종료부
    if(index_s >  index_te || index_e <  index_ts) return 1;          // "현재노드가 갖고있는 인덱스범위"가 "탐색 인덱스 범위"와 포함관계가 없는 경우
    if(index_s >= index_ts && index_e <= index_te) return tree[num];  // "현재노드가 갖고있는 인덱스범위"가 "탐색 인덱스 범위"에 완전히 포함되는 경우
    
    // 자식노드 호출
    int mid  =  (index_s + index_e)/2;
    ll left  =  Query(num*2,    index_s,  mid,      index_ts, index_te);   // 짝수노드 탐색
    ll right =  Query(num*2+1,  mid + 1,  index_e,  index_ts, index_te);   // 홀수노드 탐색
    
    // 반환부
    return (left*right) % MOD;
}

void Update(int num, int index_s, int index_e, int index, ll val)
{
    // 종료부
    if(index < index_s || index_e < index) return;         // "현재노드가 갖고있는 인덱스범위"가 "탐색 인덱스 범위"와 포함관계가 없는 경우
    if(index_s == index_e){tree[num] = val;  return;}  // 노드 끝에 도달한 경우 (값을 갱신하고자 하는 노드에 도달한 경우)
    
    // 자식노드 호출
    int mid  =  (index_s + index_e)/2;
    Update(num*2,    index_s,  mid,      index, val);
    Update(num*2+1,  mid + 1,  index_e,  index, val);
    
    // 실행부
    tree[num] = (tree[num*2]*tree[num*2+1]) % MOD;   // 세그먼트트리값 갱신
}
