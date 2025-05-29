#include "../header/lihatantrian.h"

void lihatSemuaAntrian(RumahSakit rs, ListUser lUser) {
    // Tampilkan denah terlebih dahulu
    printDenah(rs);

    // Iterasi tiap ruangan
    for (int i = 0; i < rs.rows; i++) {
        for (int j = 0; j < rs.cols; j++) {
            Ruangan r = rs.data[i][j];
            if (r.dokterId != 0) {  // Hanya tampilkan jika ada dokter
                // Cetak header
                printf("\n============ %c%d ============\n", 'A' + i, j + 1);
                printf("Kapasitas  : %d\n", rs.kapasitasPerRuangan);

                // Tampilkan nama dokter
                const char* namaDokter = "-";
                for (int u = 0; u < lUser.jumlahuser; u++) {
                    if (lUser.users[u].id == r.dokterId) {
                        namaDokter = lUser.users[u].username;
                        break;
                    }
                }
                printf("Dokter     : Dr. %s\n", namaDokter);

                // Tampilkan pasien dalam ruangan
                printf("Pasien di dalam ruangan:\n");
                if (r.jumlahPasien == 0) {
                    printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
                } else {
                    for (int k = 0; k < r.jumlahPasien; k++) {
                        for (int u = 0; u < lUser.jumlahuser; u++) {
                            if (lUser.users[u].id == r.pasienIds[k]) {
                                printf("  %d. %s\n", k + 1, lUser.users[u].username);
                                break;
                            }
                        }
                    }
                }

                // Tampilkan pasien di antrian
                printf("Pasien di antrian:\n");
                if (isEmptyQueue(r.baris)) {
                    printf("  Tidak ada pasien di antrian saat ini.\n");
                } else {
                    int nomor = 1;
                    int k = IDX_HEAD(r.baris);
                    while (1) {
                        // Cari nama pasien berdasarkan ID
                        const char* pasienName = "-";
                        for (int l = 0; l < lUser.jumlahuser; l++) {
                            if (lUser.users[l].id == r.baris.buffer[k]) {
                                pasienName = lUser.users[l].username;
                                break;
                            }
                        }
                        printf("  %d. %s\n", nomor, pasienName);
                        if (k == IDX_TAIL(r.baris)) break;
                        k = (k + 1) % CAPACITY_QUEUE;
                        nomor++;
                    }
                }
            }
        }
    }
}