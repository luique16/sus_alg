#define DEFAULT_MAX_SIZE 15

#include <stdio.h>
#include <stdlib.h>

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

QUEUE* init_queue(){
    QUEUE *queue = (QUEUE*) calloc(1, sizeof(QUEUE));
    queue->size = 0;
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

bool is_queue_empty(QUEUE *queue){
    if(queue->head == NULL){
        return false;
    }else{
        return true;
    }
}

bool enqueue(QUEUE *queue, PATIENT *patient){
    if(queue == NULL){
        return false;
    }

    NODE *n = (NODE*) calloc(1, sizeof(NODE));
    n->patient = patient;
    queue->size += 1;
    n->next = NULL;
    
    if(is_queue_empty(queue)){
        queue->head = n;
        n->prev = NULL;
    }else {
        n->prev = queue->tail;
    }
    queue->tail = n;
    
    return true;
}

int get_queue_size(QUEUE *queue){
    return queue->size;
}

PATIENT* dequeue(QUEUE *queue){
    NODE *n = queue->head;

    n->next->prev = NULL;
    queue->head = n->next;
    queue->size -= 1;
    free(n->next);

    return n->patient;
}
    
void print_queue(QUEUE *queue){
    NODE *p = queue->head;

    for(int i = 0; i < queue->size; i++){
        printf("%s\n", get_patient_name(p->patient));
        p = p->next;
        if(p == NULL){
            break;
        }
    }
}

bool is_queue_full(QUEUE *queue, unsigned int limit){
    if(queue->size >= limit){
        return true;
    }else{
        return false;
    }
}

void delete_queue(QUEUE **queue){
    NODE *p1 = (*queue)->head;
    NODE *p2 = (*queue)->head->next;

    for(int i = 0; i < (*queue)->size; i++){
        if(p1 == NULL){
            break;
        }

        free(p1->next);
        free(p1->prev);
        free(p1);
        p1 = p2;
        if(p2 != NULL){
            p2 = p2->next;
        }
    }

    free(p1);
    free(p2);
}
