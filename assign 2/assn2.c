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

#define SIZE 75

// For visualize
void set_color_rgb(int r, int g, int b);
void reset_color();

// Tool
int max(int arr[][SIZE][SIZE]);
int min(int arr[][SIZE][SIZE]);

// Image File Management
int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int *width, int *height);
void save_image(int image_rgb[][SIZE][SIZE], int width, int height);

// Image Modification
void rgb_to_hsv(const int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int width, int height);
void change_color(int image_hsv[][SIZE][SIZE], int width, int height, int source, int target);

// Image Visualization
void print_image(int image_rgb[][SIZE][SIZE], int width, int height);
void print_histogram(float image_hsv[][SIZE][SIZE], int width, int height);

int main(void) {
    char file_name[SIZE];

    printf("Enter input filename: ");
    scanf("%s", file_name);

    int image_rgb[3][SIZE][SIZE];
    float image_hsv[3][SIZE][SIZE];
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

int max(int arr[3][SIZE][SIZE]) {
    int max = arr[0][0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (arr[i][j][k] > max) max = arr[i][j][k];
            }
        }
    }
    return max;
}

int min(int arr[3][SIZE][SIZE]) {
    int min = arr[0][0][0];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                if (arr[i][j][k] < min) min = arr[i][j][k];
            }
        }
    }
    return min;
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

void rgb_to_hsv(const int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int width, int height) {
    float c_max = max(image_rgb) / 255.0, c_min = min(image_rgb) / 255.0;
    float delta = c_max - c_min;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float r = image_rgb[0][i][j] / 255.0, g = image_rgb[1][i][j] / 255.0, b = image_rgb[2][i][j] / 255.0;
            float h, s, v;

            // Compute H
            if (delta == 0) h = 0;
            else if (c_max == r) h = 60 * (((g - b) / delta) % 6);
            else if (c_max == g) h = 60 * (((b - r) / delta) + 2);
            else if (c_max == b) h = 60 * (((r - g) / delta) + 4);

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
