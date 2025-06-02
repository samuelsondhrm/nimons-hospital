#ifndef DENAH_H
#define DENAH_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ADT/room.h"
#include "ADT/user.h"

void printDenah(const RumahSakit rs);
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