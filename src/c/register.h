#ifndef REGISTER_H
#define REGISTER_H

#include "../header/user.h"
#include "../header/set.h"
#include "../header/parser_user_csv.h"  // tulis user csv
#include <stdbool.h>

#define MAX_FIELD 128

bool is_username_valid(const char* username);
void register_pasien(ListUser *ListUser, const char* filename); 

#endif