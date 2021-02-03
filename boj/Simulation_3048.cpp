#include <iostream>
#include <string>
#include <vector>
#include <utility> // pair<>
#include <algorithm> // swap
using namespace std;

#define f first
#define s second

int N1,N2,  T;
string group1, group2;
vector<pair<char,int>> ants;  // <문자, 속한 group>

int main()
{
    int i;

    ios_base::sync_with_stdio(false); // cin,cout 속도향상
    cin.tie(NULL);   cout.tie(NULL);
    
    // 입력부
    cin>> N1 >> N2;
    cin>> group1 >> group2;
    cin>> T;
    reverse(group1.begin(), group1.end()); // 개미 group1 index 순서 뒤집어 준다.
    for(i=0; i< N1; i++) ants.push_back( {group1[i], 1} ); // 개미 group1 넣어준다.
    for(i=0; i< N2; i++) ants.push_back( {group2[i], 2} ); // 개미 group2 넣어준다.


    // 실행부
    while(T--)
    {
        // 1초마다 왼쪽에서 오른쪽으로 전체 확인해서. group1, group2 개미가 만나는 경우만 위치를 서로 바꿔주면 된다.
        for(i=0; i<N1+N2-1; i++) // 맨 오른쪽에 위치한 개미는 오른쪽(i+1)에 비교할 개미가 없으므로. N1+N2-1 까지만 확인.
            if( ants[i].s==1 && ants[i+1].s==2 )  // 개미 group1,group2가 서로 만나는 경우만 서로 위치 바꿔준다.
            {
                swap(ants[i],ants[i+1]);
                i++; // i인 경우 i+1과 위치를 바꿨으므로. 다음 for문은 i+1+1 = i+2 값부터 확인하면 된다. 벡터 index 벗어나면 for문 안들어옴.
            }
    }
    
    
    // 출력부
    for(i=0; i<N1+N2; i++)
        cout<<ants[i].f;


    return 0;
}
