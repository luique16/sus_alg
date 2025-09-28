#ifndef PATIENT_H
    #define PATIENT_H
    #include <stdbool.h>
    #include "history.h"

    typedef struct _patient PATIENT;

    PATIENT* init_patient();
    void set_patient_name(PATIENT *patient, char *name);
    void get_patient_name(PATIENT *patient, char *name);
    void get_patient_id(PATIENT *patient, int *id);
    HISTORY* get_patient_history(PATIENT *patient);
    void print_patient(PATIENT *patient);
    bool delete_patient(PATIENT *patient);
#endif
