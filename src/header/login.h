#ifndef LOGIN_H
#define LOGIN_H

#include "ADT/user.h"
#include "ADT/set.h"
#include "csv_parser.h"


// Variabel global
User *current_user = NULL;  
boolean SudahLogin = false;  
boolean PasswordSalah = false; 

// Deklarasi fungsi login
void login(ListUser *users, User *current_user);

#endif 
