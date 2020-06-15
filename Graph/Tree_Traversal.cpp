#include <stdio.h>

typedef struct nd
{
    char vertex;
    struct nd * left;
    struct nd * right;

    nd()    //  생성자
    {
        vertex = 'A';
        left = NULL;
        right = NULL;
    }
}node;

void preorder( node* );
void inorder( node* );
void postorder( node* );

node graph[27]; //  graph 저장
int N;  //  노드 갯수

int main()
{
    int i;
    char vertex,left,right;

    //  입력부
    scanf("%d", &N);
    for(i=0; i<N; i++)
    {
     //  문자 입력 받을 때.. 앞에 공백 넣어주자 (그래야 공백,\n 으로 문자가 구분되어져서 제대로 입력 된다)
        scanf(" %c %c %c", &vertex, &left, &right);

        graph[vertex-'A'].vertex = vertex;
        if(left != '.') graph[vertex-'A'].left = graph + (left-'A');
        if(right != '.') graph[vertex-'A'].right = graph + (right-'A');
    }

    preorder(graph);
    printf("\n");
    inorder(graph);
    printf("\n");
    postorder(graph);

    return 0;
}

void preorder( node* nd )
{
    if( nd == NULL ) return;

    printf("%c", nd->vertex);
    preorder(nd->left);
    preorder(nd->right);

}
void inorder( node* nd )
{
    if( nd == NULL ) return;

    inorder(nd->left);
    printf("%c", nd->vertex);
    inorder(nd->right);
}
void postorder( node* nd )
{
    if( nd == NULL ) return;

    postorder(nd->left);
    postorder(nd->right);
    printf("%c", nd->vertex);
}
