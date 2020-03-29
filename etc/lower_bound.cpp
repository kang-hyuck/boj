#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> v1;

    //  lower_bound
    //   - 찾는 숫자의 index번호    =    lower_bound( , , ) - 배열주소
    //   - 찾는 숫자가 여러개 존재하는 경우 가장 낮은 index 출력
    //   - %ld 형으로 출력 해준다
    //   - binary search로 찾는다, O(logN)

int main()
{   
    //  [입력부]
    v1.push_back(10);
    v1.push_back(20);
    v1.push_back(10);
    v1.push_back(30);
    v1.push_back(20);
    v1.push_back(50);
      
    
    //  [출력부]
    printf("%ld", lower_bound(v1.begin(),v1.end(), 50)-v1.begin() );
    
    
    return 0;   
}
