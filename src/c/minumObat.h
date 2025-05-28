#include <stdio.h>
#include "../header/ADT/stack.h"
#include "../header/ADT/room.h"
#include "../header/ADT/penyakit_dan_obat.h"  

Pasien* cariPasienById(Inventory *inv, int userId);

void minumObat(int userId, ListObat *lObat, Inventory *inv);
