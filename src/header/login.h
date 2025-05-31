#ifndef LOGIN_H
#define LOGIN_H

#include "ADT/user.h"
#include "ADT/set.h"
#include "lupaPassword.h"


// Variabel global
extern User current_user; 
extern boolean SudahLogin; 

// Deklarasi fungsi login
void login(ListUser *users);
void lupaPassword(ListUser *LU);

#endif 
