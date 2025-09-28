#include "../include/history.h"

#define DEFAULT_MAX_SIZE 10

typedef struct _history {
    char procedures[DEFAULT_MAX_SIZE];
    int size;
} HISTORY;
