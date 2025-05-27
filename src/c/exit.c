#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"



void saveuToCSV(User u[], int count) {
    FILE *file = fopen("user.csv", "w");
    
    fprintf(file, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;kadar_kolesterol_ldl;trombosit\n");


    for (int i = 0; i < count; i++) {
        fprintf(file, "%d;%s;%s;%s;%s;%.1f;%d;%d;%d;%.1f;%d;%.1f;%d;%d;%d;%d\n",
                u[i].id,
                u[i].username,
                u[i].password,
                u[i].role,
                u[i].riwayat_penyakit,
                u[i].suhu_tubuh,
                u[i].tekanan_darah_sistolik,
                u[i].tekanan_darah_diastolik,
                u[i].detak_jantung,
                u[i].saturasi_oksigen,
                u[i].kadar_gula_darah,
                u[i].berat_badan,
                u[i].tinggi_badan,
                u[i].kadar_kolesterol,
                u[i].kadar_kolesterol_ldl,
                u[i].trombosit);
    }

    fclose(file);
}

char readExit(){
    int n;
    scanf("%s" , &n);
    while(n != 'n' || n != 'N' || n!='y' || n != 'Y'){
        scanf("%s" , &n);
    }
    return n;
}


void exit(User u[], int count,char n){
    n = readExit();
    if(n == 'n' || n =='N'){
        return;
        // lakukan procedure untuk keluar dari program utama
    }
    else if(n == 'Y' || n == 'y'){
        saveuToCSV(u,count);
        // lakukan procedure untuk keluar dari program utama
        return;

    }
}