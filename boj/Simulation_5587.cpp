/* Simulation_5587, 카드 캡터 상근이 */
/*
 기본 (시뮬레이션)문제
 "보유한 카드" 중 "제출된 카드" 보다 (크면서&&보유카드중 작은 값)이 나와야 한다
 따라서 for문으로 보유 카드들의 값을 확인 해야한다
*/
#include <iostream>
#include <deque>
#include <algorithm>  //sort()
using namespace std;

int n, fin, submit,turn;
int used[210];  // 1: 상근이 카드  0: 근상이 카드
deque<int> card[2];

void Start(void);
void Submit(int);

int main()
{
    int i,temp;

    // 입력부
    cin>>n;
    for(i=0; i<n; i++){ cin>>temp;  card[0].push_back(temp); used[temp]=1;}
    sort(card[0].begin(), card[0].end());
    for(i=1; i<=2*n; i++) if(used[i]==0) card[1].push_back(i);  // 남은 카드는 근상이 카드

    // 실행부
    Start();
    
    // 출력부
    cout<<(int)card[1].size()<<"\n"<<(int)card[0].size();

    return 0;
}

void Start()
{
    while(1)
    {
        // 종료조건
        if(fin==1) return;

        // 카드 제출
        Submit(turn);
    }
}

void Submit(int people)
{
    int flag=0;

    // 제출할 카드가 있는 경우 ( (제출된 카드) < (보유 카드) 인 경우 )
    for(int i=0;  i<(int)card[people].size();  i++)
        if(submit < card[people][i])  // 보유 카드 중 제출할 카드가 있는 경우. 카드 제출후 반복문 빠져나온다
            {flag=1; submit=card[people][i];  card[people].erase(card[people].begin()+i); break;}
    
    // 제출할 카드가 없는 경우
    if(flag==0){
        turn = !people;   // 턴이 넘어간다
        submit = 0;  // 카드가 사라진다
        return;
    }
    
    // 카드를 모두 제출한 경우 (게임 종료)
    if( 0 == (int)card[people].size() ) fin=1;
    
    // 턴 넘기기
    turn = !people;
}
