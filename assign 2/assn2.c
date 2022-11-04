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

#include <stdio.h>
#include <math.h>

#define SIZE 75
#define ERROR 1e-5

// For visualize
void set_color_rgb(int r, int g, int b);
void reset_color();

// Tool
float max(float a, float b, float c);
float min(float a, float b, float c);
int comp_float(float a, float b);
int within(int n, int a, int b); // check if n is in [a, b]

// Image File Management
int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int *width, int *height);
void save_image(int image_rgb[][SIZE][SIZE], int width, int height);

// Image Modification
void rgb_to_hsv(int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int width, int height);
void dot_hsv_to_rgb(float h, float s, float v, int *r, int *g, int *b);
void hsv_to_rgb(float image_hsv[][SIZE][SIZE], int image_rgb[][SIZE][SIZE], int width, int height);

void input_colors(int *source, int *target);
void change_color(float image_hsv[][SIZE][SIZE], int width, int height, int source, int target);

// Image Visualization
void print_image(int image_rgb[][SIZE][SIZE], int width, int height);
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
        printf("======================== \n");
        printf("   IMAGE COLOR CHANGER   \n");
        printf("======================== \n");
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
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void reset_color() {
    printf("\033[0m");
}

float max(float a, float b, float c) {
    float max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

float min(float a, float b, float c) {
    float min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

int comp_float(float a, float b) {
    if (fabsf(a - b) < ERROR) return 1;
    return 0;
}

int within(int n, int a, int b) {
    if (a <= n && n <= b) return 1;
    return 0;
}

int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int *width, int *height) {
    FILE *f = fopen(filename, "r");
    if (f == NULL) return 0;

    char magic_number[SIZE];
    fscanf(f, "%s", magic_number);

    int max_value;
    fscanf(f, "%d %d %d", width, height, &max_value);

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            fscanf(f, "%d %d %d", &image_rgb[0][i][j], &image_rgb[1][i][j], &image_rgb[2][i][j]);
        }
    }

    rgb_to_hsv(image_rgb, image_hsv, *width, *height);

    fclose(f);
    return 1;
}

void save_image(int image_rgb[][SIZE][SIZE], int width, int height) {
    FILE *f = fopen("output.ppm", "w");
    fprintf(f, "P3 %d %d 255\n", width, height);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fprintf(f, "%d %d %d ", image_rgb[0][i][j], image_rgb[1][i][j], image_rgb[2][i][j]);
        }
    }
    fclose(f);
}

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
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float h = image_hsv[0][i][j], s = image_hsv[1][i][j], v = image_hsv[2][i][j];
            dot_hsv_to_rgb(image_hsv[0][i][j], image_hsv[1][i][j], image_hsv[2][i][j], 
                &image_rgb[0][i][j], &image_rgb[1][i][j], &image_rgb[2][i][j]);
        }
    }
}

void input_colors(int *source, int *target) {
    while (1) {
        printf("Choose source color >> ");
        scanf("%d", source);
        if (within(*source, 0, 11)) break;
        printf("Wrong input! \n");
    }

    while (1) {
        printf("Choose target color >> ");
        scanf("%d", target);
        if (within(*target, 0, 11)) break;
        printf("Wrong input! \n");
    }
}

void change_color(float image_hsv[][SIZE][SIZE], int width, int height, int source, int target) {
    int diff = target - source;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image_hsv[0][i][j] += diff * 30;
            if (image_hsv[0][i][j] < 0) image_hsv[0][i][j] += 360;
            if (image_hsv[0][i][j] >= 360) image_hsv[0][i][j] -= 360;
        }
    }
}

void print_image(int image_rgb[][SIZE][SIZE], int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            set_color_rgb(image_rgb[0][i][j], image_rgb[1][i][j], image_rgb[2][i][j]);
            printf("▇");
            reset_color();
        }
        printf("\n");
    }
}

void print_histogram(float image_hsv[][SIZE][SIZE], int width, int height) {
    int histogram[12] = {0};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (comp_float(image_hsv[1][i][j], 0)) continue;
            histogram[(int) (image_hsv[0][i][j] / 30)]++;
        }
    }

    for (int i = 0; i < 12; i++) {
        printf("[%2d]", i);
        for (int j = 0; j < histogram[i] / 10; j++) {
            int r, g, b;
            dot_hsv_to_rgb(i * 30, 1, 1, &r, &g, &b);
            set_color_rgb(r, g, b);
            printf("▇");
            reset_color();
        }
        printf("%d \n", histogram[i]);
    }
}
