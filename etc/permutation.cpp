#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v1;

//  [입력부]
//   - vector안에 값을 저장 한다
//  [실행부]
//   - 처음에 vector안의 값에 따른 조합을 출력한다
//   - 다음 while문 안에서 next_permutation을 통해 vector안의 값으로 다른 순열을 만들어낸다

//  * 참고사항 *
//   - <algorithm> 헤더를 추가해야 next_permutation 를 사용할 수 있다
//   - 원소 값이 겹칠 경우도 알아서 파악하고 순열을 만들어준다 (겹치는 경우 예: {1, 1, 3})
//   - 만약 더이상 만들 순열 경우의 수가 없을 경우 false를 반환 (만약 성공적으로 생성할 경우 true 반환)

//  http://www.cplusplus.com/reference/algorithm/next_permutation/
//  https://twpower.github.io/82-next_permutation-and-prev_permutation

int main()
{
    int i;
    
    //  [입력부]
    for(i=0; i<3; i++)
        v1.emplace_back(i);
   
    
    
    //  [실행부] , 처음에 벡터의 원소저장 상태 그대로 순열 경우의 수를 하나 출력하고, 다음부터 next_permutation을 실행 해준다
    for(i=0; i<3; i++)
            printf("%d ", v1[i]);
    printf("\n");
    
    while( next_permutation(v1.begin(),v1.end()) )
    {
        for(i=0; i<3; i++)
            printf("%d ", v1[i]);
        printf("\n");
    }
    
    
    
    
    
    return 0;   
}


