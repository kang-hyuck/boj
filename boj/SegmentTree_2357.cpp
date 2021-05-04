/* SegmentTree_2357, 최솟값과 최댓값 */
/* 포인트
  1. 세그먼트트리가 "포함하는 index 범위" 내에서. {가장작은값, 가장큰값}을 세그먼트트리가 갖고 있으면 된다.
     세그먼트트리는 항상.... 세그먼트트리 [노드가 갖고 있는 index 범위] - [구하려는 값] 이 대응되도록... 만들면 된다
  2. Init에서는 tree값을 초기화 해야하므로 반환부에서 tree[num] = ... 식으로 담아 주었다. 반면에
     Query에서는 값이채워진 tree값을 이용해서 "데이터를 출력만" 하면 되므로. 반환부에서 tree[num] = ... 이 아니라.. "연산식"만 적어주면 된다
  3. endl -> "\n" 로 바꾸어 주어서 "시간초과" 해결했다........ (endl 사용해서 시간초과 나는것 때문에 6번 틀림ㅠ)
  4. Init이 굳이 반환형일 필요가 없다.. 노드끝까지 탐색했다가 돌아오므로.. Update때처럼 후위호출부(종료될때)에서 tree값 갱신해도 된다..
     Init의 반환형이.. 구조체면 안된다는 것을 알 수 있다... 반면에 값 1개만 반환하는 것은 괜찮은듯.
*/
#include <iostream>
#include <algorithm>  // min(), max()
#define INF   2000000000     //  20억
using namespace std;

typedef struct Node{
    int minVal, maxVal;
}Node;

// 전역변수선언
int val[100010];   // 값
int treeMin[400010];  // 세그먼트트리값
int treeMax[400010];
int N,M;

// 함수선언
void Init(int, int,int);
Node Query(int, int,int,int,int);

int main()
{   
    ios::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int a,b;  Node tmp;

    // 입력부
    cin>>N>>M;
    for(int i=0; i<N; i++) cin>>val[i];

    // 실행부
    Init(1, 0,N-1);   // 세그먼트트리 초기화 (시작노드번호,  시작인덱스,끝인덱스)

    // 출력부
    for(int i=0; i<M; i++){cin>>a>>b;  tmp=Query(1, 0,N-1, a-1,b-1);  cout<<tmp.minVal<<" "<<tmp.maxVal<<"\n";}

    return 0;   
}

void Init(int num, int index_s, int index_e)
{
    // 종료부
    if(index_s==index_e){treeMin[num]=val[index_s];  treeMax[num]=val[index_s];  return;}

    // 자식노드 호출
    int mid = (index_s + index_e)/2;
    Init(num*2,    index_s,  mid    );  // 짝수번호 탐색
    Init(num*2+1,  mid+1,    index_e);  // 홀수번호 탐색

    // 반환부
    treeMin[num]=min(treeMin[num*2], treeMin[num*2+1]);   // 왼쪽,오른쪽 중 "최솟값" 저장
    treeMax[num]=max(treeMax[num*2], treeMax[num*2+1]);   // 왼쪽,오른쪽 중 "최댓값" 저장
}

Node Query(int num, int index_s, int index_e, int index_ts, int index_te)
{
    // 종료부
    if(index_s >  index_te || index_e <  index_ts) return {INF, 0};                        // "현재노드의 보유 인덱스범위"가 포함되지 않는 경우
    if(index_s >= index_ts && index_e <= index_te) return {treeMin[num], treeMax[num]};    // "현재노드의 보유 인덱스범위"가 완전히 포함 되는 경우

    // 자식노드 호출
    int mid = (index_s + index_e)/2;
    Node left  = Query(num*2,    index_s,  mid,      index_ts, index_te);  // 짝수번호 탐색
    Node right = Query(num*2+1,  mid+1,    index_e,  index_ts, index_te);  // 홀수번호 탐색

    // 반환부
    return {min(left.minVal, right.minVal),  max(left.maxVal, right.maxVal)};   // 왼쪽,오른쪽 중 {최소,최대} 출력
}
