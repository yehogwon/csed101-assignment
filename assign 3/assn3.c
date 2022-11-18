/**
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022.11.
 * OS: macOS 13.0
 * IDE Environment: Visual Studio Code 1.73.1
 * GCC version: gcc 14.0.0
 * C standard: C99
 * Encoding: UTF-8
 * End of Line Sequence: LF
 * Naming Convention: snake_case
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 91
#define GREEN 92
#define YELLOW 93
#define BLUE 94
#define VIOLET 95

// Print Utils
void set_color(int code);
void reset_color();
void clear();

int** allocate_ladder(int n_people, int height);
void generate_ladder(int **board, int height, int n_line);
void free_ladder(int **board, int height);

void save_ladder(char filename[], int **board);
int** load_ladder(char *filename);

int main(void) {
    int **ladder_board = NULL;
    int n_people, height, n_line;
    char filename[25];

    while (1) {
        printf("[사다리 게임] \n");
        printf("======================================= \n");
        printf("1. 사다리 보드 생성 \n");
        printf("2. 사다리 타기 시작 \n");
        printf("3. 종료 \n");
        printf("======================================= \n");
        printf("선택: \n");

        int menu;
        scanf("%d", &menu);

        switch(menu) {
            case 1: 
                printf("참여 인원수: "); scanf("%d", &n_people);
                printf("사다리 높이: "); scanf("%d", &height);
                printf("가로줄 개수: "); scanf("%d", &n_line);
                printf("파일이름: "); scanf("%s", filename);

                ladder_board = allocate_ladder(n_people, height);
                generate_ladder(ladder_board, height, n_line);
                save_ladder(filename, ladder_board);
                free_ladder(ladder_board, height);
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Uncaught Exception! \n");
                break;
        }
    }

    return 0;
}

void set_color(int code) {
    printf("\033[%dm", code);
}

void reset_color() {
    printf("\033[0m");
}

void clear() {
    system("clear");
}

int** allocate_ladder(int n_people, int height) {
    int **board = (int**)calloc(height + 1, sizeof(int*));
    for (int i = 0; i < height; i++) board[i] = (int*) calloc(n_people - 1, sizeof(int));
    board[height] = NULL;
    return board;
}

// TODO: generate_ladder()
void generate_ladder(int **board, int height, int n_line) {

}

void free_ladder(int **board, int height) {
    int **ptr = board;
    while (*ptr != NULL) {
        free(*ptr);
        ptr++;
    }
    free(board);
}
