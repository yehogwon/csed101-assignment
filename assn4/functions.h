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

void add_fn();
void delete_fn();
void show_fn();
void show_favorites_fn();
void exit_fn();
