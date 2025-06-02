#include "../header/checkUp.h"

LinkedList pasienCheckUpList;

char to_upper(char c) {
    return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

boolean isPasienSudahAntri(Queue q, int pasienId) {
    for (int i = 0, idx = q.idxHead; i < lengthQueue(q); i++, idx = (idx + 1) % CAPACITY_QUEUE) {
        if (q.buffer[idx] == pasienId) return true;
    }
    return false;
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
                        printf("%d. Dr. %s (Ruangan %c%d)\n", counter++, listUser->users[k].username, 'A' + i, j + 1);
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

    if(!pasien || strcmp(pasien->role,"pasien") != 0) { 
        printf("Hanya pasien yang bisa melakukan pendaftaran checkup");
        return;
    }

    // Input data medis
    printf("Masukkan suhu tubuh (32.0 - 42.0): ");
    while (scanf("%f", &pasien->suhu_tubuh) != 1 || pasien->suhu_tubuh < 32.0 || pasien->suhu_tubuh > 42.0) {
        printf("Suhu tidak valid. Masukkan ulang: ");
        while (getchar() != '\n');
    }

    printf("Masukkan tekanan darah (sistolik diastolik): ");
    while (scanf("%d %d", &pasien->tekanan_darah_sistolik, &pasien->tekanan_darah_diastolik) != 2 ||
        pasien->tekanan_darah_sistolik <= 80 ||
        pasien->tekanan_darah_diastolik <= 50 ||
        pasien->tekanan_darah_sistolik < pasien->tekanan_darah_diastolik) {
        printf("Tekanan darah tidak valid. Masukkan ulang (sistolik diastolik): ");
        while (getchar() != '\n');
    }

    printf("Masukkan detak jantung (61 - 159): ");
    while (scanf("%d", &pasien->detak_jantung) != 1 || pasien->detak_jantung <= 60 || pasien->detak_jantung >= 160) {
        printf("Detak jantung tidak valid. Masukkan ulang: ");
        while (getchar() != '\n');
    }

    printf("Masukkan saturasi oksigen (80.0 - 100.0): ");
    while (scanf("%f", &pasien->saturasi_oksigen) != 1 || pasien->saturasi_oksigen < 80.0 || pasien->saturasi_oksigen > 100.0) {
        printf("Saturasi oksigen tidak valid. Masukkan ulang: ");
        while (getchar() != '\n');
    }

    printf("Masukkan kadar gula darah (71 - 139): ");
    while (scanf("%d", &pasien->kadar_gula_darah) != 1 || pasien->kadar_gula_darah <= 70 || pasien->kadar_gula_darah >= 140) {
        printf("Kadar gula tidak valid. Masukkan ulang: ");
     while (getchar() != '\n');
    }

    printf("Masukkan berat badan (11.0 - 199.0): ");
    while (scanf("%f", &pasien->berat_badan) != 1 || pasien->berat_badan <= 10.0 || pasien->berat_badan >= 200.0) {
        printf("Berat badan tidak valid. Masukkan ulang: ");
        while (getchar() != '\n');
    }

    printf("Masukkan tinggi badan (51 - 249): ");
    while (scanf("%d", &pasien->tinggi_badan) != 1 || pasien->tinggi_badan <= 50 || pasien->tinggi_badan >= 250) {
        printf("Tinggi badan tidak valid. Masukkan ulang: ");
        while (getchar() != '\n');
    }

    printf("Masukkan kadar kolesterol (101 - 299): ");
    while (scanf("%d", &pasien->kadar_kolesterol) != 1 || pasien->kadar_kolesterol <= 100 || pasien->kadar_kolesterol >= 300) {
        printf("Kolesterol tidak valid. Masukkan ulang: ");
        while (getchar() != '\n');
    }

    printf("Masukkan kadar trombosit (101 - 499): ");
    while (scanf("%d", &pasien->trombosit) != 1 || pasien->trombosit <= 100 || pasien->trombosit >= 500) {
        printf("Trombosit tidak valid. Masukkan ulang: ");
        while (getchar() != '\n');
    }

    // Tampilkan pilihan dokter (user.h & room.h)
      tampilkanDokterTersedia(listUser, rs);
    printf("pilih dokter yang tersedia: \n");
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

    Queue *antrian = &rs->data[rowRuangan][colRuangan].antrianPasienIds;
    if (isPasienSudahAntri(*antrian, pasien->id)) {
    printf("Anda sudah terdaftar dalam antrian check-up! Silakan selesaikan check-up yang sudah terdaftar terlebih dahulu.\n");
    return;
    }
    if (lengthQueue(*antrian) >= rs->kapasitasBaris) {
     printf("Antrian untuk ruangan ini sudah penuh.\n");
        return;
    }

    if (dokterId != -1 && rowRuangan != -1 && colRuangan != -1) {
    enqueue(&rs->data[rowRuangan][colRuangan].antrianPasienIds, pasien->id);
    insertAtTail(&pasienCheckUpList, pasien->id); 

    int nomorAntrian = lengthQueue(rs->data[rowRuangan][colRuangan].antrianPasienIds); // nomor pasien sekarang

    printf("Pasien berhasil masuk ke antrian check up.\n");
    printf("Dokter: Dr. ");
    for (int i = 0; i < listUser->jumlahuser; i++) {
        if (listUser->users[i].id == dokterId) {
            printf("%s\n", listUser->users[i].username);
            break;
        }
    }

    printf("Nomor antrian Anda: %d\n", nomorAntrian);

    // Tampilkan seluruh antrian 
    printf("Daftar antrian saat ini:\n");
    int idx = antrian->idxHead;
    for (int i = 0; i < lengthQueue(*antrian); i++) {
        int pasienId = antrian->buffer[idx];
        for (int j = 0; j < listUser->jumlahuser; j++) {
            if (listUser->users[j].id == pasienId) {
                printf("%d. %s\n", i + 1, listUser->users[j].username);
                break;
            }
        }
        idx = (idx + 1) % CAPACITY_QUEUE;
    }
}