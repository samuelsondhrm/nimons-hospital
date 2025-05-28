#include <stdio.h>
#include "antrianSaya.h"
#include "checkUp.h"

void AntrianSaya(ListUser *listUser, Queue *antrianDokter, RumahSakit rs, const char *username) {
    User *pasien = NULL;
    for (int i = 0; i < listUser->jumlahuser; i++) {
        if (strcmp(listUser->users[i].username, username) == 0) {
            pasien = &listUser->users[i];
            break;
        }
    }

    if (!pasien) {
        return;
    }

    if (!pasienAntri[pasien->id]) {
        printf("Anda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
        return;
    }

    for (int i = 0; i < rs.rows; i++) {
        for (int j = 0; j < rs.cols; j++) {
            int dokterId = rs.data[i][j].dokterId;
            Queue q = antrianDokter[dokterId];
            int len = length(q);
            int idx = IDX_HEAD(q);

            for (int k = 0; k < len; k++) {
                if (q.buffer[idx] == pasien->id) {
                    printf("Status antrian Anda:\n");
                    printf("Dokter: %s\n", listUser->users[dokterId].username);
                    printf("Ruangan: %c%d\n", 'A' + i, j + 1);
                    printf("Posisi antrian: %d dari %d\n", k + 1, len);
                    return;
                }
                idx = (idx + 1) % CAPACITY;
            }
        }
    }
}
