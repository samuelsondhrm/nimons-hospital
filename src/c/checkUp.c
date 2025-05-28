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
    }

    // Input data medis
    while (1) {
        scanf("%f", &pasien->suhu_tubuh);
        if (pasien->suhu_tubuh >= 35.0 && pasien->suhu_tubuh <= 42.0) break;
    }
    
    // Tekanan Darah
    while (1) {
        scanf("%d %d", &pasien->tekanan_darah_sistolik, &pasien->tekanan_darah_diastolik);
        if (pasien->tekanan_darah_sistolik > 70 && pasien->tekanan_darah_diastolik > 40 &&
            pasien->tekanan_darah_sistolik >= pasien->tekanan_darah_diastolik) break;
    }
    
    // Detak Jantung
    while (1) {
        scanf("%d", &pasien->detak_jantung);
        if (pasien->detak_jantung > 40 && pasien->detak_jantung < 150) break;
    }
    
    // Saturasi Oksigen
    while (1) {
        scanf("%f", &pasien->saturasi_oksigen);
        if (pasien->saturasi_oksigen >= 75.0 && pasien->saturasi_oksigen <= 100.0) break;
    }
    
    // Kadar Gula Darah
    while (1) {
        scanf("%d", &pasien->kadar_gula_darah);
        if (pasien->kadar_gula_darah > 50 && pasien->kadar_gula_darah < 300) break;
    }
    
    // Berat Badan
    while (1) {
        scanf("%f", &pasien->berat_badan);
        if (pasien->berat_badan > 10.0 && pasien->berat_badan < 200.0) break;
    }
    
    // Tinggi Badan
    while (1) {
        scanf("%d", &pasien->tinggi_badan);
        if (pasien->tinggi_badan > 80 && pasien->tinggi_badan < 250) break;
    }
    
    // Kadar Kolesterol
    while (1) {
        scanf("%d", &pasien->kadar_kolesterol);
        if (pasien->kadar_kolesterol > 100 && pasien->kadar_kolesterol < 300) break;
    }
    
    // Kadar Kolesterol LDL
    while (1) {
        scanf("%d", &pasien->kadar_kolesterol_ldl);
        if (pasien->kadar_kolesterol_ldl > 50 && pasien->kadar_kolesterol_ldl < 200) break;
    }
    
    // Trombosit
    while (1) {
        scanf("%d", &pasien->trombosit);
        if (pasien->trombosit > 100 && pasien->trombosit < 500) break;
    }

    void simpanDiagnosis(Map *diagnosisMap, int pasienId, const char *penyakit) {
        char key[10];
        sprintf(key, "%d", pasienId);
        InsertMap(diagnosisMap, key, penyakit);
    }

    void tampilkanDokterTersedia(ListUser *listUser, RumahSakit *rs) {
        int counter = 1;
        for (int i = 0; i < rs->rows; i++) {
            for (int j = 0; j < rs->cols; j++) {
                if (rs->data[i][j].dokterId != 0) {
                    User *dokter = getUserById(listUser, rs->data[i][j].dokterId);
                    if (dokter) {
                        char kodeRuangan[3];
                        sprintf(kodeRuangan, "%c%d", 'A' + i, j + 1);
                    }
                }
            }
        }
    }    

    tampilkanDokterTersedia(listUser, rs, antrianDokter);

    // Pilih dokter 
    int pilihDokter;
    scanf("%d", &pilihDokter);

    int current = 1;
    int dokterId = -1;
    char ruanganDipilih[3] = "";

    // cari dokter
    for (int i = 0; i < rs->rows && dokterId == -1; i++) {
        for (int j = 0; j < rs->cols && dokterId == -1; j++) {
            if (rs->data[i][j].dokterId != 0) {
                if (current == pilihan) {
                    dokterId = rs->data[i][j].dokterId;
                    sprintf(ruanganDipilih, "%c%d", 'A' + i, j + 1);
                }
                current++;
            }
        }
    }

    // [7] Validasi & tambah ke antrian
    if (dokterId != -1) {
        EnqueueLinked(&antrianDokter[dokterId], pasien->id);
        pasienAntri[pasien->id] = 1;
        return;

    } else {
        return;

    }
    
}