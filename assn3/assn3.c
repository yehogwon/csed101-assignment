/**
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022.11.24
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

/**
 * printf의 색을 설정하는 함수
 * 매개변수 color: 색상 코드 (printf format)
 * 리턴값: 없음
*/
void set_color(int color);

/**
 * printf의 색을 초기화하는 함수
 * 매개변수: 없음
 * 리턴값: 없음
*/
void reset_color();

/**
 * 주어진 색상 코드에 따라 적절하게 주어진 문자열을 출력하는 함수
 * 매개변수 str: 출력할 문자열
 * 매개변수 code: 출력할 색상 코드 (함수에서 디코딩 됨)
 * 리턴값: 없음
*/
void print_color(char *str, int code);

/**
 * 화면을 지우는 함수
 * 매개변수: 없음
 * 리턴값: 없음
*/
void clear();

/**
 * scanf의 stdin 버퍼를 지우는 함수
 * 매개변수: 없음
 * 리턴값: 없음
*/
void flush();

/**
 * 사다리 정보를 저장할 변수의 공간을 할당하는 함수
 * 매개변수 n_people: 사다리 타기에 참여한 사람 수
 * 매개변수 height: 사다리의 높이
 * 리턴값: 할당된 공간을 가리키는 이중포인터 (2차원 배열)
*/
int** allocate_ladder(int n_people, int height);

/**
 * 사다리의 한 행이 주어질 때 이웃하는 위치에 가로 선이 존재하는지 확인하는 함수
 * 매개변수 board_row: 사다리의 한 행
 * 매개변수 n_line: 사다리의 가로 선 개수
 * 매개변수 x: 이웃 여부를 확인할 x좌표
 * 리턴값: 이웃한다 (1 ; true), 이웃하지 않는다 (0 ; false)
*/
int check_adjacent(int *board_row, int n_people, int x);

/**
 * 주어진 공간에 주어진 정보의 임의의 사다리를 만들고 저장하는 함수
 * 매개변수 board: 사다리 정보를 저장할 변수 (2차원 배열)
 * 매개변수 n_people: 사다리 타기에 참여한 사람 수
 * 매개변수 height: 사다리의 높이
 * 매개변수 n_line: 사다리의 가로 선 개수
 * 리턴값: 없음
*/
void generate_ladder(int **board, int n_people, int height, int n_line);

/**
 * 사다리를 저장하기 위해 할당된 공간을 해제하는 함수
 * 매개변수 board: 사다리 정보가 저장된 공간 (2차원 배열)
 * 매개변수 height: 사다리의 높이
 * 리턴값: 없음
*/
void free_ladder(int **board, int height);

/**
 * 사다리 정보를 파일에 저장하는 함수
 * 매개변수 filename: 저장할 파일 이름
 * 매개변수 board: 사다리 정보가 저장된 변수 (2차원 배열)
 * 매개변수 n_people: 사다리 타기에 참여한 사람 수
 * 매개변수 height: 사다리의 높이
 * 매개변수 n_line: 사다리의 가로 선 개수
 * 리턴값: 없음
*/
void save_ladder(char *filename, int **board, int n_people, int height, int n_line);

/**
 * 파일에서 사다리 정보를 읽어 저장하는 함수
 * 매개변수 filename: 읽어올 파일 이름
 * 매개변수 n_people: 사다리 타기에 참여한 사람 수를 저장할 변수
 * 매개변수 height: 사다리의 높이를 저장할 변수
 * 매개변수 n_line: 사다리의 가로 선 개수를 저장할 변수
 * 리턴값: 사다리 정보를 저장할 2차원 배열 공간
*/
int** load_ladder(char *filename, int *n_people, int *height, int *n_line);

/**
 * 사다리를 출력하는 함수 (0 또는 1이 아니라면 적당한 색으로 출력)
 * 매개변수 board: 사다리 정보가 저장된 변수 (2차원 배열)
 * 매개변수 n_people: 사다리 타기에 참여한 사람 수
 * 매개변수 height: 사다리의 높이
 * 리턴값: 없음
*/
void show_ladder(int **board, int n_people, int height);

/**
 * 주어진 시작점부터 사다리를 타고 올라가는 함수
 * 매개변수 board: 사다리 정보가 저장된 변수 (2차원 배열)
 * 매개변수 n_people: 사다리 타기에 참여한 사람 수
 * 매개변수 height: 사다리의 높이
 * 매개변수 start: 사다리를 타기 시작할 위치 (1 ~ n_people)
 * 매개변수 wait: 사다리를 타는 과정 사이에 사용자의 Enter Key 입력을 기다릴지 여부
 * 리턴값: 사다리의 목적지 (1 ~ n_people)
*/
int navigate(int **board, int n_people, int height, int start, int wait);

/**
 * 사용자와 상호작용하며 반복적으로 사다리 타기를 진행하는 함수
 * 매개변수 board: 사다리 정보가 저장된 변수 (2차원 배열)
 * 매개변수 n_people: 사다리 타기에 참여한 사람 수
 * 매개변수 height: 사다리의 높이
 * 리턴값: 없음
*/
void iterate_navigate(int **board, int n_people, int height);

int main(void) {
    srand(time(NULL)); // 난수 생성을 위한 시드를 현재 시간으로 설정한다. 

    int **ladder_board = NULL; // 사다리 정보를 저장할 2차원 배열을 선언한다. 
    int n_people, height, n_line; // 사다리 타기에 참여한 사람 수, 사다리의 높이, 사다리의 가로 선 개수를 저장할 변수를 선언한다.
    char filename[25]; // 사다리의 정보를 저장하거나 불러올 파일 이름을 저장할 변수를 선언한다. 최대 길이가 20이므로 넉넉하게 25로 설정한다. 

    int flag = 1; // 반복을 제어할 flag를 선언하고, 처음에는 반복하므로 1로 초기화한다. 
    while (flag) {
        // 사용자가 선택할 수 있는 메뉴를 출력한다. 
        printf("\n");
        printf("[사다리 게임] \n");
        printf("======================================= \n");
        printf("1. 사다리 보드 생성 \n");
        printf("2. 사다리 타기 시작 \n");
        printf("3. 종료 \n");
        printf("======================================= \n");
        printf("선택: ");

        // 사용자의 메뉴 선택을 받는다. 
        int menu, start;
        scanf("%d", &menu);
        printf("\n");
        
        switch(menu) {
            case 1: // 사용자가 < 1. 사다리 보드 생성 >을 선택한 경우
                // 사용자에게 사다리 타기에 참여할 사람 수, 사다리의 높이, 가로줄의 개수, 저장할 파일 이름을 입력받는다. 
                printf("참여 인원수: "); scanf("%d", &n_people);
                printf("사다리 높이: "); scanf("%d", &height);
                printf("가로줄 개수: "); scanf("%d", &n_line);
                printf("파일이름: "); scanf("%s", filename);

                ladder_board = allocate_ladder(n_people, height); // 사다리를 저장할 메모리 공간을 동적할당한다. 
                generate_ladder(ladder_board, n_people, height, n_line); // 사다리를 무작위로 생성한다. 
                save_ladder(filename, ladder_board, n_people, height, n_line); // 파일에 사다리 정보를 저장한다. 
                free_ladder(ladder_board, height); // 사다리를 저장하기 위해 동적할당한 메모리 공간을 해제한다. 
                break;
            case 2: // 사용자가 < 2. 사다리 타기 시작 >을 선택한 경우
                printf("파일이름: "); scanf("%s", filename); // 사다리를 불러올 파일 이름을 입력받는다. 
                
                ladder_board = load_ladder(filename, &n_people, &height, &n_line); // 파일에서 사다리 정보를 불러온다. 
                if (ladder_board) { // 사다리 정보를 불러오는데 성공한 경우
                    iterate_navigate(ladder_board, n_people, height); // 사용자와 상호작용하며 사다리 타기를 진행한다. 
                    free_ladder(ladder_board, height); // 사다리를 저장하기 위해 동적할당한 메모리 공간을 해제한다. 
                } else printf("파일이 존재하지 않습니다. \n"); // 사다리 정보를 불러오는데 실패한 경우 (파일이 존재하지 않는 경우)
                break;
            case 3: // 사용자가 < 3. 종료 >를 선택한 경우
                flag = 0; // 반복을 종료하기 위해 flag를 0으로 설정한다. 
                break;
        }
    }

    return 0;
}

void set_color(int color) {
    printf("\033[%dm", color); // 주어진 색으로 printf 색상 변경
}

void reset_color() {
    printf("\033[0m"); // printf 출력 색상 초기화
}

void print_color(char *str, int code) {
    // 코드가 음수라면 플레이어의 색을, 아니라면 기본 색을 의미한다. 
    int color = code < 0 ? 90 - (code) % 5 : 0; // 위 logic에 따라 색을 디코딩한다. 
    if (color == 90) color = 95; // 색이 90으로 디코드되었을 때는 violet을 의미하는 예외이므로 95로 바꿔준다. 
    set_color(color); // 디코딩한 색으로 printf 색을 변경한다.
    printf("%s", str); // 문자열을 출력한다. 
    reset_color(); // printf 색을 초기화한다. 
}

void clear() {
    system("clear"); // 화면을 모두 지운다. (macOS에서 build 및 실행하여 clear를 사용했습니다. )
}

void flush() {
    char c; // 입력 버퍼를 임시 저장할 변수
    while ((c = getchar()) != '\n' && c != EOF); // 입력 버퍼를 비운다.
}

int** allocate_ladder(int n_people, int height) {
    int **board = (int**)calloc(height, sizeof(int*)); // 각 행을 저장할 포인터 배열을 동적 할당한다. 
    for (int i = 0; i < height; i++) board[i] = (int*) calloc(n_people * 2 - 1, sizeof(int)); // 각 행에 사다리 정보를 저장할 배열을 동적 할당한다. 
    return board; // 할당된 공간의 포인터를 반환한다. 
}

int check_adjacent(int *board_row, int n_people, int x) {
    if (n_people == 2) return 0; // 플레이어가 두 명이면 이웃하는 경우는 고려하지 않는다. 
    else return (x - 2 >= 0 && board_row[x - 2]) || (x + 2 <= (n_people - 1) * 2 && board_row[x + 2]); // 왼쪽 끝이 아닐때는 왼쪽을 확인, 오른쪽 끝이 아닐때는 오른쪽을 확인한다. 
}

void generate_ladder(int **board, int n_people, int height, int n_line) {
    for (int i = 0; i < height; i++) for (int j = 0; j < n_people * 2; j += 2) board[i][j] = 1; // 세로줄을 그릴 수 있는 공간을 1로 초기화한다. 
    
    // 추가해야 하는 선의 개수만큼 반복한다. 
    while (n_line--) {
        int x = (rand() % (n_people - 1)) * 2 + 1; // x 좌표는 무작위로 1, 3, 5, ... (n_people - 1) * 2 - 1 중 하나가 된다. 
        int y = 1 + rand() % (height - 2); // y 좌표는 무작위로 1, 2, 3, ... height - 2 중 하나가 된다. 
        if (board[y][x] || check_adjacent(board[y], n_people, x)) n_line++; // 이미 선이 그어져 있거나, 이웃하는 경우는 다시 뽑는다. 
        else board[y][x] = 1; // 가로 선을 그릴 수 있다면 그린다. 
    }
}

void free_ladder(int **board, int height) {
    for (int i = 0; i < height; i++) free(board[i]); // 각 행에 대해 할당된 메모리를 해제한다. 
    free(board); // 포인터 배열에 대해 할당된 메모리를 해제한다. 
}

void save_ladder(char *filename, int **board, int n_people, int height, int n_line) {
    FILE *fp = fopen(filename, "w"); // 파일을 쓰기 모드로 열고, 파일 포인터를 얻는다. 
    fprintf(fp, "%d %d %d\n", n_people, height, n_line); // 첫 줄에 플레이어 수, 사다리 높이, 가로 선의 개수를 저장한다.
    // 배열의 모든 가로 선 후보 위치 (모든 행, 홀수 열)에 대해 반복한다. 
    for (int i = 0; i < height; i++) {
        for (int j = 1; j < n_people * 2; j += 2) {
            if (board[i][j]) fprintf(fp, "%d %d\n", i, (j - 1) / 2 + 1); // 가로 선이 있다면 현재 위치를 파일에 저장한다. 
        }
    }
    fclose(fp); // 파일 포인터를 닫는다. 
}

int** load_ladder(char *filename, int *n_people, int *height, int *n_line) {
    FILE *fp = fopen(filename, "r"); // 파일을 읽기 모드로 열고, 파일 포인터를 얻는다. 
    if (fp == NULL) return NULL; // 파일이 존재하지 않으면 FILE DOES NOT EXIST의 신호로 NULL을 반환한다. 
    
    fscanf(fp, "%d %d %d", n_people, height, n_line); // 첫 번째 줄에 있는 사다리의 정보를 읽는다. 

    int **board = allocate_ladder(*n_people, *height); // 사다리를 저장할 메모리를 적절하게 할당한다. 
    for (int i = 0; i < *height; i++) for (int j = 0; j < *n_people * 2; j += 2) board[i][j] = 1; // 세로 선을 그을 수 있는 모든 곳에 1을 표시한다. 
    for (int i = 0; i < *n_line; i++) { // 저장되어 있는 가로 선의 개수만큼 반복한다. 
        int x, y;
        fscanf(fp, "%d %d", &y, &x); // 가로 선의 위치를 읽는다. 
        board[y][(x - 1) * 2 + 1] = 1; // 가로 선이 그어진 곳에 1을 표시한다. 
    }
    
    fclose(fp); // 파일 포인터를 닫는다. 
    return board; // 사다리가 저장된 공간의 포인터를 반환한다. 
}

void show_ladder(int **board, int n_people, int height) {
    // 목적지를 가로로 출력한다. 
    for (int i = 0; i < n_people; i++) printf("%3c ", 'A' + i);
    printf("\n");

    // 사다리를 출력한다. 
    for (int i = 0; i < height; i++) {
        printf("  "); // 각 행의 시작 부분에 공백을 맞춘다. 
        for (int j = 0; j < n_people * 2 - 1; j++) {
            // 아래 프린트는 모두 printf가 아닌 print_color()를 이용해 색을 포함하여 출력한다. 
            if (j % 2 == 0) print_color("+", board[i][j]); // 세로 선 부분에는 + 기호를 프린트한다. 
            else if (board[i][j] != 0) print_color("---", board[i][j]); // 가로 선 부분에는 --- 기호를 프린트한다. 
            else print_color("   ", board[i][j]); // 모두 아닌 경우에는 공백을 프린트한다. 
        }
        printf("\n"); // 각 행의 출력이 끝날때마다 개행한다. 
    }

    // 시작점 (사람 번호)를 가로로 출력한다. 
    for (int i = 0; i < n_people; i++) printf("%3d ", i + 1);
    printf("\n");
}

// Print the coord
int navigate(int **board, int n_people, int height, int start, int wait) {
    int mark = -start, x = (start - 1) * 2, y = height - 1; // trace를 저장할 값 mark와 현재 좌표 x, y를 선언한다. 
    int vel = 0, prev_x = x, prev_y = y; // 현재 가로로 움직이는 속도 (vel)와 이전 위치 (prev_x, prev_y)를 선언 및 초기화한다. 
    
    while (y >= 0) { // 사다리의 맨 위에 도달할 때까지 반복한다. 
        prev_x = x, prev_y = y; // 이전 위치를 저장한다. 
        board[y][x] = mark; // 현재 도달한 위치를 현재 플레이어의 색으로 표시한다. 

        if (x % 2 != 0) { // 현재 위치가 가로 선이라면
            x += vel; // 이전에 움직이던 방향으로 가로로 계속 움직인다. 
        } else { // 현재 위치가 세로 선이라면
            if (vel != 0) { // 이전 step에 가로로 움직였다면
                y--; // 한 칸 위로 움직이고
                vel = 0; // 가로 속도를 0으로 초기화한다. 
            }
            else { // 이전 step에 가로로 움직이지 않았다면
                if (x > 0 && board[y][x - 1]) x += (vel = -1); // 왼쪽으로 움직일 수 있는지 확인하고, 가능하다면 움직인다. 
                else if (x + 1 < n_people * 2 - 1 && board[y][x + 1]) x += (vel = 1); // 오른쪽으로 움직일 수 있는지 확인하고, 가능하다면 움직인다. 
                else y--; // 모두 아니라면 그냥 한 칸 위로 움직인다. 
            }
        }
        
        clear(); // 화면을 지우고
        printf("%d %d \n", prev_y, prev_x); // 현재 좌표를 출력한 뒤
        show_ladder(board, n_people, height); // 색칠된 사다리를 출력한다. 
        if (wait && prev_y) // navigation 과정을 출력하도록 설정되어 있고, 사다리의 맨 위에 도달하지 않았다면
            getchar(); // 사용자가 엔터를 누를 때까지 기다린다. 
    }

    return x / 2 + 1; // 도착한 위치를 반환한다. 
}

void iterate_navigate(int **board, int n_people, int height) {
    clear(); // 화면을 지운다. 
    show_ladder(board, n_people, height); // 사다리를 타기 전 사다리를 출력한다. 
    
    int flag = 1, start; // 반복을 제어할 flag와 시작점을 저장할 변수를 선언한다. 
    int *dest = (int*)calloc(n_people, sizeof(int)); // 각 시작점에서 도착점을 저장할 배열을 동적할당한다. 
    while (flag) {
        printf(">> "); scanf("%d", &start); // 사용자에게 시작점 혹은 다른 신호를 입력받는다.
        flush(); // stdin 입력 버퍼를 비운다. 
        switch (start) {
            case 0: // 사용자가 0을 선택한 경우
                flag = 0; // flag를 0으로 설정하여 반복을 종료한다. 
                break;
            case -1: // 사용자가 -1을 선택한 경우
                clear(); // 화면을 지운다. 
                for (int i = 0; i < n_people; i++) dest[i] = navigate(board, n_people, height, i + 1, 0); // 각 시작점에서 사다리를 타 도착점을 계산한다. 이 과정은 출력하지 않는다. 
                printf("\n");
                for (int i = 0; i < n_people; i++) printf("%d -> %c \n", i + 1, 'A' + dest[i] - 1); // 각 시작점에서 도착점을 출력한다. 
                printf("\n");
                break;
            default: 
                dest[start - 1] = navigate(board, n_people, height, start, 1); // 사용자가 입력한 시작점에서 사다리를 타 도착점을 계산한다. 이 과정은 출력한다. 
                printf("\n");
                printf("result: %d -> %c \n", start, 'A' + dest[start - 1] - 1); // 시작점과 도착점을 출력한다. 
                printf("\n");
                break;
        }
    }
    free(dest); // 목적지를 저장하기 위해 동적할당한 배열을 해제한다. 
}
