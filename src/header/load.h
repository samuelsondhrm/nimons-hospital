#ifndef LOAD_H
#define LOAD_H

#include "ADT/user.h"
#include "csv_parser.h"
#include "parser_config_txt.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Validasi folder
int validate_folder(const char *path);

// Validasi keberadaan akun manajer
void check_manager_account(ListUser *listUser);

// Prosedur utama untuk load data
void load_data(const char *folder_name, ListUser *listUser, RumahSakit *rs, Pasien pasienData[]);

#endif