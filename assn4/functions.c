#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void add_fn(Node *head, Music *data) {
    Node *new_node = (Node*) malloc(sizeof(Node));
    new_node->data = *data;

    Node *prev = head;
    Node *cursor = head->next;
    while (cursor != NULL) {
        if (strcmp(new_node->data.title, cursor->data.title) < 0) break;
        prev = cursor;
        cursor = cursor->next;
    }
    prev->next = new_node;
    new_node->next = cursor;
}

// TODO: Simplify the print method
void delete_fn(Node *head, char *title) {
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
        printf("                                      PLAYLIST                                       \n");
        printf("==================================================================================== \n");
        printf(" No.         Title                  Artist            Volume          Preference     \n");
        printf("------------------------------------------------------------------------------------ \n");
        printf("#%2d  |%14s      |%14s      |     %5.2fMB     |     %5.2f \n", idx, cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        printf("------------------------------------------------------------------------------------ \n");
        free(cursor);
    } else printf("플레이리스트에 해당 음악(%s)이 없습니다. \n", title);
}

void show_fn(Node *head) {
    int count = 0;
    float storage = 0;
    Node *cursor = head->next;
    
    printf("                                      PLAYLIST                                       \n");
    printf("==================================================================================== \n");
    printf(" No.         Title                  Artist            Volume          Preference     \n");
    printf("------------------------------------------------------------------------------------ \n");
    if (cursor == NULL) printf("Empty Playlist! \n");
    while (cursor != NULL) {
        printf("#%2d  |%14s      |%14s      |     %5.2fMB     |     %5.2f \n", ++count, cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
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
