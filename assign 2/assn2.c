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
int load_image(const char *filename, int image_rgb[][SIZE][SIZE], float iamge_hsv[][SIZE][SIZE], int *width, int *height);
void save_image(int image_rgb[][SIZE][SIZE], int width, int height);

// Image Modification
void change_color(int image_hsv[][SIZE][SIZE], int width, int height, int source, int target);

// Image Visualization
void print_image(int image_rgb[][SIZE][SIZE], int width, int height);
void print_histogram(float image_hsv[][SIZE][SIZE], int width, int height);

int main(void) {
    return 0;
}


void set_color_rgb(int r, int g, int b) {
    printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void reset_color() {
    printf("\033[0m");
}
