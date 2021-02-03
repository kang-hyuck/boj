#include <stdio.h>

int N,M;
char map[510][510];
char dirChar[4] = {'U', 'R', 'D', 'L'};
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};
int ansCnt,ansIndex;
int startY,startX,  voyager;

void Start(int);

int main()
{
    int i,j;

    // 입력부
    scanf("%d %d", &N,&M);
    
    for(i=0; i<N; i++)
        for(j=0; j<M; j++)
            scanf(" %c", &map[i][j]);
            
    scanf("%d %d", &startY,&startX);
    startY=startY-1;   startX=startX-1; // 인덱스 맞추기. 맵은 인덱스 0부터. 입력은 1부터 이므로.


    // 실행부
    for(i=0; i<4; i++)
    {
        Start(i); // 각 방향 마다 시뮬레이션 실행.
        if(voyager==1) break; // voyager이면 남은 방향들은 시뮬레이션 해볼 필요없다
    }
    
    
    // 출력부
    printf("%c\n", dirChar[ansIndex]);
    if(voyager==1) printf("Voyager\n");
    else printf("%d\n", ansCnt);

    
    return 0;
}

void Start(int startDir)
{
    int y,x, dir, cnt;
    
    y=startY;  x=startX;  dir=startDir;  cnt=1; // 
    
    while(1)
    {
        // 다음 위치 이동
        y = y + dy[dir];   x = x + dx[dir];
               
        // 종료 조건
        if( y<0 || x<0 || y >=N || x>=M ) return; // 1. 맵을 벗어난 경우
        if( map[y][x] == 'C' ) return; // 2. 블랙홀을 만난경우
        if( y==startY && x==startX && dir==startDir ){voyager=1; return;} // 3. 제자리로 돌아올 경우
        
        // 방향 전환이 필요한 경우
        if( map[y][x] == '/' && dirChar[dir]=='U') dir=(dir+1)%4;
        else if( map[y][x] == '/' && dirChar[dir]=='D') dir=(dir+1)%4;
        else if( map[y][x] == '/' && dirChar[dir]=='R') dir--;
        else if( map[y][x] == '/' && dirChar[dir]=='L') dir--;
        else if( map[y][x] == '\\' && dirChar[dir]=='U' ) dir=3;
        else if( map[y][x] == '\\' && dirChar[dir]=='D' ) dir--;
        else if( map[y][x] == '\\' && dirChar[dir]=='R' ) dir++;
        else if( map[y][x] == '\\' && dirChar[dir]=='L' ) dir=0;
        
        // 카운트
        cnt++;
        if( cnt > ansCnt )
        {
            ansCnt = cnt;
            ansIndex = startDir;
        }
    }
}
