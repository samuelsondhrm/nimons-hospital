#include "checkUp.h"
#include <stdio.h>
#include <string.h>

// ctype manual
char to_upper(char c) {
    if (c >= 'a' && c <= 'z') return c - ('a' - 'A');
    return c;
}

int pasienAntri[CAPACITY] = {0}; 


void DaftarCheckUp(ListUser *listUser, Queue *antrianDokter, RumahSakit *rs, const char *username) {
    // 1. Cari pasien
    User *pasien = NULL;
    for (int i = 0; i < listUser->jumlahuser; i++) {
        if (strcmp(listUser->users[i].username, username) == 0) {
            pasien = &listUser->users[i];
            break;
        }
    }
    
    if (!pasien) { // validasi pasien
        return;
    }

     if (pasienAntri[pasien->id] == 1) { // cek apakah sudah antri
        return;

    // Input data medis
    scanf("%f", &pasien->suhu_tubuh);
    scanf("%d %d", &pasien->tekanan_darah_sistolik, &pasien->tekanan_darah_diastolik);
    scanf("%d", &pasien->detak_jantung);
    scanf("%f", &pasien->saturasi_oksigen);
    scanf("%d", &pasien->kadar_gula_darah);
    scanf("%f", &pasien->berat_badan);
    scanf("%d", &pasien->tinggi_badan);
    scanf("%d", &pasien->kadar_kolesterol);
    scanf("%d", &pasien->kadar_kolesterol_ldl);
    scanf("%d", &pasien->trombosit);

    // Pilih ruangan
    char ruangan[3];
    scanf("%s", ruangan);

    // Konversi huruf
    int baris = to_upper(ruangan[0]) - 'A';  
    int kolom = ruangan[1] - '1';

    //Tambah ke antrian dokter
    int dokterId = rs->data[baris][kolom].dokterId;
    enqueue(&antrianDokter[dokterId], pasien->id);
    pasienAntri[pasien->id] = 1; // sedang antri
}