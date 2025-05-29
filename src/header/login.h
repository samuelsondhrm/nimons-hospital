#ifndef LOGIN_H
#define LOGIN_H

#include "ADT/user.h"
#include "ADT/set.h"
#include "lupaPassword.h"


// Variabel global
User *current_user = NULL;  
boolean SudahLogin = false;  

// Deklarasi fungsi login
void login(ListUser *users, User *current_user);

#endif 
