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

    int image_rgb[3][SIZE][SIZE], image_hsv[3][SIZE][SIZE];
    int file_status = load_image(file_name, image_rgb, image_hsv, SIZE, SIZE);

    if (file_status == 0) {
        printf("File not found: %s \n", file_name);
        return 404;
    }
    
    printf("======================== \n");
    printf("  IMAGE COLOR CHANGER  ");
    printf("======================== \n");
    printf("  1. Image Histogram \n");
    printf("  2. Change Color \n");
    printf("  3. Print Image \n");
    printf("  4. Save Image \n");
    printf("  5. Exit \n");
    printf("Loaded file: %s \n", file_name);
    printf("\n");

    int menu;
    printf("Choose menu number >> ");
    scanf("%d", &menu);
    return 0;
}


void set_color_rgb(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void reset_color() {
    printf("\033[0m");
}
