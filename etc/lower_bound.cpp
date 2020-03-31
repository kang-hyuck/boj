#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v1;

    //  lower_bound
    //   - 찾는 숫자의 index번호    =    lower_bound( , , ) - 배열주소
    //   - 찾는 숫자가 여러개 존재하는 경우 가장 낮은 index 출력한다
    //   - 찾는 숫자와 "같거나 다음으로 큰" 원소의 index를 출력한다
    //   - %ld 형으로 출력 해준다
    //   - binary search로 찾는다, O(logN)

    //  * 참고사항 *
    //   - binary search의 선행조건은 원소들이 미리 "정렬" 되어 있어야 한다

int main()
{   
    //  [입력부]
    int i;
    for(i=0; i<5; i++)
        v1.push_back(10*i);
      
    
    //  [출력부],  이렇게 15를 찾으려고 하면 "2"가 출력된다
    printf("%ld", lower_bound(v1.begin(),v1.end(), 15)-v1.begin() );
    
    
    return 0;   
}
