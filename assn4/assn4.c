#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

Node* load_playlist(char *filename);
int add_music(Node *head);

int main(void) {
    char filename[35];
    Node *head = NULL;
    while (1) {
        printf("음악 리스트 파일 이름을 입력해주세요. >> ");
        scanf("%s", filename);
        if ((head = load_playlist(filename)) != NULL) break;
        printf("유효하지 않은 파일입니다. ");
    }

    char command[20];
    while (1) {
        printf("\n");
        printf("명령어를 입력해주세요. >> ");
        scanf("%s", command);

        if (strcmp(command, "show") == 0) {
            show_fn(head);
        } else if (strcmp(command, "show_favorites") == 0) {
            int n;
            printf("상위 몇 개의 음악을 추출할까요? >> "); scanf("%d", &n);
            if (show_favorites_fn(head, n) == -1) printf("추출하고자 하는 음악의 수가 전체 음악의 수보다 많습니다. \n");
        } else if (strcmp(command, "add") == 0) {
            if (add_music(head) == -1) printf("해당 음악이 이미 플레이리스트 내에 존재합니다. \n");
        } else if (strcmp(command, "delete") == 0) {
            char title[15];
            printf("삭제할 음악의 타이틀을 입력해주세요. >> "); scanf("%s", title);
            if (delete_fn(head, title) == -1) printf("플레이리스트에 해당 음악(%s)이 없습니다. \n", title);
        } else if (strcmp(command, "exit") == 0) {
            printf("저장할 파일명을 입력해주세요. >> ");
            scanf("%s", filename);
            exit_fn(head, filename);
            break;
        } else {
            printf("유효하지 않은 명령어입니다. \n");
        }
    }

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

int add_music(Node *head) {
    Music music;
    printf("추가할 음악의 타이틀을 입력해주세요. >> "); scanf("%s", music.title);
    printf("추가할 음악의 아티스트를 입력해주세요. >> "); scanf("%s", music.artist);
    printf("추가할 음악의 용량을 입력해주세요. >> "); scanf("%f", &music.size);
    printf("추가할 음악의 선호도를 입력해주세요. >> "); scanf("%f", &music.pref);
    
    Node *cursor = head;
    while (cursor != NULL) {
        if (strcmp(cursor->data.title, music.title) == 0) return -1;
        cursor = cursor->next;
    }
    add_fn(head, &music);
    return 0;
}
