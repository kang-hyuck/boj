/* Stack_2812, 크게 만들기 */
/* 포인트
 1. stack대신 deque사용하자. 나중에 출력할 때 stack에 있는 원소 순서를 bottom부터 출력하고 싶을 때 다른 stack에 옮겨 담아서 출력해야하는데 번거롭다
    deque사용하면 index로 원소에 접근이 가능하니까... 맨 bottom에 있는 원소부터 출력할 수 있다
 2. "목표하는 원소 값까지" 스택에서 값을 꺼내야할 때. while( 안비어있다면 && 조건1 && 조건2 ...) 이런 식으로 구현하자 !! 이렇게 짜는게 깔끔한듯.
    while()문 안에서부터는 BFS처럼 맨 처음에 pop()해주는 작업 적어주도록 하자. while()문 밖에서 부터. (i) 왜 멈췄는지(스택이 비어서 or 목표하는 조건에 도달해서)
    (ii) 멈춘 이유에 따른 처리(행동). 을 적어주도록 하자.
*/
#include <iostream>
#include <string>
#include <deque>
using namespace std;

string s;
deque<char> dq;  // 스택 대신에 덱 사용. "출력"할 때 덱이 더 용이하다... 덱은 인덱스 접근이 가능하니까.

int N,K;

int main()
{
    int i, cnt;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    
    // 입력부
    cin>>N>>K;
    cin>>s;
    cnt = K;  // 제거 해야하는 숫자 넣어준다
    
    // 실행부
    for(i=0; i<N; i++)
    {
        // 스택에서 값을 꺼낸다 (항상..."스택 비어있지 않거나" && "꺼내는 조건1" 형식으로 적어주자)
        while(!dq.empty() && dq.back() < s[i] && cnt>0)  // 스택 탑과 문자열 크기 비교
        {
            // 값 꺼내줌
            dq.pop_back();
            cnt--;  // 꺼내야하는 횟수 감소
        }
        // 꺼내는 작업 종료 후. 스택에 값을 넣어준다
        dq.push_back(s[i]);
    }
    
    // 출력부
    for(i=0; i<N-K; i++)
        cout<<dq[i];

    return 0;
}

