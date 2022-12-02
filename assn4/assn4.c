#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

Node* load_playlist(char *filename);
void save_playlist(char *filename, Node* head);
void free_playlist(Node* head);

void add_music(Node *head);

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

        } else if (strcmp(command, "add") == 0) {
            add_music(head);
        } else if (strcmp(command, "delete") == 0) {

        } else if (strcmp(command, "exit") == 0) {
            // TODO: Move this menu to functions.c
            printf("저장할 파일명을 입력해주세요. >> ");
            scanf("%s", filename);
            save_playlist(filename, head);
            free_playlist(head);
            printf("프로그램을 종료합니다. \n");
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

void save_playlist(char *filename, Node* head) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) return;

    Node *cursor = head->next;
    while (cursor != NULL) {
        fprintf(fp, "%s\t%s\t%.6f\t%.6f\n", cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        cursor = cursor->next;
    }
    fclose(fp);
}

void free_playlist(Node* head) {
    Node *cursor = head;
    while (cursor != NULL) {
        Node *temp = cursor;
        cursor = cursor->next;
        free(temp);
    }
}

void add_music(Node *head) {
    Music music;
    printf("추가할 음악의 타이틀을 입력해주세요. >> "); scanf("%s", music.title);
    printf("추가할 음악의 아티스트를 입력해주세요. >> "); scanf("%s", music.artist);
    printf("추가할 음악의 용량을 입력해주세요. >> "); scanf("%f", &music.size);
    printf("추가할 음악의 선호도를 입력해주세요. >> "); scanf("%f", &music.pref);
    
    Node *cursor = head;
    while (cursor != NULL) {
        if (strcmp(cursor->data.title, music.title) == 0) {
            printf("해당 음악이 이미 플레이리스트 내에 존재합니다. \n");
            return;
        }
        cursor = cursor->next;
    }
    add_fn(head, &music);
}
