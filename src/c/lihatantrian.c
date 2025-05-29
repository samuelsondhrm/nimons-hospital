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

                // Hitung panjang antrian
                int len = lengthQueue(r.antrianPasienIds);
                int dalamRuangan = (len < rs.kapasitasPerRuangan) ? len : rs.kapasitasPerRuangan;
                int dalamAntrian = len - dalamRuangan;

                // Tampilkan pasien di dalam ruangan
                printf("Pasien di dalam ruangan:\n");
                if (dalamRuangan == 0) {
                    printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
                } else {
                    int index = IDX_HEAD(r.antrianPasienIds);
                    for (int k = 0; k < dalamRuangan; k++) {
                        int id = r.antrianPasienIds.buffer[index];
                        const char* namaPasien = "-";
                        for (int l = 0; l < lUser.jumlahuser; l++) {
                            if (lUser.users[l].id == id) {
                                namaPasien = lUser.users[l].username;
                                break;
                            }
                        }
                        printf("  %d. %s\n", k + 1, namaPasien);
                        index = (index + 1) % CAPACITY_QUEUE;
                    }
                }

                // Tampilkan pasien di antrian
                printf("Pasien di antrian:\n");
                if (dalamAntrian == 0) {
                    printf("  Tidak ada pasien di antrian saat ini.\n");
                } else {
                    int index = (IDX_HEAD(r.antrianPasienIds) + dalamRuangan) % CAPACITY_QUEUE;
                    for (int k = 0; k < dalamAntrian; k++) {
                        int id = r.antrianPasienIds.buffer[index];
                        const char* namaPasien = "-";
                        for (int l = 0; l < lUser.jumlahuser; l++) {
                            if (lUser.users[l].id == id) {
                                namaPasien = lUser.users[l].username;
                                break;
                            }
                        }
                        printf("  %d. %s\n", k + 1, namaPasien);
                        index = (index + 1) % CAPACITY_QUEUE;
                    }
                }
            }
        }
    }
}
