#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct {
    char title[15];
    char artist[15];
    float size;
    float pref;
} Music;

typedef struct Node {
    Music data;
    struct Node *next;
} Node;

void add_fn(Node *head, Music *data);
void delete_fn(Node *head, char *title);
void show_fn(Node *head);
void show_favorites_fn();
void exit_fn();

#endif