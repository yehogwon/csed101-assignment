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

float crit_title(Music *a, Music *b)
{
    return strcmp(a->title, b->title);
}

float crit_pref(Music *a, Music *b)
{
    return -(a->pref - b->pref);
}

void add_fn(Node *head, Music *data, float (*criterion)(Music *, Music *)) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = *data;

    Node *prev = head;
    Node *cursor = head->next;
    while (cursor != NULL) {
        if (criterion(&new_node->data, &cursor->data) < 0) break;
        prev = cursor;
        cursor = cursor->next;
    }
    prev->next = new_node;
    new_node->next = cursor;
}

int show_favorites_fn(Node *head, int n) {
    Node *favo_head = (Node*) malloc(sizeof(Node)), *favo_cursor = favo_head;
    favo_head->next = NULL;

    // TODO: Enhance the space efficiency
    Node *cursor = head->next;
    while (cursor != NULL) {
        add_fn(favo_head, &cursor->data, crit_pref);
        cursor = cursor->next;
    }
    
    favo_cursor = favo_head;
    while (n--) {
        if (favo_cursor->next == NULL) return -1;
        favo_cursor = favo_cursor->next;
    }
    favo_cursor->next = NULL;

    show_fn(favo_head, "FAVORITES");

    free(favo_head);

    return 0;
}

int delete_fn(Node *head, char *title) {
    int idx = 1;
    Node *prev = head;
    Node *cursor = head->next;
    while (cursor != NULL) {
        if (strcmp(cursor->data.title, title) == 0) {
            prev->next = cursor->next;
            break;
        }
        prev = cursor;
        cursor = cursor->next;
        idx++;
    }

    if (cursor) {
        printf("==================================================================================== \n");
        printf(" No.         Title                  Artist            Volume          Preference     \n");
        printf("------------------------------------------------------------------------------------ \n");
        printf("#-%2d  |%14s      |%14s      |     %5.2fMB     |     %5.2f \n", idx, cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        printf("------------------------------------------------------------------------------------ \n");
        free(cursor);
        return 0;
    } else return -1;
}

void show_fn(Node *head, char *header) {
    int count = 0;
    float storage = 0;
    Node *cursor = head->next;
    
    printf("                                      %9s                                      \n", header);
    printf("==================================================================================== \n");
    printf(" No.         Title                  Artist            Volume          Preference     \n");
    printf("------------------------------------------------------------------------------------ \n");
    if (cursor == NULL) printf("Empty Playlist! \n");
    while (cursor != NULL) {
        printf("#%-2d  |%14s      |%14s      |     %5.2fMB     |     %5.2f \n", ++count, cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        storage += cursor->data.size;
        cursor = cursor->next;
    }
    printf("------------------------------------------------------------------------------------ \n");
    printf("Total number of songs: %d \n", count);
    printf("Storage: %.2f MB \n", storage);
    printf("==================================================================================== \n");
}

void exit_fn(Node *head, char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    Node *cursor = head->next;
    while (cursor != NULL) {
        fprintf(fp, "%s\t%s\t%.6f\t%.6f\n", cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        cursor = cursor->next;
    }
    fclose(fp);

    cursor = head;
    while (cursor != NULL) {
        Node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
    
    printf("프로그램을 종료합니다. \n");
}
