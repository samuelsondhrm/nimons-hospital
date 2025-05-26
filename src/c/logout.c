#include "login.h"
#include "logout.h"

void logout() {
        if (SudahLogin) {
            printf("Sampai jumpa!\n");
            SudahLogin = false;
            current_user = NULL;
        }
        else {
            printf("Logout gagal!\n");
            printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        }  
    }

