/**
 * File: functions.c
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

float crit_title(Music *a, Music *b) {
    return strcmp(a->title, b->title); // strcmp()를 이용하여 문자열 비교
}

float crit_pref(Music *a, Music *b) {
    return -(a->pref - b->pref); // 두 음악의 preference를 비교
}

void free_list(Node *head) {
    Node *cursor = head; // 첫 번째 노드를 가리키는 포인터
    while (cursor != NULL) { // 맨 끝에 도달할 때까지 반복
        Node *temp = cursor; // 삭제할 노드를 가리키는 포인터
        cursor = cursor->next; // 현재 노드 삭제
        free(temp); // 삭제된 노드 할당 해제
    }
}

void add_fn(Node *head, Music *data, float (*criterion)(Music *, Music *)) {
    Node *new_node = (Node*) malloc(sizeof(Node)); // 추가할 노드를 동적할당
    new_node->data = *data; // 새로운 노드에 데이터를 복사

    Node *prev = head; // 삽입할 위치를 찾기 위한 이전 노드
    Node *cursor = head->next; // 삽입할 위치를 찾기 위한 현재 노드
    while (cursor != NULL) { // 맨 끝에 도달할 때까지 반복
        if (criterion(&new_node->data, &cursor->data) < 0) break; // 삽입할 위치를 찾았다면 반복문을 빠져나옴
        // 삽입할 위치를 찾지 못했다면 다음 노드로 이동
        prev = cursor;
        cursor = cursor->next;
    }
    // 삽입할 위치를 찾았으므로 새로운 노드를 삽입
    prev->next = new_node;
    new_node->next = cursor;
}

int show_favorites_fn(Node *head, int n) {
    Node *favo_head = (Node*) malloc(sizeof(Node)), *favo_cursor = favo_head; // 즐겨찾기를 저장할 연결리스트의 헤드 노드 (기존 playlist를 복사한다)
    favo_head->next = NULL; // 즐겨찾기를 저장할 연결리스트의 헤드 노드의 다음 노드를 NULL로 초기화

    // TODO: Enhance the space efficiency
    Node *cursor = head->next; // 기존 playlist의 노드를 순회하기 위한 포인터
    while (cursor != NULL) { // 맨 끝에 도달할 때까지 반복
        add_fn(favo_head, &cursor->data, crit_pref); // 기존 playlist의 노드를 favo linkedlist에 추가 ; preference를 기준으로 정렬한다. 
        cursor = cursor->next; // 다음 노드로 이동
    }
    
    favo_cursor = favo_head; // 즐겨찾기를 저장할 연결리스트의 헤드 노드를 순회하기 위한 포인터
    while (n--) { // n번 반복
        if (favo_cursor->next == NULL) return -1; // playlist에 있는 전체 음악의 개수가 n개 미만이라면 -1을 반환
        favo_cursor = favo_cursor->next; // 다음 노드로 이동
    }
    favo_cursor->next = NULL; // favo linkedlist를 n개에서 끊는다. 

    show_fn(favo_head, "FAVORITES"); // favo linkedlist를 출력한다. 이때, header는 FAVORITES를 출력한다. 

    free_list(favo_head); // favo linkedlist의 메모리를 해제한다. 

    return 0; // 성공적으로 수행했으므로 0을 반환
}

int delete_fn(Node *head, char *title) {
    int idx = 1; // 삭제할 노드의 인덱스를 저장하기 위한 변수
    Node *prev = head; // 삭제할 노드의 이전 노드
    Node *cursor = head->next; // 삭제할 노드
    while (cursor != NULL) { // 맨 끝에 도달할 때까지 반복
        if (strcmp(cursor->data.title, title) == 0) { // 삭제할 노드를 찾았다면 반복문을 빠져나옴
            prev->next = cursor->next; // 삭제할 노드를 연결리스트에서 제거
            break; // 반복문을 빠져나옴
        }
        // 다음 노드로 이동
        prev = cursor;
        cursor = cursor->next;
        idx++; // 인덱스를 1 증가
    }

    if (cursor) {
        // 삭제한 음악의 정보를 출력
        printf("==================================================================================== \n");
        printf(" No.         Title                  Artist            Volume          Preference     \n");
        printf("------------------------------------------------------------------------------------ \n");
        printf("#%-2d  |%14s      |%14s      |     %5.2fMB     |     %5.2f \n", idx, cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        printf("------------------------------------------------------------------------------------ \n");
        free(cursor); // 삭제한 노드의 메모리를 해제
        return 0; // 성공적으로 삭제했으므로 0을 반환
    } else return -1; // 삭제할 노드를 찾지 못했으므로 -1을 반환
}

void show_fn(Node *head, char *header) {
    int count = 0; // 음악의 개수를 세기 위한 변수
    float storage = 0; // 음악의 총 용량을 저장하기 위한 변수
    Node *cursor = head->next; // 현재 node를 가리키는 cursor
    
    // header 출력
    printf("                                      %9s                                      \n", header);
    printf("==================================================================================== \n");
    printf(" No.         Title                  Artist            Volume          Preference     \n");
    printf("------------------------------------------------------------------------------------ \n");
    if (cursor == NULL) printf("Empty Playlist! \n"); // 노드가 없다면 (playlist가 비었다면) 사용자에게 알린다. 
    while (cursor != NULL) { // 노드가 없을 때까지 반복
        // 현재 음악의 정보를 출력
        printf("#%-2d  |%14s      |%14s      |     %5.2fMB     |     %5.2f \n", ++count, cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        storage += cursor->data.size; // 현재 음악의 용량을 총 용량에 더한다.
        cursor = cursor->next; // 다음 노드로 이동
    }
    printf("------------------------------------------------------------------------------------ \n");
    printf("Total number of songs: %d \n", count); // 총 음악의 개수를 출력
    printf("Storage: %.2f MB \n", storage); // 총 용량을 출력
    printf("==================================================================================== \n");
}

void exit_fn(Node *head, char *filename) {
    FILE *fp = fopen(filename, "w"); // 파일을 쓰기 모드로 열기
    if (fp == NULL) return; // 파일 열기에 실패하면 함수를 종료 (uncaught error)

    Node *cursor = head->next; // 첫 번째 노드를 가리키는 포인터
    while (cursor != NULL) { // 맨 끝에 도달할 때까지 반복
        // 파일에 노드의 데이터를 저장
        fprintf(fp, "%s\t%s\t%.6f\t%.6f\n", cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        cursor = cursor->next; // 다음 노드로 이동
    }
    fclose(fp); // 파일 닫기
    free_list(head); // 동적 할당한 메모리 해제
    
    printf("프로그램을 종료합니다. \n"); // 프로그램을 종료한다는 prompt 출력
}
