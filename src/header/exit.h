#ifndef EXIT_H
#define EXIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/save.h"
#include "../header/ADT/user.h"



void exitProgram(ListUser listUser, RumahSakit rs, Pasien pasienData[]);
// Prosedur untuk keluar dari program, dengan opsi untuk menyimpan data yang telah diubah

void save_data(ListUser listUser, RumahSakit rs, Pasien pasienData[]);
// Prosedur untuk menyimpan data ke dalam file

#endif