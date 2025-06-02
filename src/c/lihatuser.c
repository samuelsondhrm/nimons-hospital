/*

3 PROSEDUR PEMANGGILAN:
    lihatUser(&lu, 0); --> melihat semua user
    lihatUser(&lu, 1); --> melihat hanya pasien
    lihatUser(&lu, 2); --> melihat hanya dokter

*/

#include "../header/lihatuser.h"

void lihatUser(ListUser *lUser, int mode) {
    // Ambil input urutan sort
    int byId = getIntInput(
        "Urutkan berdasarkan?\n1. ID\n2. Nama\n>> Pilihan: ", 1, 2);
    int asc = getIntInput(
        "Urutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)\n>> Pilihan: ", 1, 2);

    // Konversi ke boolean
    byId = (byId == 1);
    asc = (asc == 1);

    // Filter user sesuai mode
    User temp[MAX_FIELD];
    int count = 0;
    for (int i = 0; i < lUser->jumlahuser; i++) {
        if (mode == 0 ||
            (mode == 1 && strcmp(lUser->users[i].role, "pasien") == 0) ||
            (mode == 2 && strcmp(lUser->users[i].role, "dokter") == 0)) {
            temp[count++] = lUser->users[i];
        }
    }

    // Sort hasil filter
    sortUsers(temp, count, byId, asc);

    // Cetak header
    const char *tipe = mode == 0 ? "pengguna"
                        : mode == 1 ? "pasien"
                        : "dokter";
    const char *kriteria = byId ? "ID" : "nama";
    const char *urutan = asc ? "ascending" : "descending";
    printf("Menampilkan %s dengan %s terurut %s...\n", tipe, kriteria, urutan);

    // Tampilkan user
    displayHeader(mode);
    for (int i = 0; i < count; i++) {
        displayUser(&temp[i], mode);
    }
}
