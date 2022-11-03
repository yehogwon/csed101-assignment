/**
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 
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
int max(int arr[][SIZE][SIZE], int width, int height);
int min(int arr[][SIZE][SIZE], int width, int height);
int comp_float(float a, float b);

// Image File Management
int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int *width, int *height);
void save_image(int image_rgb[][SIZE][SIZE], int width, int height);

// Image Modification
void rgb_to_hsv(int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int width, int height);
void hsv_to_rgb(float image_hsv[][SIZE][SIZE], int image_rgb[][SIZE][SIZE], int width, int height);
void change_color(int image_hsv[][SIZE][SIZE], int width, int height, int source, int target);

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
        if (menu >= 1 && menu <= 5) break;
        printf("Wrong input! \n");
    }

    switch (menu) {
        case 1: 
            print_histogram(image_hsv, width, height);
            break;
        case 2:
            break;
        case 3:
            print_image(image_rgb, width, height);
        case 4:
            break;
        case 5:
            break;
        default: 
            printf("Something went wrong! This exception is not handled. \n");
            return -500;
    }

    return 0;
}


void set_color_rgb(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void reset_color() {
    printf("\033[0m");
}

int max(int arr[][SIZE][SIZE], int width, int height) {
    int max = arr[0][0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < width; k++) {
                if (arr[i][j][k] > max) max = arr[i][j][k];
            }
        }
    }
    return max;
}

int min(int arr[][SIZE][SIZE], int width, int height) {
    int min = arr[0][0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < height; j++) {
            for (int k = 0; k < width; k++) {
                // printf("cur: %d, min: %d \n", arr[i][j][k], min);
                if (arr[i][j][k] < min) min = arr[i][j][k];
            }
        }
    }
    return min;
}

int comp_float(float a, float b) {
    if (fabs(a - b) < ERROR) return 1;
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

void rgb_to_hsv(int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int width, int height) {
    float c_max = max(image_rgb, width, height) / 255.0, c_min = min(image_rgb, width, height) / 255.0;
    float delta = c_max - c_min;
    printf("c_max: %f, c_min: %f, delta: %f \n", c_max, c_min, delta);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float r = image_rgb[0][i][j] / 255.0, g = image_rgb[1][i][j] / 255.0, b = image_rgb[2][i][j] / 255.0;
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

void hsv_to_rgb(float image_hsv[][SIZE][SIZE], int image_rgb[][SIZE][SIZE], int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float h = image_hsv[0][i][j], s = image_hsv[1][i][j], v = image_hsv[2][i][j];
            float c = v * s;
            float x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
            float m = v - c;

            float r, g, b;
            switch ((int) (h / 60)) {
                case 0:
                    r = c;
                    g = x;
                    b = 0;
                    break;
                case 1:
                    r = x;
                    g = c;
                    b = 0;
                    break;
                case 2:
                    r = 0;
                    g = c;
                    b = x;
                    break;
                case 3:
                    r = 0;
                    g = x;
                    b = c;
                    break;
                case 4:
                    r = x;
                    g = 0;
                    b = c;
                    break;
                case 5:
                    r = c;
                    g = 0;
                    b = x;
                    break;
                default:
                    r = 0;
                    g = 0;
                    b = 0;
                    break;
            }

            image_rgb[0][i][j] = (r + m) * 255;
            image_rgb[1][i][j] = (g + m) * 255;
            image_rgb[2][i][j] = (b + m) * 255;
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
            set_color_rgb(255, 255, 255);
            printf("▇");
            reset_color();
        }
        printf("%d \n", histogram[i]);
    }
}
