/* Bitmask_1062, 가르침 */
/* 포인트
 (백트래킹 + Bitmask) 문제
 1. DFS로 내려가면서 선택한 알파벳(문자)를 비트셋에 저장하고, 선택한 알파벳 갯수가 충족되면 글자들을 읽을 수 있는 지 확인한다
 2. DFS로 "조합(Combination)"을 구현하려면 부모노드로부터 현재 노드에서  자식호출시 어디서 부터 for문을 돌릴지에 대한 "index 정보"가 필요하고, DFS 함수 인자로 주어져야한다  
 3. 현재 DFS에서 "선택한 알파벳 비트셋"과 글자가 구성하는 "비트셋"과 AND연산을 해서, "글자를 구성하는 비트셋" 값이 나온다면 그 글자를 읽을 수 있다
 4.  & 연산은 비트연산이므로, 비트값이 나오게 된다 (1,10,13, ...) 그래서 & 연산의 결과값을 == 1 로 비교하면 안된다.. 예로 13 == 1 하면 거짓이다.
 5. "알파벳 보유 상태"를 비트셋으로 구현하는게 vector<char>로 담아서 구현 하는 것보다 "속도" 측면에서 유리하다. 비트셋으로 구현하면 바로 인덱스 위치를 알 수 있는 반면 vector는 for문 돌리고 비교하면서 해당 문자가 있는지 찾아야 한다
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int N, K;
vector<string> v;   // 조사할 단어들 저장용도
int characterBitset;  // 알파벳(character) 비트셋
int ans;
void DFS(int, int);  // DP 할때나 DFS 반환값을 int로... (조합 만들기 위한 인덱스, 지금까지 선택한 알파벳 수)
int  CheckWords(void); // 주어진 알파벳 조합으로 읽을 수 있는 단어 갯수 반환,  "알파벳 비트셋"(현재 DFS에서 선택한 알파벳 조합)은 "전역변수" 그대로 사용해도 됌

int main()
{
    int i;
    string temp;
    ios_base::sync_with_stdio(0);  cin.tie(0);  cout.tie(0);

    // 입력부
    cin >> N >> K;
    for (i = 0; i < N; i++)
    {
        cin >> temp;
        v.push_back(temp);
    }

    // "anta","tica"는 필수이므로. 포함되는 알파벳 넣어줌
    characterBitset |= (1 << ('a' - 'a'));
    characterBitset |= (1 << ('n' - 'a'));
    characterBitset |= (1 << ('t' - 'a'));
    characterBitset |= (1 << ('i' - 'a'));
    characterBitset |= (1 << ('c' - 'a'));

    // 선택해야하는 알파벳 갯수에 5글자 빼준다.
    K = K - 5;
    if (K < 0) { cout << 0; return 0;}  // 선택 해야하는 갯수 5개 미만이면 종료

    // 실행부
    DFS(0, 0);  // (부모 알파벳 인덱스 + 1, 지금까지 선택한 알파벳 수)

    // 출력부
    cout << ans;

    return 0;
}

void DFS(int index, int cnt)
{
    int i;

    // 알파벳 선택 갯수 채운 경우 (읽을 수 있는 글자 갯수 조사 및 정답에 갱신)
    if (cnt == K) { ans = max(ans, CheckWords()); return; }

    for (i = index; i <= (int)('z' - 'a'); i++)  //  조합 구현 (부모알파벳 인덱스 + 1 에서 'z'까지 넣는다),  'z'-'a' 부분에서 등식 < 로 했다가 한 번 틀림 ㅎ.ㅎ
    {
        // 이미 등록된 알파벳인지 검사
        if ((characterBitset & (1 << i))) continue;   // 이미 비트셋에 등록된 알파벳이면 넘긴다

        // 등록 되지 않은 알파벳인 경우
        characterBitset |= (1 << i);   // 비트셋에 알파벳 등록
        DFS(i + 1, cnt + 1);  // (자식에서 검사할 시작 알파벳 인덱스, 알파벳 선택한 갯수 증가)
        characterBitset &= ~(1 << i);  // 자식에서 부모 노드로 돌아온 경우 제거 해주고 다른 자식 호출 계속 진행
    }
}

int  CheckWords()
{
    int i, wordBitset, cnt;
    wordBitset = 0;  // 글자에 들어간 알파벳 체크. characterBitset과 비교용으로 사용
    cnt = 0;  // 읽을 수 있는 글자수 저장용

    for (i = 0; i < (int)v.size(); i++)
    {
        // 단어 1개씩 가져와서 단어에 있는 알파벳을 모두 저장
        for (auto character : v[i])  // v[i]가 단어, character가 문자
            wordBitset |= 1 << (character - 'a');

        // 알파벳 상태 비교
        if ( (characterBitset & wordBitset) == wordBitset) cnt++;  // 알파벳 갯수 같으면 읽을 수 있는 단어 증가

        // 초기화 (다른 단어 조사할때 다시 사용할 것임)
        wordBitset = 0; 
    }

    // 읽을 수 있는 글자수 반환
    return cnt;
}
