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

void show_fn(Node *head) {
    // TODO: Format the output
    Node *cursor = head->next;
    while (cursor != NULL) {
        printf("%s %s %.1fMB %.1f\n", cursor->data.title, cursor->data.artist, cursor->data.size, cursor->data.pref);
        cursor = cursor->next;
    }
}
