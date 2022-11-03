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

// Image File Management
int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float image_hsv[][SIZE][SIZE], int *width, int *height);
void save_image(int image_rgb[][SIZE][SIZE], int width, int height);

// Image Modification
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

    fclose(f);
    return 1;
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
