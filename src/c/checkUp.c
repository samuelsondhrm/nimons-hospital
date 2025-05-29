#include "../header/checkUp.h"

int pasienAntri[CAPACITY] = {0};

char to_upper(char c) {
    return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

// tampilkan dokter tersedia dari room.h
// loop seluruh ruangan di rumah sakit, jika id !- 0, cari dokter di ListUser, print
void tampilkanDokterTersedia(ListUser *listUser, RumahSakit *rs) {
    int counter = 1;
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            int id = rs->data[i][j].dokterId;
            if (id != 0) {
                for (int k = 0; k < listUser->jumlahuser; k++) {
                    if (listUser->users[k].id == id) {
                        //printf("%d. Dr. %s (Ruangan %c%d)\n", counter++, listUser->users[k].username, 'A' + i, j + 1);
                        break;
                    }
                }
            }
        }
    }
}

void DaftarCheckUp(ListUser *listUser, RumahSakit *rs, const char *username) {
    User *pasien = NULL;
    for (int i = 0; i < listUser->jumlahuser; i++) {
        if (strcmp(listUser->users[i].username, username) == 0) {
            pasien = &listUser->users[i];
            break;
        }
    }
    if (!pasien || pasienAntri[pasien->id]) { //apakah sudah terdaftar
        //printf("Anda sudah terdaftar dalam antrian check-up! Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.");
        return; 
    }
    // Input data medis
    do scanf("%f", &pasien->suhu_tubuh); while (pasien->suhu_tubuh < 32.0 || pasien->suhu_tubuh > 42.0);

    do scanf("%d %d", &pasien->tekanan_darah_sistolik, &pasien->tekanan_darah_diastolik);
    while (pasien->tekanan_darah_sistolik <= 80 || pasien->tekanan_darah_diastolik <= 50 || pasien->tekanan_darah_sistolik < pasien->tekanan_darah_diastolik);

    do scanf("%d", &pasien->detak_jantung); while (pasien->detak_jantung <= 60 || pasien->detak_jantung >= 160);

    do scanf("%f", &pasien->saturasi_oksigen); while (pasien->saturasi_oksigen < 80 || pasien->saturasi_oksigen > 100.0);

    do scanf("%d", &pasien->kadar_gula_darah); while (pasien->kadar_gula_darah <=70 || pasien->kadar_gula_darah >= 140);

    do scanf("%f", &pasien->berat_badan); while (pasien->berat_badan <= 10.0 || pasien->berat_badan >= 200.0);

    do scanf("%d", &pasien->tinggi_badan); while (pasien->tinggi_badan <= 50 || pasien->tinggi_badan >= 250);

    do scanf("%d", &pasien->kadar_kolesterol); while (pasien->kadar_kolesterol <= 100 || pasien->kadar_kolesterol >= 300);

    do scanf("%d", &pasien->kadar_kolesterol_ldl); while (pasien->kadar_kolesterol_ldl <= 50 || pasien->kadar_kolesterol_ldl >= 200);
    
    do scanf("%d", &pasien->trombosit); while (pasien->trombosit <= 100 || pasien->trombosit >= 500);

    // Tampilkan pilihan dokter (user.h & room.h)
    tampilkanDokterTersedia(listUser, rs);
    int pilihan;
    scanf("%d", &pilihan);


    // temukan ruangan sesuai pilihan
    // current adalah dokter yang dpilih, 
    int current = 1, dokterId = -1, rowRuangan = -1, colRuangan = -1; // inisialisasi belum ketemu
    for (int i = 0; i < rs->rows && dokterId == -1; i++) {
        for (int j = 0; j < rs->cols && dokterId == -1; j++) {
            if (rs->data[i][j].dokterId != 0) {
                if (current == pilihan) {
                     dokterId = rs->data[i][j].dokterId;
                     rowRuangan = i;
                     colRuangan = j;
                }
                current++;
              
            }
        }
    }

    Queue antrian = rs->data[rowRuangan][colRuangan].antrianPasienIds;
    if (lengthQueue(antrian) >= rs->kapasitasBaris) {
    // printf("Antrian untuk ruangan ini sudah penuh.\n");
        return;
    }

    if (dokterId != -1 && rowRuangan != -1 && colRuangan != -1) { // masuk antrian
        enqueue(&rs->data[rowRuangan][colRuangan].antrianPasienIds, pasien->id);
        //printf("Pasien berhasil masuk ke antrian check up.\n");
    } else { // tidak valid
        //printf("pilihan anda tidak valid");
        return;
    }
}
