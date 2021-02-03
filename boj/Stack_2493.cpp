/* Stack_2493, 탑 */
/* 포인트
 1. 오른쪽에서 왼쪽을 바라보았을 때, 눈에 보이는 탑을 스택에서 탐색해서 찾아주면 된다.
    6 5 4 3 2 .. 탑이 이런 순서로 나온다면 2 다음에 오른쪽에 나오게 될 탑의 입장에서, 2,3,4,5,6 순서대로 자신의 눈에 보이는 탑인지 아닌지 확인하면 됨
    만약 2 오른쪽에 있는 탑이 4 였다면 4 옆에 나오게 될 탑은 6,5,4 중에 자신의 눈에 보이는 탑을 확인하면 되므로. 자신의 눈에 안보이는 탑은 제거해주고
    다음 오른쪽에 나올 탑을 위해서 스택에 자신의 값을 채워 넣으면 된다.
 2. while()문 안에 스택 탐색 조건 2개를 넣어주고, while()문 밖으로 나왔을 때 탐색 종료 이유를 확인 해서 처리하는게 깔끔하다
    Merge Sort 구현할 때 사용했던 방식을 착안했음.
*/
#include <iostream>
#include <stack>
using namespace std;

typedef struct top{
    int height, order;
}top;

int N;
stack<top> s;

void Start(void);

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    cin>>N;

    // 실행부
    Start();

    return 0;
}

void Start()
{
    int temp,order;
    top cur;  // 조사할 탑
    order=1;  // 순서 정보에 넣어줄 값

    while(N--)  // 데이터 갯수(=출력할 갯수)만큼 실행.
    {
        // 조사할 탑의 정보(높이,순서)를 넣음
        cin>>temp;
        cur.height=temp;   cur.order=order++;  // 순서 값 넣고 1 증가

        // 스택을 탐색한다 (자기 값 이상인 값이 나올 때 까지)
        while(!s.empty() && s.top().height<cur.height)  // 스택이 비거나 || 자기보다 높은 값이 나타날 경우 종료 됨
        {
            s.pop();  // 스택에서 값을 꺼냄
        }

        // 탐색 종료 이유 확인 및 처리
        if(s.empty()){cout<<"0 "; s.push(cur);}  // 스택이 비어있어서 종료 된 거라면 0 출력후 자신의 값 넣음
        else{cout<<s.top().order<<" ";s.push(cur);}  // 자기 값보다 "이상인 값"이 나타난 거라면 해당 탑의 순서 출력해주고 자신의 값을 넣음
    }
}
