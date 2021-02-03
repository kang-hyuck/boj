/* Simulation_19236, 청소년 상어 */
/* 포인트
  (시뮬레이션 + 완전탐색) 문제다
  자식노드 호출 시, 현재 정보 (물고기 정보, 맵 정보 등)를 부모노드 내에서 백업 해주고
  자식노드에서 부모노드로 돌아왔을 때 되돌려 주는 작업을 하였다  
*/
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

typedef struct fishInfo{
    int y,x, dir;
}fishInfo;

int map[15][15];
fishInfo fish[20];
fishInfo shark;

int dx[9] = {0,   0, -1, -1, -1,   0, 1, 1, 1};   // 0번 더미
int dy[9] = {0,  -1, -1,  0,  1,   1, 1, 0,-1};
int ans;

void MoveFish(void);
void SwapFish(int, int);
void DFS(int);

int main()
{
    int i,j, num,dir;

    // 입력부
    for(i=0; i<4; i++)
        for(j=0; j<4; j++)
        {
            cin>>num;  cin>>dir;
            fish[num] = {i,j,dir};
            map[i][j] = num;
        }

    // 실행부
    // 초기에 상어가 (0,0) 물고기의 정보를 갖는다.
    ans += map[0][0];  // 정답에 더해줌
    shark = fish[map[0][0]];  // 물고기 정보를 갖는다
    fish[map[0][0]] = {0,0,0};  // 잡아먹힌 물고기 정보 지워줌
    map[0][0] = 0;  // 맵에 물고기 표시 지워줌
    DFS(ans);  // DFS시작

    // 출력부
    cout<<ans;  

    return 0;
}

void DFS(int sum)
{
    int y,x,dir, num;
    int backup[15][15];
    fishInfo backupFish[20];
    fishInfo backupShark;

    // 정답 갱신
    ans = max(ans, sum);

    // 물고기 이동
    MoveFish();  // 아래에 넣어버리면... 물고기 먹을 때마다 호출된다...

    // 자식 노드 호출
    y = shark.y;  x = shark.x;  dir = shark.dir;
    while(1)
    {
        y = y + dy[dir];  x = x + dx[dir];

        // 이동할 수 없는 경우
        if(y<0 || x<0 || y>=4 || x>=4) return;  // 종료

        // 잡아 먹을 수 없는 경우
        if(map[y][x]==0) continue;  // 먹을 물고기가 없는 칸인 경우

        // 잡아 먹을 수 있는 경우
        memcpy(backup, map, sizeof(map));  // 현재 물고기 맵 표시 저장
        memcpy(backupFish, fish, sizeof(fish));  // 현재 물고기 정보(위치+방향) 저장
        backupShark = shark;  // 상어 위치 정보 저장
        num = map[y][x];  // 잡아먹을 물고기 번호 저장

        // 잡아 먹는다
        shark = fish[map[y][x]];  // 상어가 물고기 정보를 가진다
        fish[map[y][x]] = {0,0,0};  // 잡아 먹힌 물고기 정보 지움
        map[y][x] = 0;  // 잡아 먹힌곳 0으로 표시

        DFS(sum+num);  // 물고기 번호 더해줌

        // 복구 한다
        shark = backupShark;  // 상어 위치 정보 복원
        memcpy(map, backup, sizeof(backup));   // 물고기 맵 표시 복원
        memcpy(fish, backupFish, sizeof(backupFish));  // 물고기 정보 복원
    }
}

void MoveFish()
{
    int i, yy,xx,y,x,dir;

    // 1~16번 물고기 전부 한마리씩 이동
    for(i=1; i<=16; i++)
    {
        yy=fish[i].y;  xx=fish[i].x;  dir=fish[i].dir;

        // 살아있지 않은 물고기인 경우
        if(dir==0) continue;  // 방향이 0이면 살아있지 않은 물고기임

        // 살아있는 물고기인 경우 (이동 하려는 방향 계산)
        y = yy + dy[dir];   x = xx + dx[dir];

        // 이동할 수 없는 경우 (방향을 계속 전환 한다)
        while( (y<0 || x<0 || y>=4 || x>=4) || (shark.y==y && shark.x==x) )  // 맵을 벗어나거나 || 상어가 있는 경우
        {
            dir = dir==8 ? 1:dir+1;  // 반시계 방향 회전
            y = yy + dy[dir];   x = xx + dx[dir];
        }

        // 이동할 수 있는 경우
        if(map[y][x]!=0) SwapFish(i, map[y][x]);  // i번 물고기랑 이동하려는 곳에 있는 "물고기랑 위치 정보" 바꿈 (방향은 각자 유지)
        else {fish[map[yy][xx]].y = y;  fish[map[yy][xx]].x = x;}  // 아무 곳도 없는 곳에는 물고기가 그냥 이동 하면됌... 여기 때문에 ㅠ 3시간 동안 디버깅함
        swap(map[yy][xx], map[y][x]);  // map에 "물고기 표시" 위치 바꿈
        fish[i].dir = dir;  // 바뀐 물고기 dir 저장 해주어야 한다
    }
}

void SwapFish(int a, int b)
{
    fishInfo temp;    temp = fish[a];
    fish[a].y = fish[b].y;   fish[a].x = fish[b].x;   // a에 b위치 넣음
    fish[b].y = temp.y;      fish[b].x = temp.x;      // b에 a위치 넣음
}
