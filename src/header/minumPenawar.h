#ifndef MINUMPENAWAR_H
#define MINUMPENAWAR_H

#include <stdio.h>
#include "../src/header/ADT/penyakit_dan_obat.h"  
#include "../src/header/ADT/room.h"               
#include "../src/header/ADT/stack.h"             

Pasien* cariPasienById(Inventory *inv, int userId);

void minumPenawar(int userId, ListObat *lObat, Inventory *inv);

#endif
