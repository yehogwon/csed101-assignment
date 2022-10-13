// TODO: update newlines

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define PLAIN "\033[0;37m"
#define RED "\033[1;31m"

#define USER 0
#define COMPUTER 1

#define CALL 0
#define RAISE 1
#define FOLD -1

#define NOPAIR 1
#define DOUBLE 2
#define STRAIGHT 3
#define TRIPLE 4

void clear() {
    system("clear");
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

void print_game_status(int round, int user_chips, int com_chips);
void show_chips(int user_chips, int com_chips);

void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card);
void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card);

int is_valid_num(int a, int b, int num);
int is_valid_bet(int turn, int num);
int user_turn(int user_chips, int *user_betting_chips, int betted_chips, int turn);

int calc_hand(int card, int shard_card1, int shard_card2);
int com_do_call(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn);
int com_do_raise(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn, int count);
int computer_turn(int user_hand, int com_chips, int *com_betting_chips, int betted_chips, int turn);

int calc_winner(int shared_card1, int shared_card2, int user_card, int computer_card);

void update(int winner, int *user_chips, int *com_chips, int user_betting_chips, int com_betting_chips);

int main(void) {
    srand(time(NULL));

    int prev_winner = USER;
    int user_chips = 50, com_chips = 50;
    
    int round;
    for (round = 1; round <= 10; round++) {
        clear();
        print_game_status(round, user_chips, com_chips);

        int shared_card1, shared_card2, user_card, computer_card;
        card_shuffle(&shared_card1, &shared_card2, &user_card, &computer_card);

        print_card_info(shared_card1, shared_card2, -1, computer_card);

        int user_betting_chips = 1, com_betting_chips = 1;
        int turn, ret = -100;
        if (user_chips != 1 && com_chips != 1) {
            for (turn = 1;; turn++) {
                printf("┏━━━━━━━━━━━━━━━━━━━━━━━━┓ \n");
                printf("┃        Betting         ┃ \n");
                printf("┗━━━━━━━━━━━━━━━━━━━━━━━━┛ \n");
                printf("\n");


                printf("┏━━━━━━━━━━━━┳━━━━━━━━━━┓ \n");
                printf("┃ User:%3d   ┃ Com:%3d  ┃ \n", user_betting_chips, com_betting_chips);
                printf("┗━━━━━━━━━━━━┻━━━━━━━━━━┛ \n");
                printf("\n");

                // FIXME: Check if turning algorithm works well
                if ((turn + prev_winner) % 2 != USER)
                    ret = user_turn(user_chips, &user_betting_chips, com_betting_chips, turn);
                else
                    ret = computer_turn(calc_hand(user_card, shared_card1, shared_card2), com_chips, &com_betting_chips, user_betting_chips, turn);
                if (ret == CALL || ret == FOLD) break;
            }

            printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
            printf("Betting Finished \n");
            print_card_info(shared_card1, shared_card2, user_card, computer_card);
        }

        // FIXME: Check if winner checking algorithm works well
        prev_winner = ret == FOLD ? 1 - (turn + prev_winner) % 2 : calc_winner(shared_card1, shared_card2, user_card, computer_card);
        update(prev_winner, &user_chips, &com_chips, user_betting_chips, com_betting_chips);

        int signal;
        printf("Proceed or Not? [Go: 1, End: -1]: ");
        scanf("%d", &signal);
        if (user_chips == 0 || com_chips == 0 || signal == -1) break;
    }

    printf("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ \n");
    printf("Number of Games: %d \n", round);
    show_chips(user_chips, com_chips);
    printf("%s win! \n", user_chips >= com_chips ? "User" : "Computer");
}

void print_game_status(int round, int user_chips, int com_chips) {
    printf("┏━━━━━━━━━━━━━━━━━━━━━┓ \n");
    printf("┃   %2d Game Starts!   ┃ \n", round);
    printf("┗━━━━━━━━━━━━━━━━━━━━━┛ \n");
    printf("\n");

    show_chips(user_chips, com_chips);
}

void show_chips(int user_chips, int com_chips) {
    printf("Chips remaining: \n");
    printf("┏━━━━━━━━━━━━━━┳━━━━━━┓ \n");
    printf("┃   User       ┃ %3d  ┃ \n", user_chips);
    printf("┃   Computer   ┃ %3d  ┃ \n", com_chips);
    printf("┗━━━━━━━━━━━━━━┻━━━━━━┛ \n");
    printf("\n");
}

void card_shuffle(int *shared_card1, int *shared_card2, int *user_card, int *computer_card) {
    *shared_card1 = rand() % 10 + 1;
    *shared_card2 = rand() % 10 + 1;
    *user_card = rand() % 10 + 1;
    *computer_card = rand() % 10 + 1;
}

void print_card_info(int shared_card1, int shared_card2, int user_card, int computer_card) {
    printf("┏━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━┓ \n");
    printf("┃  Computer   ┃       Shared Cards        ┃     User    ┃ \n");
    printf("┣━━━━━━━━━━━━━╋━━━━━━━━━━━━━┳━━━━━━━━━━━━━╋━━━━━━━━━━━━━┫ \n");
    printf("┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ ┏━━━━━━━━━┓ ┃ \n");
    printf("┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ ┃ ♠       ┃ ┃ \n");
    printf("┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ ┃         ┃ ┃ \n");
    if (user_card != -1)
        printf("┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ \n", computer_card, shared_card1, shared_card2, user_card);
    else
        printf("┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃  %3d    ┃ ┃ ┃    ?    ┃ ┃ \n", computer_card, shared_card1, shared_card2);
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
    if (user_hand > NOPAIR) {
        if (prob < 70) ret = -1;
        else {
            if (turn != 1) ret = com_do_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
            else ret = com_do_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, 1);
        }
    } else {
        if (prob < 50 && turn > 1) ret = com_do_call(user_hand, com_chips, com_betting_chips, betted_chips, turn);
        else ret = com_do_raise(user_hand, com_chips, com_betting_chips, betted_chips, turn, rand() % 5 + 1);
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
