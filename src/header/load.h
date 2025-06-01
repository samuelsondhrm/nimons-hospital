// filepath: c:\Users\Miguel\VSCODE\if1210-tubes-2025-k01-e-3\src\header\load.h
#ifndef LOAD_H
#define LOAD_H

#include "ADT/user.h"
#include "ADT/room.h"
#include "ADT/penyakit_dan_obat.h"
#include "parser_config_txt.h"
#include "csv_parser.h"

int load_data(const char *folder, ListUser *listuser, ListObat *listobat, 
              ListPenyakit *listpenyakit, ListFormula *listformula, 
              RumahSakit *rs, Inventory *inventory);
              
int file_exists(const char *filename);

#endif