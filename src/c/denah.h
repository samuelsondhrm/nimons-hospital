#ifndef DENAH_H
#define DENAH_H

#include "../header/room.h"
#include "../header/user.h"

void printDenah(const RumahSakit* rs);
/**
 * Prosedur untuk menampilkan denah rumah sakit
 **/

 void lihatRuangan(RumahSakit rs, char* kode, ListUser lUser);
/**
 * Prosedur untuk melihat detail isi ruangan di rumah sakit
 * @param rs Rumah Sakit yang dipanggil
 * @param kode Kode kamar yang diakses
 * @param lUser Berisi memori user apa aja yang ada di rumah sakit
 **/

#endif