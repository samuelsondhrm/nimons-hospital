#ifndef PULANGDOK_H
#define PULANGDOK_H

#include "ADT/user.h"
#include "ADT/penyakit_dan_obat.h"
#include "ADT/stack.h"
#include "ADT/queue.h"
#include "ADT/room.h"
#include "ADT/liststatik.h"
#include "diagnosis.h"

/*
Mengecek apakah pasien sudah bisa dipulangkan berdasarkan diagnosis dan urutan konsumsi obat.
Syarat:
- Sudah didiagnosis
- Semua obat sudah diminum (inventory kosong)
- Urutan peminuman obat sesuai dengan formula penyakit
 
Jika syarat dipenuhi:
- Pasien dikeluarkan dari ruangan
- Perut (stack) dan inventory direset
- Diagnosis diselesaikan
 
Jika tidak, akan menampilkan alasan dan saran sesuai spesifikasi.
*/

void bolehPulang(User current_user, Inventory *inv, const ListObat *lObat, const ListFormula *lFormula, const ListPenyakit *lPenyakit, RumahSakit *rs);

#endif