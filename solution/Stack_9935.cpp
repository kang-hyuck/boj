/* Stack_9935, 문자열 폭발 */
/* 포인트
 1. 함수단위로 먼저 코드를 구성한다. 함수단위로 틀을 만들어 놓고 함수 내부를 구현하는 식으로 코드를 구성하면 쉽게 구현할 수 있다
*/
#include <iostream>
#include <stack>
#include <string>
using namespace std;

stack<char> s, res;
string str, bomb;
char last;  // 폭발 문자열의 "오른쪽 맨 끝 문자"

void Start(void);
void Bomb(void);
void Print(void);
int CanBomb(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin>>str;   // 조사할 문자열
    cin>>bomb;  // 폭발 문자열

    // 실행부
    Start();  

    // 출력부
    Print();

    return 0;
}

void Start()
{
    int i;
    last = bomb[bomb.size()-1]; // 폭발 문자열의 "오른쪽 맨 끝 문자" 값을 담는다

    // 문자열 길이 만큼 조사
    for(i=0; i<(int)str.size(); i++)
    {
        // 스택에 문자를 넣는다
        s.push(str[i]);

        // 폭발 할 수 없는 경우
        if( -1 == CanBomb() ) continue;

        // 폭발 할 수 있는 경우
        Bomb();
    }
}

int CanBomb()
{
    int i;
    stack<char> popped;  // 조사할 때 스택에서 꺼낸 문자들을 저장, 스택 복구할 때 사용

    // 폭발 불가능한 경우
    if (s.top()!=last) return -1;   // 스택에 마지막으로 들어간 문자 값이 폭발 문자열 마지막 문자 값과 다른 경우
    if (s.size()<bomb.size()) return -1;  // 스택에 들어있는 크기가 폭발 문자열 길이보다 작은 경우

    // 폭발 가능성 조사
    for(i=(int)bomb.size()-1; i>=0; i--)  // 폭발 문자열 맨 뒤에서 부터 문자 하나씩 비교해본다
    {
        if(s.top()!=bomb[i]) break;  // 중간에 문자 다른 경우가 나오는 경우
        popped.push(s.top());
        s.pop();
    }
    // 조사하면서 꺼냈던 문자들을 다시 스택에 넣어준다
    while(!popped.empty())
    {
        s.push(popped.top());
        popped.pop();
    }

    // 폭발 가능하다면
    if(i==-1) return 1;  // for문을 다 돌았다면 i값이 -1이다. for문이 break으로 종료 됬다면 i값이 -1이 아니다

    // 폭발 불가하다면
    return -1;
}

void Bomb()
{
    int i;

    // 폭발 문자열 크기 만큼 스택에서 꺼내준다
    for(i=0; i<(int)bomb.size(); i++)
        s.pop();
}

void Print()
{
    // 출력할 문자가 없다면,(모든 문자가 폭발해서) FRULA 출력
    if(s.size()==0){cout<<"FRULA"; return;}

    // 출력할 문자가 있다면, 스택 res 사용해서 뒤집어서 출력해준다
    while(!s.empty())
    {
        res.push(s.top());
        s.pop();
    }
    while(!res.empty())
    {
        cout<<res.top();
        res.pop();
    }
}
