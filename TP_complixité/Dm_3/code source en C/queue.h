#include "BTree.h"

typedef struct _queue_element
{
    Node* content;
    struct _queue_element *next;
} queue_element;


typedef struct
{
    queue_element *head, *tail;
    unsigned nb_values;
} queue;



queue *queue_new(void);
void queue_free(queue *);
void queue_send(queue *, Node* p);
Node* queue_receive(queue *);
void *queue_front(queue *);
unsigned queue_size(queue *);
int queue_is_empty(queue *);