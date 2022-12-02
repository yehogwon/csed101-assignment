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
    int flag = 0, idx = 1;
    Node *prev = head;
    Node *cursor = head->next;
    while (cursor != NULL) {
        if (strcmp(cursor->data.title, title) == 0) {
            prev->next = cursor->next;
            flag = 1;
            break;
        }
        prev = cursor;
        cursor = cursor->next;
        idx++;
    }

    if (flag) {
        printf("                                      PLAYLIST                                       \n");
        printf("==================================================================================== \n");
        printf(" No.         Title                  Artist            Volume          Preference     \n");
        printf("------------------------------------------------------------------------------------ \n");
        printf("#%2d  |%14s      |%14s      |     %5.2fMB     |     %5.2f \n", idx, cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        printf("------------------------------------------------------------------------------------ \n");
        free(cursor);
    } else printf("플레이리스트에 해당 음악(검색한 타이틀명)이 없습니다. \n");
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
