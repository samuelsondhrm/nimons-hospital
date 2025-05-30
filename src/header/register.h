#ifndef REGISTER_H
#define REGISTER_H

#include "ADT/user.h"
#include "ADT/set.h"
#include "csv_parser.h"  


#define MAX_FIELD 128

boolean is_username_valid(const char* username);
void register_pasien(ListUser *lUser, User *new_user);

#endif