#include <stdio.h>
#include <string.h>

#include "../include/io.h"
#include "../include/list.h"
#include "../include/queue.h"
#include "../include/patient.h"
#include "../include/history.h"

#define MAX_LINE_SIZE 1000

void skip_line(FILE *file) {
    char line[MAX_LINE_SIZE];
    fgets(line, MAX_LINE_SIZE, file);
}

bool save(LIST *list, QUEUE *queue, char *list_filename, char *queue_filename) {
    FILE *list_file = fopen(list_filename, "w");

    if(is_list_empty(list)){
        fprintf(list_file, "[]\n");
    } else {
        fprintf(list_file, "[");

        int size = get_list_size(list);
        for (int i = 0; i < size; i++) {
            int id = get_last_patients_id(list);
            PATIENT *patient = get_patient_by_id(list, id);

            char* name = get_patient_name(patient);;

            fprintf(list_file, "\n  {\n");
            fprintf(list_file, "    \"id\": %d,\n", get_patient_id(patient));
            fprintf(list_file, "    \"name\": \"%s\",\n", name);
            fprintf(list_file, "    \"history\": \"%s\"\n", save_history(get_patient_history(patient)));
            fprintf(list_file, "  }");


            if (i < get_list_size(list) - 1) {
                fprintf(list_file, ",");
            }

            remove_patient(list, id);
        }

        fprintf(list_file, "\n]\n");
    }

    fclose(list_file);

    FILE *queue_file = fopen(queue_filename, "w");

    if(is_queue_empty(queue)){
        fprintf(queue_file, "[]\n");
    } else {
        fprintf(queue_file, "[\n");

        for (int i = 0; i < get_queue_size(queue); i++) {
            PATIENT *patient = dequeue(queue);

            fprintf(queue_file, "  %d", get_patient_id(patient));

            if (i < get_queue_size(queue) - 1) {
                fprintf(queue_file, ",");
            }
        }

        fprintf(queue_file, "\n]\n");
    }

    fclose(queue_file);

    return true;
}

bool load(LIST **list, QUEUE **queue, char *list_filename, char *queue_filename) {
    // Load list
    FILE *list_file = fopen(list_filename, "r");

    if (list_file == NULL) {
        printf("Error: list file not found\n");
        return false;
    }

    bool complete = false;

    char line[MAX_LINE_SIZE];

    fgets(line, MAX_LINE_SIZE, list_file);

    if (strncmp(line, "[]", 2) == 0)
        complete = true;

    while (!complete) {
        printf("uee\n");
        skip_line(list_file);

        int id;
        char name[MAX_LINE_SIZE];
        char history[MAX_LINE_SIZE];

        for (int i = 0; i < 3; i++) {
            char field[10];

            fgets(line, MAX_LINE_SIZE, list_file);
            sscanf(line, "  \"%[^\"]\": ", field);

            if (strcmp(field, "id") == 0) {
                sscanf(line, "  \"id\": %d,", &id);
            } else if (strcmp(field, "name") == 0) {
                sscanf(line, "  \"name\": \"%[^\"]\",", name);
            } else if (strcmp(field, "history") == 0) {
                sscanf(line, "  \"history\": \"%[^\"]\",", history);
            }
        }

        HISTORY *history_struct = init_history();
        load_history(history_struct, history);

        PATIENT *patient = init_patient();
        set_patient_history(patient, history_struct);
        set_patient_id(patient, id);
        set_patient_name(patient, name);

        add_patient(*list, patient);

        fgets(line, MAX_LINE_SIZE, list_file);
        bool end = true;

        for(int i = 0; i < strlen(line); i += 1) {
            if(line[i] == '}') {
                if(line[i + 1] == ',') {
                    end = false;
                }
                break;
            }
        }

        if (end) {
            complete = true;
        }
    }

    fclose(list_file);

    // Load queue
    FILE *queue_file = fopen(queue_filename, "r");

    if (queue_file == NULL) {
        printf("Error: queue file not found\n");
        return false;
    }

    complete = false;

    fgets(line, MAX_LINE_SIZE, queue_file);

    if (strcmp(line, "[]\n") == 0) {
        complete = true;
    }

    while (!complete) {
        int id;

        fgets(line, 100, queue_file);

        if (strncmp(line, "]", 2) == 0 || strcmp(line, "]") == 0) {
            complete = true;
            break;
        }

        sscanf(line, "  %d,", &id);

        PATIENT *patient = get_patient_by_id(*list, id);
        if (patient != NULL) {
            enqueue(*queue, patient);
        }
    }

    fclose(queue_file);

    return true;
}
