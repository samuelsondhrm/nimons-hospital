#ifndef SAVE_H
#define SAVE_H

#include "ADT/user.h"

#include <sys/stat.h>

// Fungsi utama untuk save data
void save_data(ListUser listUser, RumahSakit rs, Pasien pasienData[]);
// Fungsi rekursif untuk membuat direktori
int create_directory_recursive(const char *path);

#endif