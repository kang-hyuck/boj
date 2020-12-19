#include <stdio.h>
#define INF 987654321

void floyd(void);
void print_map(void);

int map[110][110];
int n,m;    //  n:도시(노드) 갯수,    m:버스(엣지) 갯수

int main()
{
    int i,j,  a,b,c;
    
    //  입력부
    scanf("%d", &n);
    scanf("%d", &m);
    for(i=0; i<m; i++)
    {
        scanf("%d %d %d",   &a,&b,&c);
        if( (map[a][b]>c)||(map[a][b]==0) ) map[a][b] = c;
    }
      
    //  초기화,    버스 없는 곳(0인 곳)은 INF로 초기화 해준다
    for(i=1; i<=n; i++)
        for(j=1; j<=n; j++)
        {
            if( map[i][j] == 0 ) map[i][j] = INF;
            if( i==j ) map[i][j] = 0;               //  자기 위치는 0
        }

    //  Floyd-Warshall 실행
    floyd();

    //  출력부
    print_map();


    return 0;
}

void floyd()
{
    int i,j,k;
    
    for(k=1; k<=n; k++)
        for(i=1; i<=n; i++)
            for(j=1; j<=n; j++)
                if( map[i][j] > map[i][k] + map[k][j] ) map[i][j] = map[i][k] + map[k][j];
    
    return;
}

void print_map()
{
    int i,j;
    
    for(i=1; i<=n; i++)
    {
        for(j=1; j<=n; j++)
        {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }
    
    return;
}
