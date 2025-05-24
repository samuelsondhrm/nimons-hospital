#ifndef CHECKUP_H
#define CHECKUP_H

#include "parser_user_csv.h"  
#include "queue.h"            
#include "room.h"             

void DaftarCheckUp(ListUser *listUser, Queue *antrianDokter, RumahSakit *rs, const char *username);

#endif