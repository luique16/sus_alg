#include "../include/history.h"
#include "../include/patient.h"

typedef struct _patient {
    int id;
    char *name;
    HISTORY *history;
} PATIENT;
