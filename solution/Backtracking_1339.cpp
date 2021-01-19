/* Backtracking_1339, 단어 수학 */
/* 포인트
 (백트랙킹 + 순열) or (그리디)문제
 1. DFS를 이용한 "순열"구현시 (벡터, 방문배열)이 필요하다. 조합의 경우와는 다르게 DFS의 인자는 필요 없다. 왜냐면 "부모노드에서 사용한 값"을 자식 노드에서 모두 알기에 인자로는 다 적어주기 힘들다
    굳이 DFS 인자로 부모노드에서 선택한 값을 넣어주려고 vector를 사용할 수는 있는데, 자식노드에서 사용했는지 안했는지 확인하는 과정(if)에서 "시간 복잡도만 늘어난다.." (비추)
    순열의 결과 값이 "벡터"에 저장되고, 자식노드 호출시 사용되는 for문에서 인덱스 값이 "우리가 사용할 숫자"(순열에 사용하는 벡터 v에 넣을 "값")을 고려해서 for문 돌리면 된다
 2. 사실 문자가 나타나는 최대 누적값을 계산했으면.. 그냥 누적값 높은 순서대로 9,8,7,6,5... 곱해서 (그리디 방식) 더하면 정답 나온다. 그냥 DFS로 "순열" 만들어보고 싶어서 백트래킹으로 풀었음
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> v;  // 만들어낸 "순열" (0~9 에서 "문자 종류 갯수"만큼 순열 만들어낸 결과를 저장)
vector<char> alpha;  // 나온 문자 넣는다
int N, ans;
int visited[15];  // 부모 노드에서 해당 값을 사용중임을 자식 노드에게 알려주기 위한 전역변수... (노드는 각각 0~9 중 택해야 한다)
int val[30];  // 알파벳 마다 자신의 "자릿수 누적 값"을 저장

void DFS(int);  // "선택한 갯수"가 인자다.. 0~(문자종류 갯수) 만큼의 깊이를 이동함. "순열"구현할 거라서 똑같은 노드를 반복해서 왔다갔다하게 됨
int Cal(void);

int main()
{
    int i,j, digit;
    string s;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>N;
    for(i=0; i<N; i++) // 문자열 갯수만큼 반복해서 누적값 계산
    {
        // 문자열을 입력 받는다
        cin>>s;
        
        // 자릿수 1의자리 부터 시작
        digit=1;
        
        // 문자 마다 해당 자릿수를 누적해준다 (1의 자릿숫자 부터 왼쪽 방향으로 진행)
        for(j=(int)s.size()-1; j>=0; j--)
        {
            // 처음 나오는 문자는 alpha에 저장
            if(val[s[j]-'A']==0) alpha.push_back(s[j]);
            
            // 문자 마다 자신의 자릿수에 따른 누적값 계산 (자신의 문자에 해당되는 누적값을 계속 계산)
            val[s[j]-'A'] += digit;  // val 배열에 자신 문자의 누적값을 갱신
            digit = digit*10;  // 왼쪽으로 진행 할 수록 나오는 문자의 누적값에 10배 되는 값을 누적해준다
        }
    }
    
    // 실행부
    DFS(0);
    
    // 출력부
    cout<<ans;

    return 0;
}

void DFS(int cnt)
{
    int i;

    // 종료 조건 ("순열" 모두 선택시 계산)
    if( cnt == (int)alpha.size() ){ans = max( ans, Cal() );  return;}

    // 자식 노드 호출
    for(i=10-(int)alpha.size(); i<10; i++)  // (선택하는 가장 작은값)~(가장 큰 값)을 택하면 된다. (0 ~ 9)
    {
        // 방문할 수 없는 경우 (해당 숫자를 택할 수 없는 경우, 부모 노드에서 택해서 자식 노드에서는 택할 수 없는 경우)
        if(visited[i]==1) continue;
    
        // 방문할 수 있는 경우 (해당 숫자를 택할 수 있는 경우)
        visited[i] = 1;
        v.push_back(i);
        
        DFS(cnt+1);
        
        v.pop_back();
        visited[i] = 0;
    }
}

int Cal(void)
{
    int i, ret=0;
    
    // 선택된 "순열" (v에 저장됨)에 따른 정답 계산
    for(i=0; i<(int)alpha.size(); i++)
        ret += val[alpha[i]-'A']*v[i];  // 알파벳 마다 (자신의 누적값)*(선택된 값)을 넣는다

    // 결과 값 반환
    return ret;
}

