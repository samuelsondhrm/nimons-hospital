#include <stdio.h>
#include "login.h"

int main() {
    char instruksi[MAX_FIELD];

    printf(">>> ");
    scanf("%s", instruksi);

    if (strcmp(instruksi, "LOGOUT") == 0) { 
        if (SudahLogin) {
            printf("Sampai jumpa!\n");
        }
        else {
            printf("Logout gagal!\n");
            printf("Anda belum login, silahkan login terlebih dahulu sebelum melakukan logout\n");
        }  
    }

    return 0;
}

