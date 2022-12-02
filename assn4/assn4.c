// NOTE: DO NOT USE ANY OF THE FUNCTIONS IN THE STRING.H LIBRARY
#include <stdio.h>
#include <stdlib.h>
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
        new_node = (Node*)malloc(sizeof(Node));
        if (fscanf(fp, "%s %s %f %f", new_node->data.title, new_node->data.artist, &new_node->data.size, &new_node->data.pref) == EOF) {
            free(new_node);
            break;
        }
        cursor->next = new_node;
        cursor = new_node;
    }
    fclose(fp);
    return head;
}
