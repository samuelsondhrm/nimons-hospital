#ifndef LOGIN_H
#define LOGIN_H

#include "ADT/user.h"
#include "ADT/set.h"
#include "lupaPassword.h"

// Deklarasi fungsi login
void login(ListUser *users, User *current_user, boolean *SudahLogin);
void lupaPassword(ListUser *LU);

#endif 
