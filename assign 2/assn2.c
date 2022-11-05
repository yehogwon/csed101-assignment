/**
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022.11.04
 * OS: macOS 13.0
 * IDE Environment: Visual Studio Code 1.73
 * GCC version: gcc 14.0.0
 * C standard: C99
 * Editor and Terminal Font: Consolas
 * Encoding: UTF-8
 * End of Line Sequence: LF
 * Naming Convention: snake_case
*/

// 필요한 헤더 파일을 include한다. 
#include <stdio.h> // 표준 입출력 및 파일 입출력을 위한 헤더 파일
#include <math.h> // fabsf() 함수와 fmod() 함수 사용을 위한 에더 파일

#define SIZE 75 // 파일 이름의 최대 크기 및 사진 pixel 정보를 담는 배열의 width와 height의 최대 크기를 상수로 정의한다. 
#define ERROR 1e-5 // float 비교에 사용할 오차의 tolerance를 상수로 정의한다. 

/**
 * printf의 출력 색을 RGB로 설정하는 함수
 * 매개변수 r, g, b: 출력 색의 색상 RGB 코드
 * 리턴값: 없음
*/
void set_color_rgb(int r, int g, int b);

/**
 * printf의 출력 색을 초기화하는 함수
 * 매개변수: 없음
 * 리턴값: 없음
*/
void reset_color();

/**
 * 주어진 3개의 float형 실수 중 최댓값을 반환하는 함수
 * 매개변수 a, b, c: 최댓값을 구할 3개의 float형 실수
 * 리턴값: 3개의 float형 실수 중 최댓값
*/
float max(float a, float b, float c);

/**
 * 주어진 3개의 float형 실수 중 최솟값을 반환하는 함수
 * 매개변수 a, b, c: 최솟값을 구할 3개의 float형 실수
 * 리턴값: 3개의 float형 실수 중 최솟값
*/
float min(float a, float b, float c);

/**
 * 주어진 두 개의 float형 실수가 같은지 비교하는 함수
 * 매개변수 a, b: 비교할 두 개의 float형 실수
 * 리턴값: 두 수가 같은 지 여부 (1: true, 0: false)
*/
int comp_float(float a, float b);

/**
 * 주어진 int형 정수가 주어진 닫힌 구간 범위에 속하는지 확인하는 함수
 * 매개변수 n: 확인할 int형 정수
 * 매개변수 a, b: 닫힌 구간의 양 끝 [a, b]
 * 리턴값: n이 닫힌 구간 [a, b]에 속하는 지 여부 (1: true, 0: false)
*/
int within(int n, int a, int b);

/**
 * 주어진 파일 이름을 가진 이미지 파일을 RGB와 HSV로 불러오는 함수
 * 매개변수 filename: 이미지 파일 이름
 * 매개변수 image_rgb: 이미지의 RGB pixel 정보를 저장할 3차원 배열
 * 매개변수 image_hsv: 이미지의 HSV pixel 정보를 저장할 3차원 배열
 * 매개변수 width: 이미지의 가로 크기
 * 매개변수 height: 이미지의 세로 크기
 * 리턴값: 파일을 성공적으로 불러왔는 지 여부 (success: 1, fail: 0)
*/
int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int *width, int *height);

/**
 * 주어진 RGB pixel 정보를 가진 이미지를 파일 output.ppm에 저장하는 함수
 * 매개변수 image_rgb: 저장할 이미지의 RGB pixel 정보를 가진 3차원 배열
 * 매개변수 width: 저장할 이미지의 가로 크기
 * 매개변수 height: 저장할 이미지의 세로 크기
 * 리턴값: 없음
*/
void save_image(int image_rgb[][SIZE][SIZE], int width, int height);

/**
 * RGB 이미지를 HSV 이미지로 변환하는 함수
 * 매개변수 image_rgb: 변환할 이미지의 RGB pixel 정보를 가진 3차원 배열
 * 매개변수 image_hsv: 변환된 이미지의 HSV pixel 정보를 저장할 3차원 배열
 * 매개변수 width: 변환할 이미지의 가로 크기
 * 매개변수 height: 변환할 이미지의 세로 크기
 * 리턴값: 없음
*/
void rgb_to_hsv(int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int width, int height);

/**
 * HSV Pixel을 RGB Pixel으로 변환하는 함수
 * 매개변수 h, s, v: 변환할 HSV Pixel
 * 매개변수 r, g, b: 변환된 RGB Pixel
 * 리턴값: 없음
*/
void dot_hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b);

/**
 * HSV 이미지를 RGB 이미지로 변환하는 함수
 * 매개변수 image_hsv: 변환할 이미지의 HSV pixel 정보를 가진 3차원 배열
 * 매개변수 image_rgb: 변환된 이미지의 RGB pixel 정보를 저장할 3차원 배열
 * 매개변수 width: 변환할 이미지의 가로 크기
 * 매개변수 height: 변환할 이미지의 세로 크기
 * 리턴값: 없음
*/
void hsv_to_rgb(float image_hsv[][SIZE][SIZE], int image_rgb[][SIZE][SIZE], int width, int height);

/**
 * 이미지의 색조와 변환할 색조를 입력받는 함수
 * 매개변수 source: 변환할 원래 색조
 * 매개변수 target: 변환할 새로운 색조
 * 리턴값: 없음
*/
void input_colors(int *source, int *target);

/**
 * 주어진 HSV 이미지의 색조를 변환하는 함수
 * 매개변수 image_hsv: 색조를 변환할 이미지의 HSV pixel 정보를 가진 3차원 배열 (in-place로 수정됨)
 * 매개변수 width: 변환할 이미지의 가로 크기
 * 매개변수 height: 변환할 이미지의 세로 크기
 * 매개변수 source: 이미지의 원래 색조
 * 매개변수 target: 변환할 새로운 색조
 * 리턴값: 없음
*/
void change_color(float image_hsv[][SIZE][SIZE], int width, int height, int source, int target);

/**
 * 주어진 RGB 이미지를 출력하는 함수
 * 매개변수 image_rgb: 출력할 이미지의 RGB pixel 정보를 가진 3차원 배열
 * 매개변수 width: 출력할 이미지의 가로 크기
 * 매개변수 height: 출력할 이미지의 세로 크기
 * 리턴값: 없음
*/
void print_image(int image_rgb[][SIZE][SIZE], int width, int height);

/**
 * 주어진 HSV 이미지의 히스토그램을 출력하는 함수
 * 매개변수 image_hsv: 히스토그램을 출력할 이미지의 HSV pixel 정보를 가진 3차원 배열
 * 매개변수 width: 히스토그램을 출력할 이미지의 가로 크기
 * 매개변수 height: 히스토그램을 출력할 이미지의 세로 크기
 * 리턴값: 없음
*/
void print_histogram(float image_hsv[][SIZE][SIZE], int width, int height);

int main(void) {
    char file_name[SIZE];

    printf("Enter input filename: ");
    scanf("%s", file_name);

    int image_rgb[3][SIZE][SIZE] = {0, 0, 0};
    float image_hsv[3][SIZE][SIZE] = {0, 0, 0};
    int width, height;
    int file_status = load_image(file_name, image_rgb, image_hsv, &width, &height);

    if (file_status == 0) {
        printf("File not found: %s \n", file_name);
        return 404;
    }

    int flag = 1;
    while (flag) {
        printf("\n");
        printf("========================= \n");
        printf("   IMAGE COLOR CHANGER    \n");
        printf("========================= \n");
        printf(" 1. Image Histogram \n");
        printf(" 2. Change Color \n");
        printf(" 3. Print Image \n");
        printf(" 4. Save Image \n");
        printf(" 5. Exit \n");
        printf("Loaded file: %s \n", file_name);
        printf("\n");

        int menu;
        while (1) {
            printf("Choose menu number >> ");
            scanf("%d", &menu);
            if (within(menu, 1, 5)) break;
            printf("Wrong input! \n");
        }

        int source, target;
        switch (menu) {
            case 1: 
                print_histogram(image_hsv, width, height);
                break;
            case 2: 
                print_histogram(image_hsv, width, height);
                input_colors(&source, &target);
                change_color(image_hsv, width, height, source, target);
                break;
            case 3:
                hsv_to_rgb(image_hsv, image_rgb, width, height);
                print_image(image_rgb, width, height);
                break;
            case 4:
                hsv_to_rgb(image_hsv, image_rgb, width, height);
                save_image(image_rgb, width, height);
                break;
            case 5:
                flag = 0;
                break;
            default: 
                printf("Something went wrong! This exception is not handled. \n");
                return -500;
        }
    }

    return 0;
}

void set_color_rgb(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b); // ASCII Escape Character를 이용하여 색상을 출력하는 색상을 주어진 RGB 코드로 변경한다. 
}

void reset_color() {
    printf("\033[0m"); // ASCII Escape Character를 이용하여 색상을 출력하는 색상을 reset한다. 
}

float max(float a, float b, float c) {
    float max = a; // 최댓값을 a로 설정하고
    if (b > max) max = b; // b가 이전의 최댓값보다 크다면, 최댓값을 b로 업데이트한다. 
    if (c > max) max = c; // c가 이전의 최댓값보다 크다면, 최댓값을 c로 업데이트한다. 
    return max; // 계산된 최댓값 max를 반환한다. 
}

float min(float a, float b, float c) {
    float min = a; // 최솟값을 a로 설정하고
    if (b < min) min = b; // b가 이전의 최솟값보다 크다면, 최솟값을 b로 업데이트한다. 
    if (c < min) min = c; // c가 이전의 최솟값보다 크다면, 최솟값을 c로 업데이트한다. 
    return min; // 계산된 최솟값 max를 반환한다. 
}

int comp_float(float a, float b) {
    if (fabsf(a - b) < ERROR) return 1; // 두 실수의 차이가 tolerance 범위 내에 있으면 같은 수로 판단하고 1을 반환한다. 
    return 0; // 그렇지 않으면 0을 반환한다. 
}

int within(int n, int a, int b) {
    if (a <= n && n <= b) return 1; // n이 [a, b]에 속한다면 1을 반환한다. 
    return 0; // 그렇지 않으면 0을 반환한다.
}

int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int *width, int *height) {
    FILE *f = fopen(filename, "r"); // 이미지 파일을 읽기 모드로 열어 f에 저장한다. 
    if (f == NULL) return 0; // 파일을 여는 데 실패하면 (파일이 존재하지 않으면) 0을 반환한다. 

    char magic_number[SIZE]; // 이미지 파일의 매직 넘버를 저장할 변수이다. `P3`
    fscanf(f, "%s", magic_number); // 이미지 파일의 매직 넘버를 읽어 magic_number에 저장한다.

    int max_value; // 이미지 파일의 최대 픽셀 값 (255)을 저장할 변수이다.
    fscanf(f, "%d %d %d", width, height, &max_value); // 이미지 파일의 너비, 높이, 최대 픽셀 값을 읽어 각각 width, height, max_value에 저장한다.

    // 반복문을 돌며 각 픽셀의 정보를 읽어 image_rgb에 저장한다. 
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            fscanf(f, "%d %d %d", &image_rgb[0][i][j], &image_rgb[1][i][j], &image_rgb[2][i][j]);
        }
    }

    // image_rgb를 이용하여 image_hsv에 HSV 정보를 저장한다. 
    rgb_to_hsv(image_rgb, image_hsv, *width, *height);

    fclose(f); // 파일을 닫는다. 
    return 1; // 성공적으로 파일을 읽고 처리했으므로 1을 반환한다. 
}

void save_image(int image_rgb[][SIZE][SIZE], int width, int height) {
    FILE *f = fopen("output.ppm", "w"); // 이미지 파일을 쓰기 모드로 열어 f에 저장한다. 
    fprintf(f, "P3 %d %d 255\n", width, height); // 이미지 파일의 매직 넘버 `P3`, 너비, 높이, 최대 픽셀 값을 출력한다.
    // 반복문을 돌며 각 픽셀의 정보를 순서대로 파일에 저장한다. 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(f, "%d %d %d ", image_rgb[0][i][j], image_rgb[1][i][j], image_rgb[2][i][j]);
        }
    }
    fclose(f); // 파일을 닫는다.
}

// TODO: Add comments on the functions associated with color modification
void rgb_to_hsv(int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float r = image_rgb[0][i][j] / 255.0, g = image_rgb[1][i][j] / 255.0, b = image_rgb[2][i][j] / 255.0;
            float c_max = max(r, g, b), c_min = min(r, g, b);
            float delta = c_max - c_min;
            
            float h, s, v;

            // Compute H
            if (delta == 0) h = 0;
            else if (c_max == r) h = 60 * (((g - b) / delta));
            else if (c_max == g) h = 60 * (((b - r) / delta) + 2);
            else if (c_max == b) h = 60 * (((r - g) / delta) + 4);
            if (h < 0) h += 360;

            // Compute S
            if (c_max == 0) s = 0;
            else s = delta / c_max;

            // Compute V
            v = c_max;

            image_hsv[0][i][j] = h;
            image_hsv[1][i][j] = s;
            image_hsv[2][i][j] = v;
        }
    }
}

void dot_hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b) {
    float c = v * s;
    float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
    float m = v - c;

    float _r, _g, _b;

    switch ((int) (h / 60)) {
        case 0:
            _r = c;
            _g = x;
            _b = 0;
            break;
        case 1:
            _r = x;
            _g = c;
            _b = 0;
            break;
        case 2:
            _r = 0;
            _g = c;
            _b = x;
            break;
        case 3:
            _r = 0;
            _g = x;
            _b = c;
            break;
        case 4:
            _r = x;
            _g = 0;
            _b = c;
            break;
        case 5:
            _r = c;
            _g = 0;
            _b = x;
            break;
        default:
            _r = 0;
            _g = 0;
            _b = 0;
            break;
    }

    *r = (_r + m) * 255;
    *g = (_g + m) * 255;
    *b = (_b + m) * 255;
}

void hsv_to_rgb(float image_hsv[][SIZE][SIZE], int image_rgb[][SIZE][SIZE], int width, int height) {
    // 반복문을 돌며 각 픽셀의 HSV 값으로 RGB 값을 계산하고 저장한다. 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            dot_hsv_to_rgb(image_hsv[0][i][j], image_hsv[1][i][j], image_hsv[2][i][j], 
                &image_rgb[0][i][j], &image_rgb[1][i][j], &image_rgb[2][i][j]);
        }
    }
}

void input_colors(int *source, int *target) {
    // valid한 입력이 들어올 때 까지 반복적으로 source 색조를 입력받는다. 
    while (1) {
        printf("Choose source color >> ");
        scanf("%d", source);
        if (within(*source, 0, 11)) break; // source 색조가 0 ~ 11 사이의 값이면 반복문을 빠져나간다. 
        printf("Wrong input! \n"); // 그렇지 않으면 오류 메시지를 출력하고 다시 반복문을 돈다. 
    }

    // valid한 입력이 들어올 때 까지 반복적으로 target 색조를 입력받는다.
    while (1) {
        printf("Choose target color >> ");
        scanf("%d", target);
        if (within(*target, 0, 11)) break; // target 색조가 0 ~ 11 사이의 값이면 반복문을 빠져나간다.
        printf("Wrong input! \n"); // 그렇지 않으면 오류 메시지를 출력하고 다시 반복문을 돈다. 
    }
}

void change_color(float image_hsv[][SIZE][SIZE], int width, int height, int source, int target) {
    int diff = (target - source) * 30; // modify해야 하는 색조의 차이를 계산한다. 
    // 반복문을 돌면서 image_hsv의 색조를 diff만큼 수정한다. 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image_hsv[0][i][j] += diff; // 색조를 diff만큼 modify한다. 
            if (image_hsv[0][i][j] < 0) image_hsv[0][i][j] += 360; // 만약 색조 범위가 0보다 작으면 360을 더해 정상 범위로 돌린다. 
            if (image_hsv[0][i][j] >= 360) image_hsv[0][i][j] -= 360; // 만약 색조 범위가 360보다 크면 360을 빼 정상 범위로 돌린다.
        }
    }
}

void print_image(int image_rgb[][SIZE][SIZE], int width, int height) {
    // 반복문을 돌며 이미지 각 픽셀을 '▇'로 출력한다. 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // 출력 색을 현재 픽셀의 RGB 값으로 설정한다. 
            set_color_rgb(image_rgb[0][i][j], image_rgb[1][i][j], image_rgb[2][i][j]);
            printf("▇"); // 픽셀 섹으로 '▇'를 출력한다.
            reset_color(); // 출력 색을 기본 색으로 설정한다. 
        }
        printf("\n"); // 행이 끝나면 개행한다. 
    }
}

void print_histogram(float image_hsv[][SIZE][SIZE], int width, int height) {
    int histogram[12] = {0}; // 각 색조의 빈도수를 저장할 배열을 선언하고 0으로 초기화한다. 
    // 반복문을 돌며 histogram 배열에 각 색조의 빈도수를 저장한다. 
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (comp_float(image_hsv[1][i][j], 0)) continue; // 현재 색이 무채색 (saturation = 0)이라면 다음 픽셀로 넘어간다. 
            histogram[(int) (image_hsv[0][i][j] / 30)]++; // 그렇지 않다면 해당 색조의 빈도수를 1 증가시킨다. 
        }
    }
    
    // 반복문을 돌며 각 색조에 대한 histogram을 출력한다. 
    for (int i = 0; i < 12; i++) {
        printf("[%2d]", i); // 현재 색조 번호를 출력한다. 
        
        // 현재 색조의 RGB 값을 계산한다. 
        int r, g, b;
        dot_hsv_to_rgb(i * 30, 1, 1, &r, &g, &b);
        
        // 현재 색조의 RGB 값을 출력 색으로 설정한다. 
        set_color_rgb(r, g, b);
        
        // 반복문을 돌며 현재 색조의 histogram `▇`로 막대를 출력한다. 
        for (int j = 0; j < histogram[i] / 10; j++) printf("▇");

        // 출력 색을 기본 색으로 설정한다.
        reset_color();

        // 현재 색조의 빈도수를 출력하고 개행한다. 
        printf("%d \n", histogram[i]);
    }
}
