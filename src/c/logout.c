#include "logout.h"

void logout(boolean *SudahLogin, User *current_user) {
    if (*SudahLogin) {
        printf("Sampai jumpa!\n");
        *SudahLogin = false;
        CreateUser(current_user);
    } else {
        printf("Logout gagal!\n");
        printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
    }
}