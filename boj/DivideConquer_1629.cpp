/* DivideConquer_1629, 곱셈 */
/* 포인트
 1. "분할정복하고 싶은 대상"을 DFS의 "인자"로 넣어준다. "지수"부분을 분할정복할 것이므로. DFS인자에 "지수"를 넣어주었다.
 2. 자식노드호출 시, power/2를 넣었는데, power값이 (짝수/홀수)냐에 따라서, 홀수부분은 A를 1번 더 곱해주어야하는 차이가 생긴다.
    DFS에서 값을 반환할때, power가 홀수인 경우는 부족한 A 1번을 더 곱해주는 식으로 처리했다.
*/
#include <iostream>
using namespace std;
typedef long long ll;

// 전역변수
int A,B,C;

// 함수선언
ll DFS(int);

int main()
{
    // 입력부
    cin>>A>>B>>C;

    // 실행부
    cout<<DFS(B);

    return 0;
}

ll DFS(int power)
{
    // 종료조건
    if(power==1) return A%C;   // A^1인 경우

    // 자식노드 호출
    ll val = DFS(power/2);   // A^(power/2)값 계산

    // 반환부, A^(power)값 반환
    if(power%2==0) return (val*val)%C;   // 지수(power)가 짝수인경우,   A^(power/2)값 2번 곱함
    return (((val*val)%C)*A)%C;          // 지수(power)가 홀수인경우,   power/2하면 1개 부족하므로. 추가로 A 곱함
}
