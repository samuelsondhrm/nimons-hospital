#ifndef CHECKUP_H
#define CHECKUP_H

#define CAPACITY 100

#include "parser_user_csv.h"
#include "queue.h"
#include "room.h"
#include "map.h"         
#include "lihatuser.h"    

//linked list
typedef struct QueueNode {
    int pasienId;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} LinkedQueue;

extern int pasienAntri[CAPACITY];

void DaftarCheckUp(ListUser *listUser, Queue *antrianDokter, RumahSakit *rs, const char *username);

#endif