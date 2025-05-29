#ifndef MINUMOBAT_H
#define MINUMOBAT_H

#include "ADT/room.h"
#include "ADT/user.h"
#include "ADT/penyakit_dan_obat.h"
#include "ADT/stack.h"

/*
 Memungkinkan pasien untuk meminum obat dari inventorynya.
 - Obat yang dipilih akan masuk ke dalam stack perut pasien.
 - Inventory akan berkurang sesuai pilihan pasien.
*/

void minumObat(User current_user, Inventory *inv, RumahSakit *rs, ListObat *lObat);

#endif
