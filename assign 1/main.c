/**
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022-10-31
 * OS: macOS 12.6, 
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
 * 3개의 숫자가 주어질 때 최댓값을 반환하는 함수
 * 매개변수 a, b, c: 최댓값을 구할 숫자 3개
 * 리턴값: a, b, c 중 최댓값
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

    int prev_winner = COMPUTER;
    int user_chips = 50, com_chips = 50;
    
    int round;
    for (round = 1; round <= 10; round++) {
        clear();
        print_game_status(round, user_chips, com_chips);

        int shared_card1, shared_card2, user_card, computer_card;
        card_shuffle(&shared_card1, &shared_card2, &user_card, &computer_card);
        int user_hand = calc_hand(user_card, shared_card1, shared_card2);

        print_card_info(shared_card1, shared_card2, -1, computer_card);

        int user_betting_chips = 1, com_betting_chips = 1;
        int turn, ret = -100;
        if (user_chips != 1 && com_chips != 1) {
            printf("┏━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
            printf("┃        Betting         ┃ \n");
            printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
            printf("\n");
            for (turn = 1;; turn++) {
                printf("┏━━━━━━━━━━━━┳━━━━━━━━━━┓ \n");
                printf("┃ User:%3d   ┃ Com:%3d  ┃ \n", user_betting_chips, com_betting_chips);
                printf("┗━━━━━━━━━━━━┻━━━━━━━━━━┛ \n");
                printf("\n");

                switch ((turn + prev_winner) % 2) {
                    case USER: 
                        ret = user_turn(user_chips, &user_betting_chips, com_betting_chips, turn);
                        break;
                    case COMPUTER:
                        ret = computer_turn(user_hand, com_chips, &com_betting_chips, user_betting_chips, turn);
                        break;
                }
                if (ret == CALL || ret == FOLD) break;
                printf("\n");
            }

            printf("\n");
            printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
            printf("\n");

            printf("Betting Finished \n");
            printf("\n");
            print_card_info(shared_card1, shared_card2, user_card, computer_card);
        }

        prev_winner = ret == FOLD ? 1 - (turn + prev_winner) % 2 : calc_winner(shared_card1, shared_card2, user_card, computer_card);
        update(prev_winner, &user_chips, &com_chips, user_betting_chips, com_betting_chips);

        int signal;
        printf("Proceed or Not? [Go: 1, End: -1]: ");
        scanf("%d", &signal);
        if (user_chips == 0 || com_chips == 0 || signal == -1) break;
    }

    printf("\n");
    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf("\n");
    printf("Number of Games: %d \n", round > 10 ? round - 1 : round);
    printf("\n");

    printf("Chips remaining: \n");
    show_chips(user_chips, com_chips);

    printf("\n");
    printf("%s win! \n", user_chips >= com_chips ? "User" : "Computer");
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
    int max = find_max(card, shared_card1, shared_card2), middle = find_middle(card, shared_card1, shared_card2), min = find_min(card, shared_card1, shared_card2);
    if (max == middle && middle == min) {
        return TRIPLE;
    } else if (card == shared_card1 || card == shared_card2) {
        return DOUBLE;
    } else if (max - middle == 1 && middle - min == 1) {
        return STRAIGHT;
    } else {
        return NOPAIR;
    }
}

int com_call(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn) {
    if (betted_chips > com_chips) *com_betting_chips = com_chips;
    else *com_betting_chips = betted_chips;
    return CALL;
}

int com_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn, int count) {
    if (count > com_chips) return com_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
    else {
        *com_betting_chips = betted_chips + count;
        return count;
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
        if (prob < 50 && turn > 1) ret = com_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
        else ret = com_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, rand() % 5 + 1);
    }
    
    if (ret == CALL) printf("COM ┃ Call \n");
    else if (ret == FOLD) printf("COM ┃ Fold \n");
    else printf("COM ┃ Raise, +%d \n", ret);
    return ret;
}

int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card) {
    int user_hand = calc_hand(user_card, shared_card1, shared_card2);
    int com_hand = calc_hand(computer_card, shared_card1, shared_card2);
    if (user_hand > com_hand) return USER;
    else if (user_hand < com_hand) return COMPUTER;
    else {
        if (user_card < computer_card) return COMPUTER;
        else return USER;
    }
}

void update(int winner, int *user_chips, int *com_chips, int user_betting_chips, int com_betting_chips) {
    printf("┏━━━━━━━━━━━━━━━━━━━━━┓ \n");
    printf("┃ %8s win!       ┃ \n", winner == USER ? "User" : "Computer");
    printf("┗━━━━━━━━━━━━━━━━━━━━━┛ \n");
    printf("\n");

    if (winner == USER) {
        *user_chips += com_betting_chips;
        *com_chips -= com_betting_chips;
    } else if (winner == COMPUTER) {
        *user_chips -= user_betting_chips;
        *com_chips += user_betting_chips;
    }

    show_chips(*user_chips, *com_chips);
}
