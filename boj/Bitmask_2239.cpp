/* BOJ_2239, 스도쿠 */
/* 포인트
(비트마스크 + 완전탐색) 문제
 1. DFS에서 자식 노드의 호출방향이 "오른쪽"이고, 열 오른쪽 끝일 경우 "아랫행"으로 넘어간다
    y,x 좌표를 수동으로 DFS 인자로 넣어주어서 호출했는데, 조건문 사용해서 DFS를 호출해야되어서 깔끔하지 않다..
    이런 특이한 경우에는 y,x좌표 대신에 cnt값 1개로 넣어주어서 인자로 받은 cnt에서 y,x를 계산하게끔 하는게 깔끔하다 (실수가 적어진다는 의미!!)
 2. 행,열,3x3박스 각각 보유한 숫자 상태를 "비트마스크"로 저장했는데 굳이 비트마스크 안사용하고 "배열"로 1~9 들어갈 수 있는 칸 하나 더 만드는게 나은듯
 3. 이 경우는 해당 위치에서 "무조건" 숫자를 채워넣고 자식노드를 호출해야하므로... 2차원 조합 사용하면 안된다. 따라서 자식 호출시 2중for문 필요 없다
 4. 해당 노드 갯수만큼 카운트 되었을 때 DFS에서 결과 출력하고 프로그램을 종료시키면 된다.
*/
#include <iostream>
#include <stdio.h>
using namespace std;

int row[9];
int col[9];
int cluster[3][3];

int map[15][15];

void DFS(int);
void Print(void);

int main()
{
    int i, j, temp;

    // 입력부
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
        {
            scanf("%1d", &temp);
            map[i][j] = temp;
            row[i] |= (1 << temp);  col[j] |= (1 << temp);  cluster[i / 3][j / 3] |= (1 << temp);   // 행,열,3x3박스에 해당 숫자 보유 상태 표시
        }

    // 실행부
    DFS(0);

    return 0;
}

void DFS(int cnt)
{
    int y, x, k;

    // 현재 위치 계산
    y = cnt / 9;  x = cnt % 9;

    // 스도쿠 끝났는지 확인 (마지막 노드까지 다 채우고 온 경우)
    if (cnt == 81) { Print();  exit(0); }

    // 자식 노드 호출 (스도쿠 끝나지 않은 경우)
    if (map[y][x] == 0) // 숫자를 쓸 수 있는 칸인 경우
        for (k = 1; k <= 9; k++)  // 쓰고자 하는 숫자
        {
            // k를 칸에 쓸 수 없는 경우 (행,열,3x3박스에 숫자 k가 있는 경우)
            if ((row[y] & (1 << k)) || (col[x] & (1 << k)) || (cluster[y / 3][x / 3] & (1 << k)))  continue;  // 해당 숫자가 있다면

            // k를 칸에 쓸 수 있는 경우 (행,열,3x3박스에 숫자 k가 없는 경우)
            row[y] |= (1 << k);    col[x] |= (1 << k);   cluster[y / 3][x / 3] |= (1 << k);   // row,col,cluster에 숫자 k 있음을 표시
            map[y][x] = k;   // 숫자 적어줌

            DFS(cnt + 1);  // 다음 칸 이동

            map[y][x] = 0;   // 숫자 지워줌
            row[y] &= ~(1 << k);   col[x] &= ~(1 << k);  cluster[y / 3][x / 3] &= ~(1 << k);  // row,col,cluster에 숫자 k 표시 제거
        }
    else if (map[y][x] != 0)  // 숫자를 쓸 수 없는 칸인 경우
    {
        DFS(cnt + 1);  // 다음 칸 이동
    }
}

void Print()
{
    int i, j;

    // 맵 출력
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
            cout << map[i][j];
        cout << "\n";
    }
}
