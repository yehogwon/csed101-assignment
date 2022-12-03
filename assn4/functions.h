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

float crit_title(Music *a, Music *b);
float crit_pref(Music *a, Music *b);

void show_fn(Node *head, char *header);
int show_favorites_fn(Node *head, int n);
void add_fn(Node *head, Music *data, float (*criterion)(Music *, Music *));
int delete_fn(Node *head, char *title);
void exit_fn(Node *head, char *filename);

#endif