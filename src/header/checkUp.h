#ifndef CHECKUP_H
#define CHECKUP_H

#include "ADT/user.h"
#include "ADT/room.h"
#include "ADT/linkedlist.h"

#define CAPACITY 100

// apakah pasien masuk antrian
extern int pasienAntri[CAPACITY];

void DaftarCheckUp(ListUser *listUser, RumahSakit *rs, const char *username);

#endif