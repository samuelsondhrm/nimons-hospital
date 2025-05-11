#ifndef LOGIN_H
#define LOGIN_H

#include "user.h"
#include "parser_user_csv.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Variabel global
extern User* current_user;
extern bool SudahLogin;
extern bool PasswordSalah;

// Deklarasi fungsi login
User* find_user_by_username(User users[], int count, const char* username);
bool login(User users[], int user_count);

#endif 