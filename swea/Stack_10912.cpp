/* Stack_10912, 외로운 문자 */
/* 포인트
 (스택) 문제
 스택이 비어 있는 경우, 비어 있지 않는 경우를 나누어서 구현 한다
 */
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

int T,t;
string s;
deque<char> dq;

void Start(void);
void Print(void);

int main()
{
    // 입력부
    cin>>T;
 
    // 실행부
    for(t=1; t<=T; t++)
    {
        // 시뮬레이션 실행
        Start();
        
        // 출력부
        Print();
        
        // 초기화
        dq.clear();
    }
    
    return 0;
}

void Start()
{
    int i;

    // 문자 입력 받음
    cin>>s;
    sort(s.begin(), s.end());  // 알파벳 순으로 정렬 한다

    for(i=0; i<(int)s.size(); i++)
    {
        // 스택이 비어 있지 않은 경우
        if( !dq.empty() && dq.back() == s[i] ){dq.pop_back();  continue;}  // 비어 있지 않은데, 스택 탑과 문자값이 같다면 꺼내고 현재 문자도 안넣음
        
        // 스택이 비어 있는 경우
        dq.push_back(s[i]);  // 현재 문자를 넣는다
    }
}

void Print()
{
    int i;
    
    // 스택이 비어 있는 경우
    if( dq.empty() ){cout<<"#"<<t<<" Good\n"; return;}

    // 스택이 비어 있지 않는 경우 (스택 값 맨 앞 문자부터 출력)
    cout<<"#"<<t<<" ";
    for(i=0; i<(int)dq.size(); i++)
        cout<<dq[i];
    cout<<"\n";
    return;
}

