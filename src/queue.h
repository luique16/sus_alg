#define DEFAULT_MAX_SIZE 15

#include "../include/queue.h"
#include "../include/patient.h"

typedef struct _node {
    PATIENT *patient;
    struct _node *next;
    struct _node *prev;
} NODE;

typedef struct _queue {
    NODE *head;
    NODE *tail;
    int size;
} QUEUE;
