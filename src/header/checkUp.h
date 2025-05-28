#ifndef CHECKUP_H
#define CHECKUP_H

#include "user.h"
#include "room.h"

#define CAPACITY 100

// node link queue
typedef struct QueueNode {
    int pasienId;
    struct QueueNode* next;
} QueueNode;

// Struktur antrian pasien per dokter
typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} LinkedQueue;

// apakah pasien masuk antrian
extern int pasienAntri[CAPACITY];

void DaftarCheckUp(ListUser *listUser, LinkedQueue *antrianDokter, RumahSakit *rs, const char *username);
void EnqueueLinked(LinkedQueue *q, int pasienId);

#endif