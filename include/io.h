#ifndef IO_H
    #define IO_H

    #include "list.h"
    #include "queue.h"

    void save(LIST *list, QUEUE *queue, char *list_filename, char *queue_filename);
    void load(LIST **list, QUEUE **queue, char *list_filename, char *queue_filename);
#endif
