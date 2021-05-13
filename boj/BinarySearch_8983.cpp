/* BinarySearch_8983, 사냥꾼 */
/* 포인트
 1. 사대수(M), 동물수(N)이 각각 1e5이므로. 둘 중 1개를 log 씌워서 줄여야한다 (둘 중 1개를 "이분탐색" 해야한다)
    L값은 어차피 고정된 값이고. 계산에만 사용되므로. log씌울 필요가 없다
 2. "사대관점"에서 잡을 수 있는 동물수를 카운트할 경우... "잡을 수 있는 동물이 겹치는 경우" 누적으로 카운트될 수 있다...
    이렇게되면 중복처리하는 것이 어려우므로... 동물수(N)에 log를 씌워야한다
 3. "동물의관점"에서 자신이 잡히는 사대가 존재하면 ans++, 안잡히면 ans를 카운트하지 않으면 된다..
    따라서 "자신을 잡을 수 있는 사대"를 log씌워서 이분탐색으로 구하면 된다...
 4. 시뮬레이션함수에서 3가지 값을 반환하도록 했다.
    1: 해당동물을 잡을 수 있는 사대가 존재하는 경우
    0: right인덱스를 이동해야하는 경우
   -1: left인덱스를 이동해야하는 경우
   (1)시뮬레이션함수(잡을 수 있는사대가 존재하는지),  (2)인덱스이동함수(left,right 중 어떤것을 움직일 것인지) <- (잡을 수 있는 사대가 없는 경우)
   각각 나누어서 2개 구현해도 되는데... 지저분해보여서 (1),(2) 기능을 합친 함수 1개로 만들었음...
   근데 기능별로 나누어서 구현하는게 더 나은듯... (2)는 if(shootX < animalX) left = mid+1;  이런거다.. (right는 >= 하면 됨..)
*/
#include <iostream>
#include <algorithm>  // sort()
using namespace std;

typedef struct POS{  // POS: position
    int y,x;
}POS;

// 전역변수
int shootPos[100010];
POS animalPos[100010];
int M,N,L, ans;

// 함수선언
void Start();
void BinarySearch(int);   // (동물번호)
int  CanHunt(int,int);    // (사대인덱스,동물번호) =  (-1:left인덱스이동,  0:right인덱스이동,  1:잡을수있음)

int main()
{
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);
    int y,x;

    // 입력부
    cin>>M>>N>>L;
    for(int i=0; i<M; i++) cin>>shootPos[i];   // 사대위치 저장
    for(int i=0; i<N; i++){cin>>x>>y;   animalPos[i]={y,x};}  // 동물위치 저장

    // 실행부
    sort(shootPos, shootPos+M);  // 사대위치 정렬 (이진탐색 사용하려면 "정렬"되어야하므로)
    Start();

    // 출력부
    cout<<ans;

    return 0;
}

void Start()
{
    // 실행부  (동물수만큼 이진탐색 실행)
    for(int i=0; i<N; i++)  BinarySearch(i);
}

void BinarySearch(int num)   // (동물번호)
{
    int left=0,   right=M-1,   mid, res;

    // 실행부
    while(1)
    {
        // 시뮬레이션실행
        mid = (left+right)/2;
        res = CanHunt(mid, num);

        // 인덱스 이동
        if(res==-1) left  = mid+1;
        if(res== 0) right = mid-1;

        // 종료조건
        if(res==1){ans++; return;}  // 잡을 수 있는 경우 (정답수 증가)
        if(left>right)    return;   // 잡을 수 없는 경우 (정답수 증가하지 않음)
    }
}

int CanHunt(int index, int num)
{
    int shootX=shootPos[index],  animalX=animalPos[num].x,   animalY=animalPos[num].y;

    // 잡을 수 있는 경우
    if( (abs(shootX-animalX) + animalY) <= L ) return 1;  // 범위내에 존재하는 경우 (잡을 수 있는 경우)

    // 잡을 수 없는 경우
    if(shootX < animalX) return -1;  // 사대X좌표가 동물X좌표 보다 작은 경우 (left인덱스가 이동해야함)
    return 0;  // 사대X좌표가 동물X좌표 보다 같거나 큰 경우 (right인덱스가 이동해야함)
}
