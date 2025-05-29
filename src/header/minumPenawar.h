#ifndef MINUMPENAWAR_H
#define MINUMPENAWAR_H

#include "ADT/room.h"
#include "ADT/user.h"
#include "ADT/stack.h"
#include "ADT/penyakit_dan_obat.h"      

/*
 Mengeluarkan obat terakhir yang diminum (dari stack perut), dan mengembalikannya ke inventory pasien.
 - Jika perut kosong, tampilkan pesan kesalahan.
*/
void minumPenawar(User current_user, Inventory *inv, const ListObat *lObat);

#endif