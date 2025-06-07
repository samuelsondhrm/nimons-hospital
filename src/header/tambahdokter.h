#ifndef TAMBAHDOKTER_H
#define TAMBAHDOKTER_H

#include "ADT/room.h"
#include "ADT/user.h"
#include <stdio.h>
#include <string.h>

int idTerkecil(ListUser list);

void tambahDokter(ListUser *lUser);
/**
 * Prosedur untuk menambahkan dokter dan menyimpan di ListUser
 **/

 void assignDokter(RumahSakit *rs, ListUser *lUser);
/**
 * Prosedur meng-assign dokter tertentu ke ruangan di rumah sakit dengan pengecekan error
 **/

#endif