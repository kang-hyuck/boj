/* SegmentTree_2042, 구간 합 구하기 */
/* 포인트
 1. left, right 탐색할 때, 자료형 long long 이여야 한다.
 2. Update함수에서 diff 값이 long long이 되어야 한다.. 세그먼트트리 값이 long long 이고, 갱신 될때 diff값이랑 연산이 되므로. (이것 때문에 디버깅함 ㅠ)
 3. Init, Sum 함수는 구조가 비슷. Update함수는 void형이다.
 4. 트리크기... 배열보다 크게 잡아야한다 ㅠ.ㅠ depth를 ceil(log2(배열크기)) 만큼 잡고.. 트리크기를 2*depth + 1 잡아야하는데.. 그냥 4배 키웠음
 5. Update함수에서. 실행부를 (전위호출/후위호출) 둘 다 가능하다. (노드를 방문하자마자 / 노드 종료하자마자) 값을 갱신할 것인지 차이이다.
    전위호출시:  tree[num] = tree[num] + diff;                // 트리에 방문하자마자.  부모노드값 갱신후 -> 자식노드값 갱신
    후위호출시:  tree[num] = tree[num*2] + tree[num*2+1];     // 트리가 종료되자마자.  자식노드값 갱신후 -> 부모노드값 갱신
    후위호출에서 갱신하는게... 다른 문제 풀 때도 응용할 때 더 좋은듯...??
*/
#include <iostream>
using namespace std;
typedef long long ll;

// 전역변수선언
int N,M,K;
ll score[1000010];  // 배열값
ll tree[4000040];   // 세그먼트트리값 (배열보다 크게 잡아야함)

// 함수선언
ll InitSegmentTree(int, int,int);              // (노드번호, 시작인덱스,끝인덱스)
ll SumSegmentTree(int, int,int, int,int);      // (노드번호, 시작인덱스,끝인덱스, 탐색시작인덱스,탐색끝인덱스)
void UpdateSegmentTree(int, int,int, int, ll); // (노드번호, 시작인덱스,끝인덱스, 변경될인덱스, 차이값)

int main()
{
    ll a,b,c, diff;  // 변경값, 차이값 모두 long long 이여야 함 ㅠ.ㅠ 실수하기 좋음

    // 입력부
    cin>>N>>M>>K;
    for(int i=1; i<= N; i++) cin>>score[i];  // 숫자 입력 받기
    
    // 실행부
    InitSegmentTree(1, 1, N);  // 트리값 초기화 (1번노드부터 방문. 점수값(1~N) 활용)
    for(int i=1; i<= M+K; i++)
    {
        cin>>a>>b>>c;
        
        // 값변경(a==1) || 값출력(a==2)
        if(a==1){ diff=c-score[b];  score[b]=c;  UpdateSegmentTree(1, 1,N, b,diff); }   // 트리값 갱신
        if(a==2) cout<<SumSegmentTree(1, 1,N, b,c)<<endl;                               // 트리값 출력
    }
    
    return 0;
}

ll InitSegmentTree(int num, int index_s, int index_e)
{
    // 종료부
    if(index_s==index_e)  return tree[num]=score[index_s];   // 노드 1곳에 도착한 경우. 해당 위치 점수값 담음 (시작인덱스==끝인덱스)
    
    // 자식노드 호출
    int mid   = (index_s + index_e)/2;
    ll left  = InitSegmentTree(num*2,      index_s, mid    );   // 짝수노드 탐색
    ll right = InitSegmentTree(num*2 + 1,  mid + 1, index_e);   // 홀수노드 탐색
    
    // 반환부
    return tree[num] = left + right;
}

ll SumSegmentTree(int num, int index_s, int index_e,  int index_ts, int index_te)
{
    // 종료부
    if(index_ts >  index_e || index_te <  index_s ) return 0;          //  "탐색할 범위"가 "타겟 범위"와 포함관계가 없는 경우
    if(index_ts <= index_s && index_e  <= index_te) return tree[num];  //  "탐색할 범위"가 "타겟 범위"에 "완전히" 포함되는 경우

    // 자식노드 호출
    int mid   = (index_s + index_e)/2;
    ll left  = SumSegmentTree(num*2,      index_s, mid    , index_ts, index_te);   // 짝수노드 탐색
    ll right = SumSegmentTree(num*2 + 1,  mid + 1, index_e, index_ts, index_te);   // 홀수노드 탐색
    
    // 반환부
    return left + right;
}

void UpdateSegmentTree(int num, int index_s, int index_e,  int index, ll diff)
{
    // 종료부
    if(index < index_s  ||  index_e < index)  return;             // "탐색할 범위"에 "타겟 인덱스"가 포함되지 않는 경우
    if(index_s == index_e) {tree[num] = tree[num]+diff; return;}  // 노드 끝에 도착한 경우
    
    // 실행부 (전위호출)
//    tree[num] = tree[num] + diff;   // 트리값 갱신
    
    // 자식노드 호출
    int mid   = (index_s + index_e)/2;
    UpdateSegmentTree(num*2,      index_s, mid    , index, diff);   // 짝수노드 탐색
    UpdateSegmentTree(num*2 + 1,  mid + 1, index_e, index, diff);   // 홀수노드 탐색
    
    // 실행부 (후위호출)
    tree[num] = tree[num*2] + tree[num*2+1];   // 트리값 갱신
}

