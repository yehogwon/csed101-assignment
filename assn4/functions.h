/**
 * File: functions.h
 * Author: 20220358 권예호 (Yeho Gwon)
 * Date: 2022.12.03
 * OS: macOS 13.0.1
 * IDE Environment: Visual Studio Code 1.74.0
 * GCC version: gcc 14.0.0
 * C standard: C99
 * Encoding: UTF-8
 * End of Line Sequence: LF
 * Naming Convention: snake_case
*/

#ifndef FUNCTIONS_H // include guard ; functions.h가 중복으로 include 되는 것을 방지하기 위해 전체 코드를 ifndef로 묶는다. 
#define FUNCTIONS_H // 처음 include 되는 경우에 FUNCTIONS_H를 define함으로써 다음부터는 ifndef가 false가 되어 전체 코드가 실행되지 않는다. 

// 음악 정보를 저장할 Music structure
typedef struct {
    char title[15];
    char artist[15];
    float size;
    float pref;
} Music;

// linkedlist를 구성하는 Node 정보 ; Node는 Music structure를 포함하고 다음 Node를 가리키는 포인터를 가진다. 
typedef struct Node {
    Music data;
    struct Node *next;
} Node;

/**
 * 두 개의 Music structure pointer가 주어졌을 때, 두 음악의 제목을 비교하여 정렬에 사용하는 함수
 * 매개변수 a: Music structure pointer
 * 매개변수 b: Music structure pointer
 * 리턴값: a < b 여부를 float로 반환
*/
float crit_title(Music *a, Music *b);


/**
 * 두 개의 Music structure pointer가 주어졌을 때, 두 음악의 preference를 비교하여 정렬에 사용하는 함수
 * 매개변수 a: Music structure pointer
 * 매개변수 b: Music structure pointer
 * 리턴값: a < b 여부를 float로 반환
*/
float crit_pref(Music *a, Music *b);

/**
 * playlist의 head dummy node가 주어졌을 때, playlist를 출력하는 함수
 * 매개변수 head: playlist의 head dummy node
 * 매개변수 header: 출력할 때 표시할 제목 문자열
 * 리턴값: 없음
*/
void show_fn(Node *head, char *header);

/**
 * playlist에서 preference 순서로 n개의 음악을 추출하여 출력하는 함수
 * 매개변수 head: playlist의 head dummy node
 * 매개변수 n: 추출할 음악의 개수
 * 리턴값: 성공적으로 show 했다면 0, 실패했다면 1
*/
int show_favorites_fn(Node *head, int n);

/**
 * playlist에 새로운 음악을 추가하는 함수 ; criterion에 따라 정렬한다. 
 * 매개변수 head: playlist의 head dummy node
 * 매개변수 data: 추가할 음악 정보
 * 매개변수 criterion: 음악을 추가할 위치를 결정하는 함수 (정렬 기준)
 * 리턴값: 없음
*/
void add_fn(Node *head, Music *data, float (*criterion)(Music *, Music *));

/**
 * playlist에서 특정 제목의 음악을 삭제하는 함수
 * 매개변수 head: playlist의 head dummy node
 * 매개변수 title: 삭제할 음악의 제목
 * 리턴값: 성공적으로 삭제했다면 0, 실패했다면 (존재하지 않는다면) -1
*/
int delete_fn(Node *head, char *title);

/**
 * 프로그램을 정리하고 종료하는 함수
 * 매개변수 head: playlist의 head dummy node
 * 매개변수 filename: playlist를 저장할 파일 이름
 * 리턴값: 없음
*/
void exit_fn(Node *head, char *filename);

#endif // FUNCTIONS_H
