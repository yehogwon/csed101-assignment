/**
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022-10-31
 * OS: macOS 12.6
 * IDE Environment: Visual Studio Code 1.72.1
 * GCC version: gcc 14.0.0
 * C Standard: C99
 * Editor and Terminal Font: Consolas
 * Encoding: UTF-8
 * End of Line Sequence: LF
 * Naming Convention: snake_case
*/

// TODO: Refactor this code
// TODO: Add comments on each line
// comments: user_turn, com_call, com_raise, computer_turn

// 필요한 헤더 파일을 포함시킨다. 
#include <stdio.h> // 표준 입출력을 위해 포함시킨다. 
#include <time.h> // 화면 지우기 및 랜덤 시드를 시간 (초)로 설정하기 위해 포함시킨다.
#include <stdlib.h> // 랜덤 함수를 사용하기 위해 포함시킨다.

// 승자 및 현재 턴 정보를 편리하게 저장 및 이용하기 위해 상수 처리한다. 
#define USER 0
#define COMPUTER 1

// 게임에서의 행동을 편리하게 저장 및 이용하기 위해 상수 처리한다.
#define CALL 0
#define RAISE 1
#define FOLD -1

// 카드의 조합을 편리하게 저장 및 이용하기 위해 상수 처리한다.
#define NOPAIR 1
#define DOUBLE 2
#define STRAIGHT 3
#define TRIPLE 4

/**
 * 화면을 지우는 함수
 * 리턴값: 없음
*/
void clear() {
    // FIRE: Change this code below to work on Windows i.e, system("cls");
    system("clear");
}

/**
 * 3개의 숫자가 주어질 때 최댓값을 반환하는 함수
 * 매개변수 a, b, c: 최댓값을 구할 숫자 3개
 * 리턴값: a, b, c 중 최댓값
*/
int find_max(int a, int b, int c) {
    return a > b ? (a > c ? a : c) : (b > c ? b : c); // 중첩된 삼항 연산자를 이용하여 최댓값을 찾는다. 
}

/**
 * 3개의 숫자가 주어질 때 중간값을 반환하는 함수
 * 매개변수 a, b, c: 중간값을 구할 숫자 3개
 * 리턴값: a, b, c 중 중간값
*/
int find_middle(int a, int b, int c) {
    return a > b ? (a > c ? (b > c ? b : c) : a) : (b > c ? (a > c ? a : c) : b);
}

/**
 * 3개의 숫자가 주어질 때 최솟값을 반환하는 함수
 * 매개변수 a, b, c: 최솟값을 구할 숫자 3개
 * 리턴값: a, b, c 중 최솟값
*/
int find_min(int a, int b, int c) {
    return a > b ? (b > c ? c : b) : (a > c ? c : a);
}

/**
 * 게임 상황이 주어졌을 때 게임 상태를 프린트하는 함수
 * 매개변수 round: 현재 진행중인 게임의 라운드 수
 * 매개변수 user_chips: 유저가 갖고 있는 칩의 개수
 * 매개변수 com_chips: 컴퓨터가 갖고 있는 칩의 개수
 * 리턴값: 없음
*/
void print_game_status(int round, int user_chips, int com_chips);

/**
 * 유저와 컴퓨터가 갖고 있는 칩의 개수가 주어졌을 때 이를 프린트하는 함수
 * 매개변수 user_chips: 유저가 갖고 있는 칩의 개수
 * 매개변수 com_chips: 컴퓨터가 갖고 있는 칩의 개수
 * 리턴값: 없음
*/
void show_chips(int user_chips, int com_chips);

/**
 * 카드 4장을 무작위로 뽑아 각각을 포인터 변수에 저장하는 함수
 * 매개변수 shared_card1: int형의 포인터 변수로 공유 카드 1의 주소를 저장한다. 
 * 매개변수 shared_card2: int형의 포인터 변수로 공유 카드 2의 주소를 저장한다.
 * 매개변수 user_card: int형의 포인터 변수로 유저의 카드의 주소를 저장한다.
 * 매개변수 computer_card: int형의 포인터 변수로 컴퓨터의 카드의 주소를 저장한다.
 * 리턴값: 없음
*/
void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card);

/**
 * 카드 4장을 받아 각각을 프린트하는 함수
 * 매개변수 shared_card1: 공유 카드 1
 * 매개변수 shared_card2: 공유 카드 2
 * 매개변수 user_card: 유저의 카드; -1이면 유저의 카드를 ?로 표시한다. 
 * 매개변수 computer_card: 컴퓨터의 카드
 * 리턴값: 없음
*/
void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card);

/**
 * 정수가 주어졌을 때 특정 범위 (닫힌 구간)에 포함되는지 확인하는 함수
 * 매개변수 a, b: 숫자의 구간을 나타내는 정수 쌍 (닫힌 구간 [a, b])
 * 리턴값: 포함되어 있다면 1, 아니면 0
*/
int is_valid_num(int a, int b, int num);

/**
 * 취할 행동이 정수로 주어질 때 그 행동이 유효한지 확인하는 함수
 * 매개변수 turn: 현재 턴이 몇 번째인지 나타내는 정수
 * 매개변수 action: 취할 행동을 나타내는 정수
 * 리턴값: 유효하다면 1, 아니면 0
*/
int is_valid_bet(int turn, int action);

/**
 * 유저의 행동을 입력받고 그에 따라 적당한 값을 반환하는 함수
 * 매개변수 user_chips: 유저가 갖고 있는 칩의 개수
 * 매개변수 *user_betting_chips: 유저가 지금까지 베팅한 칩의 개수
 * 매개변수 betted_chips: 컴퓨터가 지금까지 베팅한 칩의 개수
 * 매개변수 turn: 현재 턴이 몇 번째인지 나타내는 정수
 * 리턴값: Rold: -1, Call: 0, Raise라면 추가로 베팅한 칩의 개수
*/
int user_turn(int user_chips, int *user_betting_chips, int betted_chips, int turn);

/**
 * 카드와 공유 카드가 주어질 때 그 카드의 조합을 반환하는 함수
 * 매개변수 card: 주어진 카드
 * 매개변수 shared_card1: 공유 카드 1
 * 매개변수 shared_card2: 공유 카드 2
 * 리턴값: No Pair: 1, Double: 2, Straight: 3, Triple: 4
*/
int calc_hand(int card, int shared_card1, int shared_card2);

/**
 * 현재 턴의 상태가 주어질 때 컴퓨터가 Call 하도록 하는 함수 (예외처리를 포함)
 * 매개변수 user_hand: 유저의 카드의 조합 정보 (No Pair: 1, Double: 2, Straight: 3, Triple: 4)
 * 매개변수 com_chips: 컴퓨터가 갖고 있는 칩의 개수
 * 매개변수 *com_betting_chips: 컴퓨터가 지금까지 베팅한 칩의 개수
 * 매개변수 betted_chips: 컴퓨터가 지금까지 베팅한 칩의 개수
 * 매개변수 turn: 현재 턴이 몇 번째인지 나타내는 정수
 * 리턴값: Call: 0 (항상 Call을 하므로 리턴값을 항상 0)
*/
int com_call(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn);

/**
 * 현재 턴의 상태와 Raise할 칩의 개수가 주어질 때 컴퓨터가 Raise 하도록 하는 함수 (예외처리를 포함)
 * 매개변수 user_hand: 유저의 카드의 조합 정보 (No Pair: 1, Double: 2, Straight: 3, Triple: 4)
 * 매개변수 com_chips: 컴퓨터가 갖고 있는 칩의 개수
 * 매개변수 *com_betting_chips: 컴퓨터가 지금까지 베팅한 칩의 개수
 * 매개변수 betted_chips: 컴퓨터가 지금까지 베팅한 칩의 개수
 * 매개변수 turn: 현재 턴이 몇 번째인지 나타내는 정수
 * 매개변수 count: Raise할 칩의 개수
 * 리턴값: 예외 처리로 인한 Call: 0, RAISE라면 추가로 베팅한 칩의 개수
*/
int com_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn, int count);

/**
 * 컴퓨터의 행동을 결정하고 그에 따라 적당한 값을 반환하는 함수
 * 매개변수 user_hand: 유저의 카드의 조합 정보 (No Pair: 1, Double: 2, Straight: 3, Triple: 4)
 * 매개변수 com_chips: 컴퓨터가 갖고 있는 칩의 개수
 * 매개변수 *com_betting_chips: 컴퓨터가 지금까지 베팅한 칩의 개수
 * 매개변수 betted_chips: 컴퓨터가 지금까지 베팅한 칩의 개수
 * 매개변수 turn: 현재 턴이 몇 번째인지 나타내는 정수
 * 리턴값: Fold: -1, Call: 0, Raise라면 추가로 베팅한 칩의 개수
*/
int computer_turn(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn);

/**
 * 승자를 판정하는 함수
 * 매개변수 shared_card1: 공유 카드 1
 * 매개변수 shared_card2: 공유 카드 2
 * 매개변수 user_card: 유저의 카드
 * 매개변수 com_card: 컴퓨터의 카드
 * 리턴값: 유저가 이겼다면 0, 컴퓨터가 이겼다면 1
*/
int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card);

/**
 * 라운드의 승자가 주어질 때 그에 따라 유저와 컴퓨터의 칩 개수를 업데이트 하는 함수
 * 매개변수 winner: 라운드의 승자 (유저: 0, 컴퓨터: 1)
 * 매개변수 user_chips: 사용자가 갖고 있는 칩의 개수를 저장하는 변수의 포인터
 * 매개변수 com_chips: 컴퓨터가 갖고 있는 칩의 개수를 저장하는 변수의 포인터
 * 매개변수 user_betting_chips: 유저가 베팅한 칩의 개수
 * 매개변수 com_betting_chips: 컴퓨터가 베팅한 칩의 개수
 * 리턴값: 없음
*/
void update(int winner, int *user_chips, int *com_chips, int user_betting_chips, int com_betting_chips);

int main(void) {
    srand(time(NULL));

    int prev_winner = COMPUTER; // 이전 턴의 승자를 저장한다. 첫 라운드는 유저의 턴으로 시작하므로 컴퓨터가 승리한 것으로 가정하고 초기화한다. 
    int user_chips = 50, com_chips = 50; // 사용자와 컴퓨터가 각각 갖고 있는 칩의 총 개수를 정수형으로 저장한다. 
    
    int round; // 현재 게임 라운드를 저장하는 변수이다. 모든 게임이 종료된 후 진행한 라운드 수를 출력해야 하므로 반복문 밖에서 선언한다. 
    for (round = 1; round <= 10; round++) {
        clear(); // 게임을 시작하기 전 화면을 지운다. 
        print_game_status(round, user_chips, com_chips); // 현재 게임의 라운드 번호, 유저와 컴퓨터가 각각 갖고 있는 칩의 개수를 프린트한다. 

        int shared_card1, shared_card2, user_card, computer_card; // 공유 카드와 유저의 카드, 컴퓨터의 카드를 저장할 변수를 선언한다. 
        card_shuffle(&shared_card1, &shared_card2, &user_card, &computer_card); // 4장의 카드를 무작위로 뽑아 할당한다. 
        int user_hand = calc_hand(user_card, shared_card1, shared_card2); // 유저의 카드 조합을 계산한다. 뒤에서 값의 변화 없이 반복적으로 이용되므로 미리 계산하고 저장해둔다. 

        print_card_info(shared_card1, shared_card2, -1, computer_card); // 선택된 카드를 프린트한다. 이때, 유저의 카드는 숨겨져야 하므로 -1을 전달한다. 

        int user_betting_chips = 1, com_betting_chips = 1; // 유저와 컴퓨터가 각각 베팅한 칩의 개수를 저장하는 변수를 선언한다. 베팅을 시작할 때 유저와 컴퓨터 모두 칩을 1개 씩 베팅한 상태로 시작하므로, 1로 초기화한다. 
        int turn, action = -100; // 턴의 번호와 유저 혹은 컴퓨터의 동작을 저장하는 변수를 선언한다. 이때, 턴은 반복문 밖에서도 이용되므로 for 반복문 밖에서 선언한다. 
        // 베팅이 진행되지 않는 상황을 고려하여 action를 -100으로 초기화한다. 이 초기값 (-100)은 -1이 아닌 다른 값으로 설정해도 무관하다. 
        if (user_chips > 1 && com_chips > 1) { // 사용자와 컴퓨터가 갖고 있는 칩의 개수가 모두 1보다 클 때만 베팅을 진행한다. 
            // 베팅이 시작되었다느 것을 보여준다. 
            printf("┏━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
            printf("┃        Betting         ┃ \n");
            printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
            printf("\n");

            for (turn = 1;; turn++) { // 매 턴을 돌며 베팅을 시작한다. 
                // 유저와 컴퓨터가 베팅한 칩의 개수를 각각 프린트한다. 
                printf("┏━━━━━━━━━━━━┳━━━━━━━━━━┓ \n");
                printf("┃ User:%3d   ┃ Com:%3d  ┃ \n", user_betting_chips, com_betting_chips);
                printf("┗━━━━━━━━━━━━┻━━━━━━━━━━┛ \n");
                printf("\n");

                // 현재 턴이 유저의 턴인지 컴퓨터의 턴인지 계산한다. 
                // prev_winner == 1 (COMPUTER) 라고 가정할 때, turn이 1에서 시작하므로 유저 (0)의 턴이다. 
                // prev_winner == 0 (USER) 라고 가정할 때, turn이 1에서 시작하므로 첫 턴은 컴퓨터 (1)의 턴이다. 
                switch ((turn + prev_winner) % 2) {
                    case USER: // turn + prev_winner가 2로 나눠 떨어지는 경우
                        // 사용자의 턴을 진행한다. 반환 값 (CALL, FOLD, 혹은 Raise한 칩의 개수)을 action에 저장한다. 
                        action = user_turn(user_chips, &user_betting_chips, com_betting_chips, turn);
                        break;
                    case COMPUTER: // turn + prev_winner가 2로 나눠 떨어지지 않는 경우
                        // 컴퓨터의 턴을 진행한다. 반환 값 (CALL, FOLD, 혹은 Raise한 칩의 개수)을 action에 저장한다. 
                        action = computer_turn(user_hand, com_chips, &com_betting_chips, user_betting_chips, turn);
                        break;
                }
                if (action == CALL || action == FOLD) break; // Call 혹은 Fold를 선택한 경우 베팅을 종료한다.
                printf("\n");
            }

            printf("\n");
            printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
            printf("\n");

            // 베팅이 끝났다는 것을 프린트한다. 
            printf("Betting Finished \n");
            printf("\n");
            print_card_info(shared_card1, shared_card2, user_card, computer_card); // 베팅이 끝났으므로 유저의 카드를 포함한 모든 카드를 공개한다. 
        }

        // 승자를 계산하고, 그에 따라 유저와 컴퓨터의 칩의 개수를 업데이트한다. 
        // action이 FOLD인 경우 방금 턴을 진행한 플레이어가 패배한 것이므로, 승자는 1 - (turn + prev_winner) % 2이다. 
        // action이 FOLD가 아닌 경우, 카드 정보를 이용하여 승자를 판단한다. 
        prev_winner = action == FOLD ? 1 - (turn + prev_winner) % 2 : calc_winner(shared_card1, shared_card2, user_card, computer_card); 

        // 주어진 승자를 이용하여 승자를 프린트한다. 
        printf("┏━━━━━━━━━━━━━━━━━━━━━┓ \n");
        printf("┃ %8s win!       ┃ \n", prev_winner == USER ? "User" : "Computer");
        printf("┗━━━━━━━━━━━━━━━━━━━━━┛ \n");
        printf("\n");

        update(prev_winner, &user_chips, &com_chips, user_betting_chips, com_betting_chips); // 계산된 승자에 따라 칩의 개수를 업데이트한다. 

        int signal; // 게임을 계속 진행할지 여부를 저장하는 변수를 선언한다. 
        printf("Proceed or Not? [Go: 1, End: -1]: ");
        scanf("%d", &signal);
        if (user_chips == 0 || com_chips == 0 || signal == -1) break; // 유저 혹은 컴퓨터의 칩의 개수가 0이거나 유저가 게임 중지를 선택 (signal == -1)했다면 게임을 중지한다. 
    }

    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf("\n");
    printf("Number of Games: %d \n", round > 10 ? round - 1 : round); // 게임 종료까지 진행한 라운드의 수를 프린트한다. 이때, 게임을 끝까지 진행한 경우 round가 11이 된 상태로 종료되므로, round > 10이면 round - 1을 프린트한다. 
    // 즉, (round > 10 ? round - 1 : round)를 프린트한다. 
    printf("\n");

    // 유저와 컴퓨터에게 남은 칩의 개수를 프린트한다. 
    printf("Chips remaining: \n");
    show_chips(user_chips, com_chips);

    printf("\n");
    printf("%s win! \n", user_chips >= com_chips ? "User" : "Computer"); // 칩의 개수가 더 많은 플레이어를 전체 게임의 최종 승자로 판단하고 이를 프린트한다. 이때 칩의 개수가 같다면 유저의 승리로 간주한다. 
}

void print_game_status(int round, int user_chips, int com_chips) {
    // 박스를 그리며 현재 게임의 라운드를 프린트한다. 
    printf("┏━━━━━━━━━━━━━━━━━━━━━┓ \n");
    printf("┃   %2d Game Starts!   ┃ \n", round);
    printf("┗━━━━━━━━━━━━━━━━━━━━━┛ \n");
    printf("\n");

    // 현재 남은 칩의 개수를 프린트한다. 
    printf("Chips remaining: \n");
    show_chips(user_chips, com_chips);
}

void show_chips(int user_chips, int com_chips) {
    // 박스를 그리며 현재 유저와 컴퓨터에게 남은 칩의 개수를 프린트한다. 
    printf("┏━━━━━━━━━━━━━━┳━━━━━━┓ \n");
    printf("┃   User       ┃ %3d  ┃ \n", user_chips);
    printf("┃   Computer   ┃ %3d  ┃ \n", com_chips);
    printf("┗━━━━━━━━━━━━━━┻━━━━━━┛ \n");
    printf("\n");
}

void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card) {
    // 랜덤 함수를 네 번 이용하여 각 변수에 무작위로 카드를 할당한다. 이때, 무작위로 할당되는 카드의 범위는 1 이상 10 이하이다. 
    *shared_card1 = rand() % 10 + 1;
    *shared_card2 = rand() % 10 + 1;
    *user_card = rand() % 10 + 1;
    *computer_card = rand() % 10 + 1;
}

void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card) {
    // 박스를 그리며 유저와 컴퓨터의 카드, 공유 카드의 정보를 프린트한다. 
    printf("┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┓ \n");
    printf("┃  Computer   ┃       Shared Cards        ┃     User    ┃ \n");
    printf("┣━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫ \n");
    printf("┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ \n");
    printf("┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ \n");
    printf("┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ \n");
    if (user_card != -1) // 유저 카드가 -1로 전달되지 않았을 때는 유저 카드의 정보를 프린트한다. 
        printf("┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ \n", computer_card, shared_card1, shared_card2, user_card);
    else // 유저 카드가 -1로 전달되었을 때는 유저 카드를 숨기고 ?로 표시한다. 
        printf("┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃    ?    ┃ ┃ \n", computer_card, shared_card1, shared_card2);
    printf("┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ \n");
    printf("┃ ┃       ♠ ┃ ┃ ┃       ♠ ┃ ┃ ┃       ♠ ┃ ┃ ┃       ♠ ┃ ┃ \n");
    printf("┃ ┗━━━━━━━━━┛ ┃ ┗━━━━━━━━━┛ ┃ ┗━━━━━━━━━┛ ┃ ┗━━━━━━━━━┛ ┃ \n");
    printf("┗━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┛━━━━━━━━━━━━━┛ \n");
    printf("\n");
}

int is_valid_num(int a, int b, int num) {
    return a <= num && num <= b; // AND 연산을 이용하여 num이 a 이상 b 이하인지 판별한다. 
}

int is_valid_bet(int turn, int action) {
    // 취한 행동이 1이상 3이하 (Call, Raise, Fold 중 하나) 인지, 그리고 이와 동시에 
    // 첫 번째 턴에서 취한 행동이 1 (Call)인지 확인한다. 
    return (is_valid_num(1, 3, action)) && (turn == 1 ? action != 1 : 1);
}

int user_turn(int user_chips, int *user_betting_chips, int betted_chips, int turn) {
    int action;
    while (1) {
        printf("USER ┃ [Call: 1 | Raise: 2 | Fold: 3]: ");
        scanf("%d", &action);
        if (is_valid_bet(turn, action)) break;
        printf("USER ┃ [Invalid input] \n");
    }
    
    if (action == 2) {
        int raise;
        printf("USER ┃ [Input number of chips for Raise]: ");
        scanf("%d", &raise);
        *user_betting_chips = betted_chips + raise;
        return raise;
    } else if (action == 1) {
        *user_betting_chips = betted_chips <= user_chips ? betted_chips : user_chips;
        return CALL;
    } else {
        return FOLD;
    }
}

int calc_hand(int card, int shared_card1, int shared_card2) {
    // 주어진 카드의 최솟값, 중간값, 최댓값을 구한다. (Straight를 간단하게 판별하기 위해 ; 1씩 차이남을 이용합니다)
    int max = find_max(card, shared_card1, shared_card2), middle = find_middle(card, shared_card1, shared_card2), min = find_min(card, shared_card1, shared_card2);
    if (max == middle && middle == min) { // 모든 카드가 같다면
        return TRIPLE; // Triple의 조합이므로 TRIPLE을 반환한다. 
    } else if (card == shared_card1 || card == shared_card2) { // 플레이어의 카드와 공유 카드 중 하나가 같다면
        return DOUBLE; // Double의 조합이므로 DOUBLE을 반환한다.
    } else if (max - middle == 1 && middle - min == 1) { // 모든 카드가 1씩 차이난다면
        return STRAIGHT; // Straight의 조합이므로 STRAIGHT을 반환한다.
    } else { // 모든 경우에 해당하지 않는다면
        return NOPAIR; // 조합이 없으므로 NOPAIR을 반환한다. 
    }
}

int com_call(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn) {
    // 컴퓨터가 Call을 할 수 있도록 처리한다. 특히, 예외 처리를 포함하여 처리하는 경우가 반복되기에 함수로 구현한다. 
    if (betted_chips > com_chips) *com_betting_chips = com_chips; // 상대방 (유저)이 이미 컴퓨터가 가진 칩보다 더 많이 베팅한 경우 올인 (지닌 칩을 모두 베팅)한다. 
    else *com_betting_chips = betted_chips; // 이외의 경우 (상대방 (유저)가 베팅한 칩이 컴퓨터가 가진 칩의 개수보다 적은 경우) Call한다. (상대방이 베팅한 칩의 개수와 동일한 수의 칩을 베팅한다. )
    return CALL; // Call을 했다는 신호로 CALL을 반환한다. 
}

// FIXME: Check if the condition of if statement is correct and works well. 
// I bet that it would be correct with a condition of (count + betted_chips > com_chips)
int com_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn, int count) {
    // 컴퓨터가 Raise를 할 수 있도록 처리한다. 특히, 예외 처리를 포함하여 처리하는 경우가 반복되기에 함수로 구현한다. 
    if (count > com_chips) return com_call(user_hand, com_chips, com_betting_chips, betted_chips, turn); // 컴퓨터가 가진 칩보다 더 많은 수의 칩을 Raise하고자 하면 Call한다. 또한 Call을 했다는 신호로 com_call() 함수의 반환값을 그대로 반환한다. 
    else { // 이외의 경우에는 (정상적으로 count만큼 Raise할 수 있는 경우 ; 컴퓨터가 가진 칩의 개수가 (count + betted_chips)보다 크거나 같은 경우)
        *com_betting_chips = betted_chips + count; // Raise에 따라 베팅한 칩의 개수를 betted_chips + count (상대방이 베팅한 칩의 개수보다 count만큼 더 많이)로 설정한다. 
        return count; // Raise를 했으므로 Raise한 칩의 개수를 반환한다. 
    }
}

int computer_turn(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn) {
    int prob = rand() % 100, ret;
    if (user_hand > NOPAIR) {
        if (prob < 70) ret = -1;
        else {
            if (turn != 1) ret = com_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
            else ret = com_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, 1);
        }
    } else {
        if (turn == 1) ret = com_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, 1);
        else if (prob < 50) ret = com_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
        else ret = com_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, rand() % 5 + 1);
    }
    
    if (ret == CALL) printf("COM ┃ Call \n");
    else if (ret == FOLD) printf("COM ┃ Fold \n");
    else printf("COM ┃ Raise, +%d \n", ret);
    return ret;
}

int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card) {
    int user_hand = calc_hand(user_card, shared_card1, shared_card2); // 유저의 카드 조합을 계산한다. 
    int com_hand = calc_hand(computer_card, shared_card1, shared_card2); // 컴퓨터의 카드 조합을 계산한다. 
    // 유저와 컴퓨터 각각의 카드 조합을 계산하여 비교한다. 더 큰 (더 좋은) 카드 조합을 지닌 사람이 승자가 된다. 
    if (user_hand > com_hand) return USER; // 유저의 카드 조합이 컴퓨터의 카드 조합보다 더 좋은 경우, 승자인 USER를 반환한다. 
    else if (user_hand < com_hand) return COMPUTER; //  // 컴퓨터의 카드 조합이 유저의 카드 조합보다 더 좋은 경우, 승자인 COMPUTER를 반환한다. 
    else { // 두 플레이어의 카드 조합이 같다면 숫자가 더 큰 카드를 지닌 사람을 승자로 판단한다. 
        if (user_card < computer_card) return COMPUTER; // 컴퓨터의 카드 숫자가 유저의 카드 숫자보다 크다면 컴퓨터를 승자로 판단하여 COMPUTER를 반환한다. 
        else return USER; // 이외의 경우, 즉 유저의 카드 숫자가 컴퓨터의 카드 숫자보다 크다면 유저를 승자로 판단하여 USER를 반환한다. 
    }
}

void update(int winner, int *user_chips, int *com_chips, int user_betting_chips, int com_betting_chips) {if (winner == USER) { // 유저가 이겼다면
        *user_chips += com_betting_chips; // 컴퓨터가 베팅한 칩의 개수만큼 유저에게 추가한다. 
        *com_chips -= com_betting_chips; // 컴퓨터가 베팅한 칩의 개수만큼 컴퓨터의 칩에서 뺀다.
    } else if (winner == COMPUTER) { // 컴퓨터가 이겼다면
        *user_chips -= user_betting_chips; // 유저가 베팅한 칩의 개수만큼 유저의 칩에서 뺀다.
        *com_chips += user_betting_chips; // 유저가 베팅한 칩의 개수만큼 컴퓨터에게 추가한다.
    }

    // 현재 유저와 컴퓨터에게 각각 남은 칩의 개수를 프린트한다. 
    show_chips(*user_chips, *com_chips);
}
