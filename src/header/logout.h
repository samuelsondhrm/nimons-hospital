#ifndef LOGOUT_H
#define LOGOUT_H

#include "login.h"

/*
Mengubah status login dan menghapus current_user aktif
*/

void logout(boolean *SudahLogin, User *current_user);

#endif