#include "../include/list.h"
#include "../include/patient.h"

typedef struct _node {
    PATIENT *patient;
    struct _node *next;
} NODE;

typedef struct _list {
    NODE *head;
    int size;
} LIST;
