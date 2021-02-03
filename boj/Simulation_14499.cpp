#include <iostream>
using namespace std;

// y,x 이동이 Move함수 내에서 이루어지는데, 매 명령마다 Move 함수를 호출하지만
// 지역변수 y,x사용해버리면 함수 종료되고나서 y,x위치값 갱신할때 번거로움 (포인터 써야함)
// 그래서 전역변수로 x,y를 여기에 정의해놓고 사용하는게 편하다
int N,M,  x,y,  K; // N:세로, M:가로
int command;

int map[25][25];

//  중앙,동,서,남,북,밑
//  명령에 따른 "변화된 위치"에 "앞 전 index 값" 적어준다.
int dir[5][6] = {
    {0, 0, 0, 0, 0, 0},  // 명령이 1부터 들어오므로 index 맞추기 위하려고 넣음.
    {2, 0, 5, 3, 4, 1},
    {1, 5, 0, 3, 4, 2},
    {4, 1, 2, 0, 5, 3},
    {3, 1, 2, 5, 0, 4}
};
int dice[6]; // 주사위 초기값 모두 0
int temp[6]; // dice 값 복사하여 이동 시킬때 필요.
int dx[] = {0, 1, -1, 0, 0};  // 1:동, 2:서, 3:북, 4:남
int dy[] = {0, 0,  0,-1, 1};

void Move(void);
bool CheckRange(int,int);

int main()
{
    int i,j;
    
    // 입력부
    cin>> N >> M >> y >> x >> K;  // 이 문제.. y,x 입력순서가 반대임.. x,y로 넣어줘서 한 번 틀렸다ㅠ 문제오류..
    for(i=0; i<N; i++)
        for(j=0; j<M; j++)
            cin >> map[i][j];

    // 실행부
    while(K--)
    {
        cin >> command;
        Move();
    }
    
    return 0;   
}

void Move()
{
    int i,j, nx,ny;
    for(i=1; i<5; i++)
    {
        // 해당 명령이 아니면 skip
        if(command != i) continue;
        
        // 해당 명령일 경우 아래 실행
        ny = y + dy[i];
        nx = x + dx[i];
        
        // 다음 이동 위치가 맵 범위 내 인지 확인.
        if( !CheckRange(ny,nx) ) return;
        
        // 이동할 수 있으므로, 변경된 주사위 위치 값을 x,y에 갱신 해준다.
        y = ny;
        x = nx;
        
        // 주사위 굴린다
        for(j=0; j<6; j++)
            temp[j] = dice[ dir[command][j] ]; // dice의 "이전index"에 대응되는 값을 가져와서 넣는다.
        for(j=0; j<6; j++)
            dice[j] = temp[j];
        
        // 주사위 밑에 값 확인
        if( map[y][x] != 0 )
        {
            dice[5] = map[y][x];
            map[y][x] = 0;
        }
        else
        {
            map[y][x] = dice[5];
        }
        
        // 주사위 윗면 출력
        printf("%d\n", dice[0]);
    }
    
    return;
}
bool CheckRange(int y,int x)
{
    if( y>=0 && x>=0 && y<N && x<M ) return true;
    return false;
}
