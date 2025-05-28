#include "checkUp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int pasienAntri[CAPACITY] = {0};

char to_upper(char c) {
    return (c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c;
}

// enqueue pasien
void EnqueueLinked(LinkedQueue *q, int pasienId) {
    QueueNode *newNode = (QueueNode *) malloc(sizeof(QueueNode));
    newNode->pasienId = pasienId;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

// tampilkan dokter tersedia
void tampilkanDokterTersedia(ListUser *listUser, RumahSakit *rs) {
    int counter = 1;
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            int id = rs->data[i][j].dokterId;
            if (id != 0) {
                for (int k = 0; k < listUser->jumlahuser; k++) {
                    if (listUser->users[k].id == id) {
                        break;
                    }
                }
            }
        }
    }
}

void DaftarCheckUp(ListUser *listUser, LinkedQueue *antrianDokter, RumahSakit *rs, const char *username) {
    User *pasien = NULL;
    for (int i = 0; i < listUser->jumlahuser; i++) {
        if (strcmp(listUser->users[i].username, username) == 0) {
            pasien = &listUser->users[i];
            break;
        }
    }
    if (!pasien || pasienAntri[pasien->id]) return;

    // Input data medis
    do scanf("%f", &pasien->suhu_tubuh); while (pasien->suhu_tubuh < 35.0 || pasien->suhu_tubuh > 42.0);

    do scanf("%d %d", &pasien->tekanan_darah_sistolik, &pasien->tekanan_darah_diastolik);
    while (pasien->tekanan_darah_sistolik <= 70 || pasien->tekanan_darah_diastolik <= 40 || pasien->tekanan_darah_sistolik < pasien->tekanan_darah_diastolik);

    do scanf("%d", &pasien->detak_jantung); while (pasien->detak_jantung <= 40 || pasien->detak_jantung >= 150);

    do scanf("%f", &pasien->saturasi_oksigen); while (pasien->saturasi_oksigen < 75.0 || pasien->saturasi_oksigen > 100.0);

    do scanf("%d", &pasien->kadar_gula_darah); while (pasien->kadar_gula_darah <= 50 || pasien->kadar_gula_darah >= 300);

    do scanf("%f", &pasien->berat_badan); while (pasien->berat_badan <= 10.0 || pasien->berat_badan >= 200.0);

    do scanf("%d", &pasien->tinggi_badan); while (pasien->tinggi_badan <= 80 || pasien->tinggi_badan >= 250);

    do scanf("%d", &pasien->kadar_kolesterol); while (pasien->kadar_kolesterol <= 100 || pasien->kadar_kolesterol >= 300);

    do scanf("%d", &pasien->kadar_kolesterol_ldl); while (pasien->kadar_kolesterol_ldl <= 50 || pasien->kadar_kolesterol_ldl >= 200);
    
    do scanf("%d", &pasien->trombosit); while (pasien->trombosit <= 100 || pasien->trombosit >= 500);

    // Tampilkan pilihan dokter
    tampilkanDokterTersedia(listUser, rs);
    int pilihan;
    scanf("%d", &pilihan);

    int current = 1, dokterId = -1;
    for (int i = 0; i < rs->rows && dokterId == -1; i++) {
        for (int j = 0; j < rs->cols && dokterId == -1; j++) {
            if (rs->data[i][j].dokterId != 0 && current++ == pilihan) {
                dokterId = rs->data[i][j].dokterId;
            }
        }
    }

    if (dokterId != -1) { // masuk antrian
        EnqueueLinked(&antrianDokter[dokterId], pasien->id);
        pasienAntri[pasien->id] = 1;
    } else { // tidak valid
        return;
    }
}
