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

// FIXME: Follow the format of the array by the instructions. 
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
int check_adjacent(int *board_row, int n_people, int x);
void generate_ladder(int **board, int n_people, int height, int n_line);
void free_ladder(int **board, int height);

void save_ladder(char filename[], int **board, int n_people, int height, int n_line);
int** load_ladder(char *filename, int *n_people, int *height, int *n_line);

int main(void) {
    srand(time(NULL));

    int **ladder_board = NULL;
    int n_people, height, n_line;
    char filename[25];

    int flag = 1;
    while (flag) {
        printf("[사다리 게임] \n");
        printf("======================================= \n");
        printf("1. 사다리 보드 생성 \n");
        printf("2. 사다리 타기 시작 \n");
        printf("3. 종료 \n");
        printf("======================================= \n");
        printf("선택: ");

        int menu;
        scanf("%d", &menu);

        switch(menu) {
            case 1: 
                printf("참여 인원수: "); scanf("%d", &n_people);
                printf("사다리 높이: "); scanf("%d", &height);
                printf("가로줄 개수: "); scanf("%d", &n_line);
                printf("파일이름: "); scanf("%s", filename);

                ladder_board = allocate_ladder(n_people, height);
                generate_ladder(ladder_board, n_people, height, n_line);
                save_ladder(filename, ladder_board, n_people, height, n_line);
                free_ladder(ladder_board, height);
            case 2:
                printf("파일이름: "); scanf("%s", filename);
                
                ladder_board = load_ladder(filename, &n_people, &height, &n_line);
                break;
            case 3:
                flag = 0;
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
    int **board = (int**)calloc(height, sizeof(int*)); // TODO: Use NULL end of array
    for (int i = 0; i < height; i++) board[i] = (int*) calloc(n_people - 1, sizeof(int));
    return board;
}

int check_adjacent(int *board_row, int n_people, int x) {
    if (x == 0) return board_row[x + 1];
    else if (x == n_people - 2) return board_row[x - 1];
    else return board_row[x - 1] || board_row[x + 1];
}

void generate_ladder(int **board, int n_people, int height, int n_line) {
    while (n_line--) {
        int x = rand() % (n_people - 1);
        int y = 1 + rand() % (height - 2);
        if (board[y][x] == 1 || check_adjacent(board[y], n_people, x)) n_line++;
        else board[y][x] = 1;
    }
}

void free_ladder(int **board, int height) {
    for (int i = 0; i < height; i++) free(board[i]);
    free(board);
}

void save_ladder(char filename[], int **board, int n_people, int height, int n_line) {
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d %d %d\n", n_people, height, n_line);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < n_people - 1; j++) {
            if (board[i][j]) fprintf(fp, "%d %d\n", i, j);
        }
    }
    fclose(fp);
}

int** load_ladder(char *filename, int *n_people, int *height, int *n_line) {
    FILE *fp = fopen(filename, "r");
    fscanf(fp, "%d %d %d", n_people, height, n_line);

    int **board = allocate_ladder(*n_people, *height);
    for (int i = 0; i < *n_line; i++) {
        int x, y;
        fscanf(fp, "%d %d", &y, &x);
        board[y][x] = 1;
    }
}
