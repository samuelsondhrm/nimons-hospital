#ifndef LOAD_H
#define LOAD_H

#include "ADT/user.h"
#include "../header/csv_parser.h"
#include "../header/parser_config_txt.h"
#include <dirent.h>
#include <sys/stat.h>

// Fungsi utama untuk load data
void load_data(const char *folder_name, ListUser *listUser, RumahSakit *rs, Pasien pasienData[]);

// Validasi folder dan file
int validate_folder(const char *path);
void check_manager_account(ListUser *listUser);

#endif