#ifndef REGISTER_H
#define REGISTER_H

#include "../header/user.h"
#include "../header/set.h"
#include "../header/csv_parser.h"  // tulis user csv


#define MAX_FIELD 128

boolean is_username_valid(const char* username);
void register_pasien(ListUser *ListUser, const char* filename); 

#endif