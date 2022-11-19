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

// Print Utils
void set_color(int code);
void reset_color();
void print_color(char *str, int code);
void clear();
void flush();

int** allocate_ladder(int n_people, int height);
int check_adjacent(int *board_row, int n_people, int x);
void generate_ladder(int **board, int n_people, int height, int n_line);
void free_ladder(int **board, int height);

void save_ladder(char *filename, int **board, int n_people, int height, int n_line);
int** load_ladder(char *filename, int *n_people, int *height, int *n_line);

void show_ladder(int **board, int n_people, int height);
int navigate(int **board, int n_people, int height, int start, int print);
void iterate_navigate(int **board, int n_people, int height);

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

        int menu, start;
        scanf("%d", &menu);
        printf("\n");

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
                break;
            case 2:
                printf("파일이름: "); scanf("%s", filename);
                
                ladder_board = load_ladder(filename, &n_people, &height, &n_line);
                if (ladder_board) {
                    iterate_navigate(ladder_board, n_people, height);
                    free_ladder(ladder_board, height);
                } else printf("파일이 존재하지 않습니다. ");
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

void print_color(char *str, int code) {
    int color = code < 0 ? 90 - (code) % 5 : 0;
    if (color == 90) color = 95;
    set_color(color);
    printf("%s", str);
    reset_color();
}

void clear() {
    system("clear");
}

void flush() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int** allocate_ladder(int n_people, int height) {
    int **board = (int**)calloc(height, sizeof(int*)); // TODO: Use NULL end of array
    for (int i = 0; i < height; i++) board[i] = (int*) calloc(n_people * 2 - 1, sizeof(int));
    return board;
}

int check_adjacent(int *board_row, int n_people, int x) {
    if (n_people == 2) return 0;
    else return (x - 2 >= 0 && board_row[x - 2]) || (x + 2 <= (n_people - 1) * 2 && board_row[x + 2]);
}

void generate_ladder(int **board, int n_people, int height, int n_line) {
    for (int i = 0; i < height; i++) for (int j = 0; j < n_people * 2; j += 2) board[i][j] = 1;

    while (n_line--) {
        int x = (rand() % (n_people - 1)) * 2 + 1;
        int y = 1 + rand() % (height - 2);
        if (board[y][x] || check_adjacent(board[y], n_people, x)) n_line++;
        else board[y][x] = 1;
    }
}

void free_ladder(int **board, int height) {
    for (int i = 0; i < height; i++) free(board[i]);
    free(board);
}

void save_ladder(char *filename, int **board, int n_people, int height, int n_line) {
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d %d %d\n", n_people, height, n_line);
    for (int i = 0; i < height; i++) {
        for (int j = 1; j < n_people * 2; j += 2) {
            if (board[i][j]) fprintf(fp, "%d %d\n", i, (j - 1) / 2);
        }
    }
    fclose(fp);
}

int** load_ladder(char *filename, int *n_people, int *height, int *n_line) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return NULL;
    }
    
    fscanf(fp, "%d %d %d", n_people, height, n_line);

    int **board = allocate_ladder(*n_people, *height);
    for (int i = 0; i < *height; i++) for (int j = 0; j < *n_people * 2; j += 2) board[i][j] = 1;
    for (int i = 0; i < *n_line; i++) {
        int x, y;
        fscanf(fp, "%d %d", &y, &x);
        board[y][x * 2 + 1] = 1;
    }
    
    fclose(fp);
    return board;
}

void show_ladder(int **board, int n_people, int height) {
    for (int i = 0; i < n_people; i++) printf("%3c ", 'A' + i);
    printf("\n");

    for (int i = 0; i < height; i++) {
        printf("  ");
        for (int j = 0; j < n_people * 2 - 1; j++) {
            if (j % 2 == 0) print_color("+", board[i][j]);
            else if (board[i][j] != 0) print_color("---", board[i][j]);
            else print_color("   ", board[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n_people; i++) printf("%3d ", i + 1);
    printf("\n");
}

int navigate(int **board, int n_people, int height, int start, int print) {
    int mark = -start, x = (start - 1) * 2, y = height - 1;
    int vel = 0, prev_x = x, prev_y = y;
    
    while (y >= 0) {
        prev_x = x, prev_y = y;
        board[y][x] = mark;

        if (x % 2 != 0) {
            x += vel;
        } else {
            if (vel != 0) {
                y--;
                vel = 0;
            }
            else {
                if (x > 0 && board[y][x - 1]) x += (vel = -1);
                else if (x + 1 < n_people * 2 - 1 && board[y][x + 1]) x += (vel = 1);
                else y--;
            }
        }
        
        if (print) {
            clear();
            printf("%d %d \n", prev_y, prev_x);
            show_ladder(board, n_people, height);
            if (prev_y) getchar();
        }
    }

    return x / 2 + 1;
}

void iterate_navigate(int **board, int n_people, int height) {
    clear();
    show_ladder(board, n_people, height);
    
    int flag = 1, start;
    int *dest = (int*)calloc(n_people, sizeof(int));
    while (flag) {
        printf(">> "); scanf("%d", &start);
        flush();
        switch (start) {
            case 0: 
                flag = 0;
                break;
            case -1: 
                clear();
                for (int i = 0; i < n_people; i++) dest[i] = navigate(board, n_people, height, i + 1, 0);
                show_ladder(board, n_people, height);
                printf("\n");
                for (int i = 0; i < n_people; i++) printf("%d -> %c \n", i + 1, 'A' + dest[i] - 1);
                printf("\n");
                break;
            default: 
                dest[start - 1] = navigate(board, n_people, height, start, 1);
                printf("\n");
                printf("result: %d -> %c \n", start, 'A' + dest[start - 1] - 1);
                printf("\n");
                break;
        }
    }
    free(dest);
}
