#include "../include/list.h"
#include "../include/patient.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _node {
    PATIENT *patient;
    struct _node *next;
    struct _node *prev;
} NODE;

typedef struct _list {
    NODE *head;
    NODE *end;
    int size;
} LIST;

//Vamos fazer uma lista duplamente encadeada e nao ordenada

LIST* init_list(){
    LIST* l = (LIST *) calloc(1, sizeof(LIST));
    l->head = NULL;
    l->end = NULL;
    l->size = 0;

    return l;
}


bool is_list_empty(LIST *list){
    if(list->head != NULL){
        return false;
    }else{
        return true;
    }
}

int get_list_size(LIST *list){
    return list->size;
}

void add_patient(LIST *list, PATIENT *patient){
    NODE *n = (NODE*) calloc(1, sizeof(NODE));
    n->next = NULL;
    n->patient = patient;

    if(is_list_empty(list) == false){
        list->head = n;
        n->prev = NULL;
        list->end = n;
    }else {
        list->end->next = n;
        n->prev = list->end;
    }
}

PATIENT* get_patient_by_id(LIST *list, int patient_id){
    NODE *p = list->head;

    for(int i = 0; i < list->size; i++){
        if(p == NULL){
            return NULL;
        }

        if(get_patient_id(p->patient) == patient_id){
            return p->patient;
        }

        p = p->next;
    }

    return NULL;
}

PATIENT* get_patient_by_name(LIST *list, char *name){
    NODE *p = list->head;

    for(int i = 0; i < list->size; i++){
        if(p == NULL){
            return NULL;
        }

        if(strcmp(get_patient_name(p->patient), name) == 0){
            return p->patient;
        }

        p = p->next;
    }

    return NULL;
}

void remove_patient(LIST *list, int patient_id){
    NODE* p = list->head;

    for(int i = 0; i < list->size; i++){
        if(p == NULL){
            return;
        }

        if(get_patient_id(p->patient) == patient_id){
            break;
        }

        p = p->next;
    }

    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->next = NULL;
    p->prev = NULL;
    free(p);
}

void print_list(LIST *list){
    NODE *p = list->head;

    for(int i = 0; i < list->size; i++){
        printf("[id: %d] %s\n", get_patient_id(p->patient), get_patient_name(p->patient));
        p = p->next;
    }
}

bool delete_list(LIST **list){
    NODE *p1 = (*list)->head;
    NODE *p2 = (*list)->head->next;

    for(int i = 0; i < (*list)->size; i++){
        if(p1 == NULL){
            break;
        }

        free(p1);
        p1 = p2;
        p2 = p2->next;
    }

    free(p1);
    free(p2);
    free(*list);
    *list = NULL;

    return true;
}
