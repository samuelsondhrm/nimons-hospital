#ifndef REGISTER_H
#define REGISTER_H

#include "ADT/user.h"
#include "ADT/set.h"
#include "csv_parser.h"  


#define MAX_FIELD 128

void InsUser(ListUser *lUser, User userBaru);
int compare_case_insensitive(const char* a, const char* b);
boolean is_username_valid(const char* username);
void register_pasien(ListUser *lUser, User *new_user);

#endif