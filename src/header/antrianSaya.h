#ifndef ANTRIANSAYA_H
#define ANTRIANSAYA_H

#include "ADT/room.h"
#include "ADT/user.h"

/* 
Menampilkan status antrian pasien saat ini.
 - Jika pasien sudah masuk ruangan (berada dalam kapasitas ruangan), akan ditampilkan pesan sedang berada di ruangan.
 - Jika pasien masih dalam antrian luar, akan ditampilkan informasi antrian.
 - Jika pasien tidak ditemukan dalam antrian manapun, akan diberi tahu untuk daftar check-up terlebih dahulu.
 */

void antrianSaya(User current_user, RumahSakit rs);

#endif
