#include "help.h"
#include <stdio.h>


void templateHelp(User u){
    printf("=========== HELP ===========\n\n");

    if(u.role == "pasien"){
        helpPasien(u);
    }
    else if(u.role == "dokter"){
        helpDokter(u);
    }
    else if(u.role == "manager"){
        helpManager(u);
    }

    printf("Footnote:\n");
    printf("1. Untuk menggunakan aplikasi, silahkan masukkan nama fungsi yang terdaftar\n");
    printf("2. Jangan lupa untuk memasukkan input yang valid\n");
}
