#ifndef CHECKUP_H
#define CHECKUP_H

#define CAPACITY 100

#include "parser_user_csv.h"  
#include "queue.h"            
#include "room.h"   

extern int pasienAntri[CAPACITY];

void DaftarCheckUp(ListUser *listUser, Queue *antrianDokter, RumahSakit *rs, const char *username);

#endif