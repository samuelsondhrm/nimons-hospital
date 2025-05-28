#ifndef LOGIN_H
#define LOGIN_H

#include "ADT/user.h"
#include "ADT/set.h"
#include "csv_parser.h"


// Variabel global
extern User* current_user;
boolean SudahLogin;
boolean PasswordSalah;

// Deklarasi fungsi login
User* find_user_by_username(User users[], int count, const char* username);
boolean login(User users[], int user_count);

#endif 
