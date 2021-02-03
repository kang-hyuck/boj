#include <stdio.h>
#include <vector>
using namespace std;

int dx[4]={1, 0, -1, 0}; // 동남서북
int dy[4]={0, 1, 0, -1}; 
int map[110][110];
int crashWall, crashRobot;
int ansRobot, ansRobot2;

typedef struct robotInfo{
    int y,x, dir;
}robotInfo;

vector<robotInfo> robot; // 로봇 정보(위치,방향) 저장 벡터. index는 로봇 번호.

int B,A,  N,M;  // B:세로,A:가로,  N:로봇위치 갯수,M:명령어 갯수

void Move(int, char, int); // 명령어 받아서 움직임
int DirtoInt(char);

int main()
{
    int i, x,y, num,iter;
    char c;

    // 입력부
    scanf("%d %d", &A,&B); // 맵 크기
    scanf("%d %d", &N,&M); // 로봇위치 갯수, 명령어 갯수    
    
    robot.push_back({0,0,0}); // "로봇번호"랑 인덱스 맞춰주기 위한  용도. 더미값.
    for(i=1; i<=N; i++)
    {
        scanf("%d %d %c", &x,&y,&c);
        y=B-y+1;
        robot.push_back({y,x,DirtoInt(c)}); // 로봇정보 저장.
        map[y][x]=i; // 맵에 "로봇번호"만 적는다. "로봇정보"(위치,방향 등)는 robot 벡터에 있음
    }


    // 실행부
    for(i=0; i<M; i++)
    {
        scanf("%d %c %d", &num, &c, &iter);
        Move(num, c, iter); // 시뮬레이션 시작.
        if(crashWall==1 || crashRobot==1) break; // 시뮬레이션 결과 확인.
    }
    
    
    // 출력부
    if(crashWall==1) printf("Robot %d crashes into the wall\n", ansRobot);
    else if(crashRobot==1) printf("Robot %d crashes into robot %d\n", ansRobot,ansRobot2);
    else printf("OK\n");
    
    
    return 0;
}

void Move(int num, char command, int iter)
{
    int y,x;
    
    // 해당 명령어일 경우 아래 실행.
    while(iter--)
    {
        // 방향 전환인 경우.
        if(command == 'L' ) robot[num].dir = (robot[num].dir==0)?3:robot[num].dir-1;
        if(command == 'R' ) robot[num].dir = (robot[num].dir==3)?0:robot[num].dir+1;

        // 앞으로 이동인 경우.
        if(command == 'F')
        {
            y = robot[num].y + dy[robot[num].dir];
            x = robot[num].x + dx[robot[num].dir];
            
            // 이동 불가능한 경우.
            if( y<1 || x<1 ||  y>B || x>A ){ansRobot=num; crashWall=1; return;} // 맵 벗어나는 경우
            if( map[y][x]!=0 ){ansRobot=num; ansRobot2=map[y][x]; crashRobot=1; return;} // 로봇과 충동하는 경우
            
            // 이동 가능한 경우. (1.맵에 표시, 2. 로봇정보 갱신)
            map[robot[num].y][robot[num].x] = 0; // 이전 위치 지워줌
            map[y][x] = num; // 이동한 위치 표시
            robot[num].y = y;  robot[num].x = x; // 로봇 정보 갱신   
        }
    }
}

int DirtoInt(char c)
{
    if(c=='E') return 0;
    if(c=='S') return 1;
    if(c=='W') return 2;
    if(c=='N') return 3;
    
    return 0;
}
