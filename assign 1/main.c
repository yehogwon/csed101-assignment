#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define CALL 1 // 같은 개수 배팅 후 끝냄
#define RAISE 2 // 받고 더 가
#define FOLD 3 // ㅌㅌㅌㅌ

#define NOPAIR 1 // 아무것도 없음
#define DOUBLE 2 // 하나만 같음
#define STRAIGHT 3 // 세 개 일열
#define TRIPLE 4 // 다 똑같음

// FIXME: update clear() function
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

// 2.2 카드 생성 및 출력
void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card); // generate 4 random cards
// TODO: Refer to the assn1.pdf
void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card); // print the cards

// 3.2 유저의 베팅
int is_valid_num(int a, int b, int num); // check if the number is within the range of [a, b]. return 1 if true, 0 otherwise
int is_valid_bet(int turn, int num);
int user_turn(int user_chips, int *user_betting_chips, int betted_chips, int turn); // get user's choice of betting and return it

// 3.3 컴퓨터의 베팅
int calc_hand(int card, int shard_card1, int shard_card2); // return the hand comparing to the shared cards
int com_do_call(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn);
int com_do_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn);
int computer_turn(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn); // make computer's choice of betting up and return it

// 4.4 게임 진행 여부 입력 및 처리
// FIXME: choose a proper return type
void calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card); // return the winner given the cards assuming that the betting turn have ended

int main(void) {
    srand(time(NULL));
    printf("┌────────────────────────┐ \n");
    printf("│        Betting         │ \n");
    printf("└────────────────────────┘ \n");
    printf("\n");
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
    printf("┌─────────────────────┐ \n");
    printf("│   %d Game Starts!   │ \n", round);
    printf("└─────────────────────┘ \n");
    printf("\n");

    printf("Chips remaining: \n");
    printf("┌─────────────────────┐ \n");
    printf("│  User       │  %2d  │ \n", user_chips);
    printf("│  Computer   │  %2d  │ \n", com_chips);
    printf("└─────────────────────┘ \n");
    printf("\n");
}

// NOTE: consider the wegiht of each probability of choosing each number
void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card) {
    *shared_card1 = rand() % 40 + 1;
    *shared_card2 = rand() % 40 + 1;
    *user_card = rand() % 40 + 1;
    *computer_card = rand() % 40 + 1;
}

// TODO: Draw detailed box
void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card) {
    printf("Computer: %2d || Shared: %2d, %2d || User: %2d \n", computer_card, shared_card1, shared_card2, user_card);
}

int is_valid_num(int a, int b, int num) {
    return a <= num && num <= b;
}

int is_valid_bet(int turn, int num) {
    return (is_valid_num(1, 3, num)) && (turn == 1 ? num != CALL : 1);
}

int user_turn(int user_chips, int *user_betting_chips, int betted_chips, int turn) {
    printf("┌────────────────────────┐ \n");
    printf("│ User: %2d  │  Com: %2d │ \n");
    printf("└────────────────────────┘ \n");
    printf("\n");

    int input;
    printf("User Input? ");
    scanf("%d", input);
    while (!is_valid_num(1, 3, input)) {
        printf("Invalid Input \n");
        printf("User Input? ");
        scanf("%d", input);
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

}

int com_do_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn) {

}

int computer_turn(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn) {
    int prob = rand() % 100;
    if (user_hand == DOUBLE || user_hand == STRAIGHT || user_hand == TRIPLE) {
        if (prob < 70); // Do Fold
        else; // Do Call
    } else {
        if (prob < 50 && turn > 1); // Do Call
        else; // Do Raise, and set randomly within [0, 5]
    }
}
