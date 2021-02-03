/* Backtracking_2661, 좋은수열 */
/* 포인트
 (백트랙킹) 문제
 1. "순열"을 DFS로 구현하고, 만들어낸 값이 좋은수열인지 확인하는 함수(CheckGood)를 거치는 작업이 필요하다.
  "순열"을 DFS로 구할 때 앞전에는 1.vector,방문확인용 배열을 사용해서 구현 했는데, 여기서는 2. string 에 값을 넣어주어서 구현했다
  좋은수열인지 확인 할 때 문자열 비교 연산 (0 == s.compare()) 사용하면 편하므로 string을 사용했다. vector를 사용한다면 묶음 비교할 때 원소단위로 비교해야하므로 번거롭다
  s.substr() 사용해서,  왼쪽,오른쪽 묶음의 "인덱스 시작부분"을 계산해서 찾는게 중요. (짝수인 경우, N=1인 경우)도 잘 고려해야한다
 2. 완전탐색하면 (좋은수열 확인 시간)*(노드갯수=3^N)으로 시간초과 날 꺼 같은데.. 모든 노드를 다 방문하는 경우가 없고, 정답에 도달하는 시간이 더 빠르다
  CheckGood()에서 좋은 수열을 찾는 경우가 빠르기 때문이다... 모든 노드 방문하기도 훨씬 전에 좋은 수열을 발견하기 때문임..
*/
#include <iostream>
#include <string>
using namespace std;

int N;
string s;

void DFS(int);
int CheckGood(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>N;
    
    // 실행부
    DFS(0);

    return 0;
}

void DFS(int cnt)
{
    int i;
    
    // 종료 조건 확인
    if( -1 == CheckGood() ) return;  // 좋은 수열이 아닌 경우
    if( cnt==N ){ cout<<s; exit(0); }  // N개 선택한 경우
    
    // 자식 노드 호출
    for(i=0; i<3; i++)
    {
        s.push_back('1' + i);
        
        DFS(cnt+1);
        
        s.pop_back();
    }
}

int CheckGood()
{
    int i;
    int half = s.length()/2;  // 문자열 중간 인덱스 저장
    string left,right;
    
    // 문자열 비교
    for(i=1; i<=half; i++)  // 묶음 선택 갯수(i): 1 ~ (절반)
    {
        // 왼쪽, 오른쪽 문자열 만듬 (1묶음, 2묶음, 3묶음, ... 씩 맨 오른쪽 부터 묶어가면서 확인)
        left  = s.substr(s.size()-2*i, i);    // (시작인덱스, 선택갯수)
        right = s.substr(s.size()-i,   i);
        
        // 만약 같은 패턴의 경우가 있으면 -1 반환
        if( 0 == left.compare(right) ) return -1;  
    }
    
    // 만들어낸 1,2,3,..묶음이 전부 달랐다면 1 반환
    return 1;
}
