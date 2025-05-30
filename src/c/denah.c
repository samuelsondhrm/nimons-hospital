/*

PROSEDUR PEMANGGILAN:
lihatRuangan(&rs, input + 14, users, 3);

*/

#include "../header/denah.h"

void printDenah(const RumahSakit rs) {
    printf("    ");
    for (int j = 0; j < rs.cols; j++) printf("  %d ", j + 1);
    printf("\n");

    for (int i = 0; i < rs.rows; i++) {
        printf("  +");
        for (int j = 0; j < rs.cols; j++) printf("---+");
        printf("\n");

        printf("%c |", 'A' + i);
        for (int j = 0; j < rs.cols; j++) {
            printf(" %c%d|", 'A' + i, j + 1);
        }
        printf("\n");
    }

    printf("  +");
    for (int j = 0; j < rs.cols; j++) printf("---+");
    printf("\n");
}


void lihatRuangan(RumahSakit rs, char* kode, ListUser lUser) {
    int row = kode[0] - 'A';
    int col = kode[1] - '1';

    if (row >= rs.rows || col >= rs.cols) {
        printf("Ruangan tidak valid.\n");
        return;
    }

    Ruangan r = rs.data[row][col];
    printf("--- Detail Ruangan %s ---\n", kode);
    printf("Kapasitas  : %d\n", rs.kapasitasPerRuangan);

    // Tampilkan nama dokter
    if (r.dokterId == 0) {
        printf("Dokter     : -\n");
    } else {
        const char* dokterName = "-";
        for (int i = 0; i < lUser.jumlahuser; i++) {
            if (lUser.users[i].id == r.dokterId) {
                dokterName = lUser.users[i].username;
                break;
            }
        }
        printf("Dokter     : Dr. %s\n", dokterName);
    }

    // Tampilkan pasien
    printf("Pasien di dalam ruangan:\n");
    if (r.jumlahPasien == 0) {
        printf("  Tidak ada pasien di dalam ruangan saat ini.\n");
    } else {
        for (int i = 0; i < r.jumlahPasien; i++) {
            const char* pasienName = "-";
            for (int j = 0; j < lUser.jumlahuser; j++) {
                if (lUser.users[j].id == r.pasienIds[i]) {
                    pasienName = lUser.users[j].username;
                    break;
                }
            }
            printf("  %d. %s\n", i + 1, pasienName);
        }
    }

    // Pemisah akhir seperti di gambar
    printf("--------------------------------------------------\n");
}