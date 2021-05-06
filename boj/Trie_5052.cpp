/* Trie_5052, 전화번호 목록 */
/* 포인트
 1. "트라이구조체 1개"가 "문자 1개"에 1:1 대응된다.
 2. 문자열 입력을 다 안받고.. 중간에 입력함수을 종표하고 NO/YES를 바로 판단해버리니까.. 입력들이 남아서 계속 "시간초과" 떴다..
 3. 트라이 구조체 안에 "변수"(플래그)를 만들어주어서, Insert 중에 "일관성 위배"되는지 안되는지 확인할 수 있게끔 해주었다.
    변수 추가하는식으로 구현하면.. 굳이 Find함수 정의한해도 된다.
 4. 부모트라이에서 "자식트라이가 갖는 문자"를 저장하게 되는데, 문자가 "A-Z" 인지, "0-9"인지에 따라서 index 계산할 때
    빼주는 문자가 'A'인지 '0'인지 결정된다. 이 부분에서 제대로 매칭해주지 않으면 세그먼트오류 뜰 수 있다.
 5. new로 트라이를 구현해놓고나서 소멸자 delete로 제거해주지 않으면 메모리초과 뜰 수도 있다고함.. 
 6. 문자를 root에 연결할 때, 문자열 1번째 문자의 주소를 1번만 넣어주면 된다.
 7. 멤버함수 "외부정의"할 때... "구조체이름::외부함수" 모양으로 정의해준다는 것 유의할 것.
*/
#include <stdio.h>
using namespace std;

// 트라이 구조체
typedef struct TRIE{
    bool finish,childExist;  TRIE *node[10];
    TRIE();   ~TRIE();   void Insert(char*);
}TRIE;

// 전역변수선언
int T,N, finishSimulation;

int main()
{
    char temp[10010];

    scanf("%d", &T); // 테스트케이스 저장
    for(int t=0; t<T; t++)  // 테스트케이스 횟수만큼 실행
    {
        // 입력부
        scanf("%d", &N);  // 문자갯수 저장
        TRIE root;   finishSimulation=0;  // 변수초기화 (root트라이, 시뮬레이션종료 플래그)

        // 실행부
        for(int i=0; i<N; i++)  // 모든 문자열 확인
        {
            // 문자열입력
            scanf("%s", temp);

            // 트라이실행
            root.Insert(&temp[0]);   // root에 연결
        }

        // 출력부
        if(finishSimulation==1) printf("NO\n");   // 트라이 구현불가능한 경우 (전화번호 "일관성"이 없는 경우)
        if(finishSimulation==0) printf("YES\n");  // 트라이 구현가능한 경우 (모든 문자열이 트라이로 만들어지는 경우)
    }

    return 0;
}

TRIE::TRIE(){  // 트라이 생성자
    finish=false;  childExist=false;  for(int i=0; i<10; i++) node[i]=NULL;
}
TRIE::~TRIE(){  // 트라이 소멸자
    for(int i=0; i<10; i++) if(node[i]!=NULL) delete node[i];  // new로 할당했던 것 제거해준다.
}
void TRIE::Insert(char *str){  // 해당문자를 "자식"으로 등록한다.
    // 종료조건
    if(*str=='\0' && childExist==1){finishSimulation=1; return;}  // 추가하려는 문자열이 끝에 도착 && 자식트라이가 존재하는 경우 "일관성 전화번호 위배".
    if(*str=='\0'){finish=true;  return;}  // 추가하려는 문자열이 끝에 도착한 경우 (현재트라이의 finish변수 true로 체크)
    if(finish==true){finishSimulation=1; return;} // 추가하려는 문자열이 존재하지만 && 현재트라이에서 끝나는 문자열이 존재하는 경우 "일관성 전화번호 위배".

    // 추가하려는 문자가 존재하는 경우
    childExist=true;  // 자식트라이가 존재함을 표시 
    int index = *str - '0';  // 인덱스계산 (자식문자)
    if(node[index]==NULL) node[index] = new TRIE();  // 자식트라이 생성 (해당문자에 대응되는)
    node[index]->Insert(str+1);  // "자식트라이"의 Insert에 "다음 문자주소"를 넣어준다.
}

