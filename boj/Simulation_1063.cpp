#include <iostream>
#include <string>
using namespace std;

// 맵의 가장 아랫행부터 0으로 정했으므로, 맵을 상하 뒤집어서 방향을 정한다.
string dir[] = {"R", "L", "B", "T", "RT", "LT", "RB", "LB"}; 
int dx[] =     { 1,  -1,   0,   0,    1,   -1,    1,   -1 };
int dy[] =     { 0,   0,   -1,  1,    1,    1,   -1,   -1 };

int KingX, KingY,   StoneX,StoneY;
int NextKingX,NextKingY,  NextStoneX,NextStoneY;
int N;

void Move(string);
bool CheckRange(int,int);
bool CheckCrushStone(int,int,int,int);

int main()
{
    string KingPosition,StonePosition, command;

    // 입력부
    cin>> KingPosition >> StonePosition >> N;
    KingX  = KingPosition[0]-'A';  KingY  = KingPosition[1]-'1';
    StoneX = StonePosition[0]-'A'; StoneY = StonePosition[1]-'1';

    // 실행부
    while(N--)
    {
        cin>> command;
        Move(command);
    }

    // 출력부
    cout<<(char)(KingX+'A')<<KingY+1<<'\n';
    cout<<(char)(StoneX+'A')<<StoneY+1;
}

void Move(string command)
{
    int i;
    for(i=0; i<8; i++)
    {
        // 해당 명령어 아니면 skip
        if( command != dir[i] ) continue;

        // 해당 명령어 진입시 아랫 부분 실행.
        NextKingY = KingY + dy[i];
        NextKingX = KingX + dx[i];
        NextStoneY = StoneY + dy[i];
        NextStoneX = StoneX + dx[i];

        if( !CheckRange(NextKingY,NextKingX) ) return; // 맵 벗어나면 안움직이고 종료한다.
        if( CheckCrushStone(NextKingY,NextKingX, StoneY,StoneX) ) // 돌이랑 부딪히면 추가적으로 실행되는 부분.
        {
            if( !CheckRange(NextStoneY,NextStoneX) ) return; // 돌맹이가 맵 내부로 이동하는지 확인. 못움직이면 종료.
            // 돌맹이는 부딪혀야지 움직인다.. 여기서 갱신해준다.
            StoneY = NextStoneY;
            StoneX = NextStoneX;
        }

        // 움직이고 난 후 위치 저장.
        KingY = NextKingY;
        KingX = NextKingX;

        return;
    }
}
bool CheckRange(int y,int x)
{
    // 맵 범위 안에 있는지 확인.
    if( y>=0 && x>=0 && y<8 && x<8 ) return true;
    return false;
}
bool CheckCrushStone(int NextKingY,int NextKingX,int StoneY,int StoneX)
{
    // 킹이 움직이려는 곳과 돌이 있는곳이 같으면 충돌.
    if( NextKingY==StoneY && NextKingX==StoneX ) return true;
    return false;
}
