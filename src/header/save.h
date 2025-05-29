#ifndef SAVE_H
#define SAVE_H

#include "../header/csv_parser.h"
#include "../header/parser_config_txt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
// Membuat folder secara rekursif
int create_directory_recursive(const char *path);

// Mengecek apakah folder ada
int folder_exists(const char *path);

// Prosedur utama save
void save_data(ListUser listUser, RumahSakit rs, Pasien pasienData[]);

#endif