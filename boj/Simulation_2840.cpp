/* Simulation_2840, 행운의 바퀴 */
/* 포인트
 덱 사용한 기본 시뮬레이션. 0번 인덱스를 화살표 가리키는 곳으로 정해놓고 풀었다
*/
#include <iostream>
#include <deque>
using namespace std;

int N,K;
int check[30];  // 같은 알파벳 존재시 "!" 출력
deque<char> dq;

void Rotate(int, char);
void Print(void);

int main()
{
    int i, num;
    char c;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    cin>>N>>K;
    for(i=0; i<N; i++)
        dq.push_back('?');

    // 실행부
    while(K--)
    {
        cin>>num>>c;    // 회전 횟수, 가리킨 글자 받는다
        Rotate(num,c);  // 회전 시킨다
    }

    // 출력부
    Print();

    return 0;   
}

void Rotate(int num, char c)
{
    char temp;

    // 회전
    while(num--)  // 회전 횟수만큼 실행
    {
        // 앞에서 꺼낸다
        temp = dq.front();
        dq.pop_front();

        // 뒤로 넣는다
        dq.push_back(temp);
    }

    // 화살표가 가리키고 있는 곳에 글자를 넣는다  (0번 인덱스를 가리키고 있다고 가정 했음)
    if(dq[0]=='?' && check[c-'A']==0){ dq[0] = c; check[c-'A']=1;}  // 비어 있다면 알파벳 쓰고, 사용 했음을 나타낸다
    else if (dq[0]!=c && check[c-'A']==1){cout<<"!"; exit(0);}  // 알파벳을 이미 썼는데, 같은 문자가 나타나는 칸에 쓰는게 아닌 경우
    else if (dq[0]!='?' && dq[0]!=c){cout<<"!"; exit(0);}  // 이미 다른 글자가 들어 있는데, 다른 문자를 쓰려고 하는 경우
}

void Print()
{
    int i;
    char temp;

    // 화살표 가리키는 숫자를 맨 뒤로 보냄 (시계방향 출력을 용이하게 하기 위해서 원소 순서 맞춰주는 작업)
    temp = dq.front();
    dq.pop_front();
    dq.push_back(temp);

    // 출력
    for(i=(int)dq.size()-1; i>=0; i--)
        cout<<dq[i];
}
