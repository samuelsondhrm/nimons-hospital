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
int folder_exist(const char *path);

// Validasi keberadaan akun manajer
int load_data(const char *folder, ListUser *listUser, ListObat *listObat, ListPenyakit *listPenyakit, ListFormula *listFormula);

// Prosedur utama untuk load data


#endif