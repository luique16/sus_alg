#include "../include/history.h"
#include "../include/patient.h"

#include <string.h>

typedef struct _patient {
    int id;
    char *name;
    HISTORY *history;
} PATIENT;

PATIENT init_patient(){
    PATIENT *paciente = (PATIENT*) calloc(1, sizeof(PATIENT));
    return paciente;
}

void set_patient_name(PATIENT *patient, char *name){
    strcpy(patient.name, name);
}