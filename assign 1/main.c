#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define USER 0
#define COMPUTER 1

#define CALL 0 // 같은 개수 배팅 후 끝냄
#define RAISE 1 // 받고 더 가
#define FOLD -1 // ㅌㅌㅌㅌ

#define NOPAIR 1 // 아무것도 없음
#define DOUBLE 2 // 하나만 같음
#define STRAIGHT 3 // 세 개 일열
#define TRIPLE 4 // 다 똑같음

void clear() {
    printf("\033[H\033[J");
}

int find_max(int a, int b, int c) {
    return a > b ? (a > c ? a : c) : (b > c ? b : c);
}

int find_middle(int a, int b, int c) {
    return a > b ? (a > c ? (b > c ? b : c) : a) : (b > c ? (a > c ? a : c) : b);
}

int find_min(int a, int b, int c) {
    return a > b ? (b > c ? c : b) : (a > c ? c : a);
}

// 2.1 게임 상태 출력
void print_game_status(int round, int user_chips, int com_chips); // print the number of chips each player has
void show_chips(int user_chips, int com_chips);

// 2.2 카드 생성 및 출력
void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card); // generate 4 random cards
void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card); // print the cards

// 3.2 유저의 베팅
int is_valid_num(int a, int b, int num); // check if the number is within the range of [a, b]. return 1 if true, 0 otherwise
int is_valid_bet(int turn, int num);
int user_turn(int user_chips, int *user_betting_chips, int betted_chips, int turn); // get user's choice of betting and return it

// 3.3 컴퓨터의 베팅
int calc_hand(int card, int shard_card1, int shard_card2); // return the hand comparing to the shared cards
int com_do_call(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn);
int com_do_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn, int count);
int computer_turn(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn); // make computer's choice of betting up and return it

// 4.4 게임 진행 여부 입력 및 처리
int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card); // return the winner given the cards assuming that the betting turn have ended

void update(int winner, int *user_chips, int *com_chips, int user_betting_chips, int com_betting_chips);

int main(void) {
    srand(time(NULL));

    int prev_winner = USER;
    int user_chips = 50, com_chips = 50;
    for (int round = 1; round <= 10; round++) {
        print_game_status(round, user_chips, com_chips);

        int shared_card1, shared_card2, user_card, computer_card;
        card_shuffle(&shared_card1, &shared_card2, &user_card, &computer_card);

        int user_betting_chips = 1, com_betting_chips = 1;
        int ret;
        if (user_chips != 1 && com_chips != 1) {
            int turn;
            for (turn = 1;; turn++) { // Betting
                printf("┌────────────────────────┐ \n");
                printf("│        Betting         │ \n");
                printf("└────────────────────────┘ \n");
                printf("\n");


                printf("┌────────────────────────┐ \n");
                printf("│ User: %2d   │ Com: %2d   │ \n", user_betting_chips, com_betting_chips);
                printf("└────────────────────────┘ \n");
                printf("\n");

                if ((turn + prev_winner) % 2 == COMPUTER) // User's turn
                    ret = user_turn(user_chips, &user_betting_chips, com_betting_chips, turn);
                else // Computer's turn
                    ret = computer_turn(calc_hand(user_card, shared_card1, shared_card2), com_chips, &com_betting_chips, user_betting_chips, turn);
                if (ret == CALL || ret == FOLD) break;
            }

            printf("Betting Finished !! \n");
            print_card_info(shared_card1, shared_card2, user_card, computer_card);

            if (ret == FOLD) {
                prev_winner = (turn + prev_winner) % 2 == COMPUTER ? USER : COMPUTER;
                update(prev_winner, &user_chips, &com_chips, user_betting_chips, com_betting_chips);
            }
        }

        int winner = calc_winner(shared_card1, shared_card2, user_card, computer_card);
        update(winner, &user_chips, &com_chips, user_betting_chips, com_betting_chips);

        if (user_chips == 0 || com_chips == 0) break;
        int signal;
        printf("Go [1] or Stop [-1] : ");
        scanf("%d", &signal);
        if (signal == -1) break;
    }

    printf("================================================== \n");
    printf("The game have ended !! \n");
    show_chips(user_chips, com_chips);
    printf("The winner is !!!!!!!!!!!!!!! %s !!!!!!!!! \n", user_chips >= com_chips ? "User" : "Computer");
}

/*
 * Tokens
 * ─
 * │
 * ┌
 * ┐
 * ┘
 * └
 * Line Maps
 * ┌─────┐
 * └─────┘
 */

// Start implementing the functions
void print_game_status(int round, int user_chips, int com_chips) {
    printf("================================================================ \n");
    printf("┌─────────────────────┐ \n");
    printf("│   %d Game Starts!    │ \n", round);
    printf("└─────────────────────┘ \n");
    printf("\n");
    printf("================================================================ \n");

    show_chips(user_chips, com_chips);
}

void show_chips(int user_chips, int com_chips) {
    printf("Chips remaining: \n");
    printf("┌─────────────────────┐ \n");
    printf("│   User       │  %2d  │ \n", user_chips);
    printf("│   Computer   │  %2d  │ \n", com_chips);
    printf("└─────────────────────┘ \n");
    printf("\n");
}

void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card) {
    *shared_card1 = rand() % 40 + 1;
    *shared_card2 = rand() % 40 + 1;
    *user_card = rand() % 40 + 1;
    *computer_card = rand() % 40 + 1;
}

void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card) {
    printf("Showing the card!! ::::: Computer: %2d || Shared: %2d, %2d || User: %2d \n", computer_card, shared_card1, shared_card2, user_card);
    printf("┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┓ \n");
    printf("┃  Computer   ┃       Shared Cards        ┃     User    ┃ \n");
    printf("┣━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫ \n");
    printf("┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ \n");
    printf("┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ \n");
    printf("┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ \n");
    printf("┃ ┃   %2d    ┃ ┃ ┃   %2d    ┃ ┃ ┃   %2d    ┃ ┃ ┃   %2d    ┃ ┃ \n", computer_card, shared_card1, shared_card2, user_card);
    printf("┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ \n");
    printf("┃ ┃       ♠ ┃ ┃ ┃       ♠ ┃ ┃ ┃       ♠ ┃ ┃ ┃       ♠ ┃ ┃ \n");
    printf("┃ ┗━━━━━━━━━┛ ┃ ┗━━━━━━━━━┛ ┃ ┗━━━━━━━━━┛ ┃ ┗━━━━━━━━━┛ ┃ \n");
    printf("┗━━━━━━━━━━━━━┻━━━━━━━━━━━━━┻━━━━━━━━━━━━━┛━━━━━━━━━━━━━┛ \n");
}

int is_valid_num(int a, int b, int num) {
    return a <= num && num <= b;
}

int is_valid_bet(int turn, int num) {
    return (is_valid_num(1, 3, num)) && (turn == 1 ? num != 1 : 1);
}

int user_turn(int user_chips, int *user_betting_chips, int betted_chips, int turn) {
    int action;
    printf("User Input [ Call: 1, Raise: 2, Fold: 3 ] ? ");
    scanf("%d", &action);
    while (!is_valid_bet(turn, action)) {
        printf("Invalid Input \n");
        printf("User Input [ Call: 1, Raise: 2, Fold: 3 ] ? ");
        scanf("%d", &action);
    }
    
    if (action == 2) { // Raise
        int raise;
        printf("Raise? How Many? ");
        scanf("%d", &raise);
        *user_betting_chips = betted_chips + raise;
        return raise;
    } else if (action == 1) { // Call
        *user_betting_chips = betted_chips <= user_chips ? betted_chips : user_chips;
        return CALL;
    } else {
        return FOLD;
    }
}

int calc_hand(int card, int shard_card1, int shard_card2) {
    int max = find_max(card, shard_card1, shard_card2), middle = find_middle(card, shard_card1, shard_card2), min = find_min(card, shard_card1, shard_card2);
    if (max == middle && middle == min) {
        return TRIPLE;
    } else if (max == middle || middle == min) {
        return DOUBLE;
    } else if (max - middle == 1 && middle - min == 1) {
        return STRAIGHT;
    } else {
        return NOPAIR;
    }
}

int com_do_call(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn) {
    if (betted_chips > com_chips) *com_betting_chips = com_chips;
    else *com_betting_chips = betted_chips;
    return CALL;
}

int com_do_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn, int count) {
    if (count > com_chips) return com_do_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
    else {
        *com_betting_chips = betted_chips + count;
        return count;
    }
}

int computer_turn(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn) {
    int prob = rand() % 100, ret;
    if (user_hand == DOUBLE || user_hand == STRAIGHT || user_hand == TRIPLE) {
        if (prob < 70) ret = -1;
        else {
            if (turn != 1) ret = com_do_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
            else ret = com_do_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, 1);
        }
    } else {
        if (prob < 50 && turn > 1) ret = com_do_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
        else ret = com_do_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, rand() % 5 + 1);
    }
    
    if (ret == CALL) printf("COM : CALL \n");
    else if (ret == FOLD) printf("COM : FOLD \n");
    else printf("COM : RAISE %d \n", ret);
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
    printf("Winner: %s \n", winner == USER ? "User" : "Computer");
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
