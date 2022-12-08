/**
 * File: functions.h
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022.12.03
 * OS: macOS 13.0.1
 * IDE Environment: Visual Studio Code 1.73.1
 * GCC version: gcc 14.0.0
 * C standard: C99
 * Encoding: UTF-8
 * End of Line Sequence: LF
 * Naming Convention: snake_case
*/

#ifndef FUNCTIONS_H // include guard ; functions.h가 중복으로 include 되는 것을 방지하기 위해 전체 코드를 ifndef로 묶는다. 
#define FUNCTIONS_H // 처음 include 되는 경우에 FUNCTIONS_H를 define함으로써 다음부터는 ifndef가 false가 되어 전체 코드가 실행되지 않는다. 

typedef struct {
    char title[15];
    char artist[15];
    float size;
    float pref;
} Music;

typedef struct Node {
    Music data;
    struct Node *next;
} Node;

/**
 * 두 개의 Music structure pointer가 주어졌을 때, 두 음악의 제목을 비교하여 정렬에 사용하는 함수
 * 매개변수 a: Music structure pointer
 * 매개변수 b: Music structure pointer
 * 리턴값: a와 b의 제목을 비교했을 때, 
*/
float crit_title(Music *a, Music *b);


/**
 * 
 * 매개변수 : 
 * 리턴값: 
*/
float crit_pref(Music *a, Music *b);

/**
 * 
 * 매개변수 : 
 * 리턴값: 
*/
void show_fn(Node *head, char *header);

/**
 * 
 * 매개변수 : 
 * 리턴값: 
*/
int show_favorites_fn(Node *head, int n);

/**
 * 
 * 매개변수 : 
 * 리턴값: 
*/
void add_fn(Node *head, Music *data, float (*criterion)(Music *, Music *));

/**
 * 
 * 매개변수 : 
 * 리턴값: 
*/
int delete_fn(Node *head, char *title);

/**
 * 
 * 매개변수 : 
 * 리턴값: 
*/
void exit_fn(Node *head, char *filename);

#endif