#include "../header/antrianSaya.h"

void antrianSaya(User current_user, RumahSakit rs) {

    int found = 0;

    for (int i = 0; i < rs.rows; i++) {
        for (int j = 0; j < rs.cols; j++) {
            Ruangan ruang = rs.data[i][j];
            Queue q = ruang.antrianPasienIds;
            int len = lengthQueue(q);

            for (int k = 0; k < len; k++) {
                int idx = (q.idxHead + k) % CAPACITY_QUEUE;
                int pasienId = q.buffer[idx];

                if (pasienId == current_user.id) {
                    found = 1;
                    if (k < rs.kapasitasPerRuangan) {
                        printf("Anda sedang berada di dalam ruangan dokter!\n");
                    } 
                    
                    else {
                        printf("Status antrian Anda:\n");
                        printf("Dokter: ID %d\n", ruang.dokterId);
                        printf("Ruangan: %c%d\n", 'A' + i, j + 1);
                        printf("Posisi antrian: %d dari %d\n", k + 1, len);
                    }
                    return;
                }
            }
        }
    }

    if (!found) {
        printf("Anda belum terdaftar dalam antrian check-up!\n");
        printf("Silakan daftar terlebih dahulu dengan command DAFTAR_CHECKUP.\n");
    }
}
