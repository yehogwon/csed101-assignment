#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

Node* load_playlist(char *filename);

int main(void) {
    char filename[100];
    Node *head = NULL;
    while (1) {
        printf("음악 리스트 파일 이름을 입력해주세요. >> ");
        scanf("%s", filename);
        if ((head = load_playlist(filename)) != NULL) break;
        printf("유효하지 않은 파일입니다. ");
    }

    show_fn(head);

    return 0;
}

Node* load_playlist(char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) return NULL;
    
    Node *head = (Node*) malloc(sizeof(Node));
    head->next = NULL;

    Node *cursor = head;
    Node *new_node = NULL;
    while (1) {
        Music music;
        if (fscanf(fp, "%s %s %f %f", music.title, music.artist, &music.size, &music.pref) == EOF) {
            free(new_node);
            break;
        }

        if (music.size > 50) {
            printf("용량 초과! 음악(%s)은 추가되지 않았습니다. \n", new_node->data.title);
            free(new_node);
            continue;
        }

        add_fn(head, &music);
    }
    fclose(fp);
    return head;
}
