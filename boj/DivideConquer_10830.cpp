/* DivideConquer_10830, 행렬 제곱 */
/* 포인트 (곱셈문제와 같음)
 1. "분할정복하고 싶은 대상"을 DFS의 "인자"로 넣어준다. "지수"부분을 분할정복할 것이므로. DFS인자에 "지수"를 넣어주었다.
 2. 자식노드호출 시, power/2를 넣었는데, power값이 (짝수/홀수)냐에 따라서, 홀수부분은 A를 1번 더 곱해주어야하는 차이가 생긴다.
    DFS에서 값을 반환할때, power가 홀수인 경우는 부족한 A 1번을 더 곱해주는 식으로 처리했다.
 3. "함수호출시" 인자의 타입이 long long이라도... "함수정의"된 곳에서 받는 인자타입이 int면 int로 바뀌어버린다... 이거때문에 고생할 수 있음..
*/
#include <iostream>
#include <vector>
using namespace std;
#define MOD  1000
typedef long long ll;
typedef vector<vector<ll>> matrix_t;

int N;
matrix_t A;
ll B;

matrix_t DFS(ll);
matrix_t Product(matrix_t, matrix_t);   // 행렬곱계산, 행렬=(행렬,행렬)

int main()
{
    // 입력부
    cin>>N>>B;
    for(int i=0; i<N; i++){  // 행방향 담기
        vector<ll> temp;
        for(int j=0; j<N; j++){   // 열방향 담기
            ll val;   cin>>val;
            temp.push_back(val);
        }
        A.push_back(temp);
    }

    // 실행부
    matrix_t ans = DFS(B);

    // 출력부
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cout<<ans[i][j]%MOD<<" ";
        cout<<endl;
    }

    return 0;
}

matrix_t DFS(ll power)
{
    // 종료부
    if(power==1) return A;

    // 자식노드 호출
    matrix_t matrixChild = DFS(power/2);   // A^(지수/2) 결과값 호출

    // 실행부
    matrix_t ret = Product(matrixChild,matrixChild);    // A^(지수) = A^(지수/2) * A^(지수/2)

    // 반환부
    if(power%2==1) return Product(ret, A);     // 홀수인 경우. (지수/2)에서 A곱이 1번 빠지므로, A를 1번 더 곱해준다.
    return ret;  // 짝수인 경우. A^(지수)값 반환
}

matrix_t Product(matrix_t matrixA, matrix_t matrixB)
{
    matrix_t ret;

    // 실행부 (행렬 A,B 곱)
    for(int i=0; i<(int)matrixA.size(); i++)  // 행렬A의 1행 마다
    {
        vector<ll> row;
        for(int j=0; j<(int)matrixB.size(); j++)   // 행렬B의 1열 마다
        {
            ll sum=0;
            for(int k=0; k<(int)matrixA.size(); k++)  sum=(sum+(matrixA[i][k]*matrixB[k][j]%MOD))%MOD;   // 원소값 계산
            row.push_back(sum);
        }
        ret.push_back(row);  // 계산된 행값 담음
    }

    // 반환부
    return ret;
}
