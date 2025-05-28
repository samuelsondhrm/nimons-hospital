#ifndef LOGIN_H
#define LOGIN_H

#include "../header/user.h"
#include "../header/set.h"
#include "../header/csv_parser.h"


// Variabel global
extern User* current_user;
extern bool SudahLogin;
extern bool PasswordSalah;

// Deklarasi fungsi login
User* find_user_by_username(User users[], int count, const char* username);
bool login(User users[], int user_count);

#endif 
