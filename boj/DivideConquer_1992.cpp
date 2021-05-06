/* DivideConquer_1992, 쿼드트리 */
/* 포인트
 1. DFS에서는 "색검사", "출력"을 담당하게 되는데, 현재DFS에서 출력할 수 없는 영역은 자식노드에서 다시 4분할해서 출력하게끔 호출하는식으로 구현하면 된다.
 2. DFS에서 4곳으로 영역을 나누어서 출력한다. 코드가 비슷하므로... sy[],sx[]배열 이용해서 2중반복문 시작인덱스만 바꿔주는식으로 구현했다.
 3. 2중반복문에서 끝나는인덱스... sy[]+size/2, sx[]+size/2로.. sy,sx값 더해주어야 하는것 유의하자 (종종 실수하는 부분..)
*/
#include <stdio.h>
using namespace std;

// 전역변수선언
int N;
int map[80][80];

// 함수선언
void DFS(int,int, int);

int main()
{
    // 입력부
    scanf(" %d", &N);
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) scanf(" %1d", &map[i][j]);  // 맵에 입력

    //실행부
    ///  1. 압축을 하지않아도 되는 경우
    int diff=0;
    for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(map[i][j] != map[0][0]) diff=1;  // 영상색을 모두 확인한다 (다른색이 있는지)
    if(diff==0){printf("%d", map[0][0]);  return 0;}  // 압축할 필요가없으면 색출력 후 종료
    ///  2. 압축을 해야하는 경우
    if(diff==1){ printf("(");   DFS(0,0, N);   printf(")");}    // 압축할 필요가있으면 4곳으로 나눈다.

    return 0;   
}

void DFS(int yy, int xx, int size)
{
    // 변수선언
    int sy[4]={yy, yy,         yy+size/2, yy+size/2};  // 4각형 시작인덱스 위치계산
    int sx[4]={xx, xx+size/2,  xx,        xx+size/2};  // "실행부"부분에서 "똑같은코드 재활용"하려고 이렇게 구현함..

    // 실행부
    for(int k=0; k<4; k++)  // 4곳 위치값 출력한다 (왼쪽위, 오른쪽위, 왼쪽아래, 오른쪽아래)
    {
        int diff=0;

        // 영상 색검사 (1개라도 다르면 diff값 1, 모두 같다면 diff값 0)
        for(int i=sy[k]; i<sy[k]+size/2; i++) for(int j=sx[k]; j<sx[k]+size/2; j++) if(map[i][j] != map[sy[k]][sx[k]]) diff=1;

        // 영상 색검사 결과확인
        if(diff==1){printf("(");  DFS(sy[k],sx[k], size/2);  printf(")");}  // "자식노드"에서 숫자출력 (영상색 "1개라도" 다른 경우)
        if(diff==0) printf("%d", map[sy[k]][sx[k]]);  // 현재 위치값 출력 (영상색 "모두" 같은 경우)
    }   
}
