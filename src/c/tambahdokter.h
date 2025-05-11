#ifndef TAMBAHDOKTER_H
#define TAMBAHDOKTER_H

#include "../header/room.h"
#include "../header/user.h"

void tambahDokter(ListUser *lUser);
/**
 * Prosedur untuk menambahkan dokter dan menyimpan di ListUser
 **/

 void assignDokter(RumahSakit *rs, ListUser *lUser);
/**
 * Prosedur meng-assign dokter tertentu ke ruangan di rumah sakit dengan pengecekan error
 **/

#endif