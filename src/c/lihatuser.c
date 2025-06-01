/*

3 PROSEDUR PEMANGGILAN:
    lihatUser(&lu, 0); --> melihat semua user
    lihatUser(&lu, 1); --> melihat hanya pasien
    lihatUser(&lu, 2); --> melihat hanya dokter

*/

#include "../header/lihatuser.h"

// Core function to handle LIHAT_USER, LIHAT_PASIEN, LIHAT_DOKTER
void lihatUser(ListUser *lUser, int mode) {
    // mode: 0 all, 1 pasien, 2 dokter
    int byId, order;
    printf("Urutkan berdasarkan?\n");
    printf("1. ID\n2. Nama\n>> Pilihan: ");
    scanf("%d", &byId);
    while(byId != 1 && byId != 2){
        printf("Masukan salah, pilih antara 1/2!\nUrutkan berdasarkan?\n1. ID\n2. Nama\n>> Pilihan: ");
        scanf("%d", &byId);
    }
    byId = (byId == 1);
    printf("Urutan sort?\n");
    printf("1. ASC (A-Z)\n2. DESC (Z-A)\n>> Pilihan: ");
    scanf("%d", &order);
    while(order != 1 && order != 2){
        printf("Masukan salah, pilih antara 1/2!\nUrutan sort?\n1. ASC (A-Z)\n2. DESC (Z-A)\n>> Pilihan: ");
        scanf("%d", &order);
    }
    int asc = (order == 1);

    // Filter users into temp array
    User temp[MAX_FIELD];
    int count = 0;
    for (int i = 0; i < lUser->jumlahuser; i++) {
        if (mode == 0 || (mode == 1 && strcmp(lUser->users[i].role, "pasien") == 0) ||
            (mode == 2 && strcmp(lUser->users[i].role, "dokter") == 0)) {
            temp[count++] = lUser->users[i];
        }
    }

    // Sort filtered array
    sortUsers(temp, count, byId, asc);

    // Print title
    if (mode == 0) printf("Menampilkan semua pengguna %s...\n", byId ? (asc ? "dengan ID terurut ascending" : "dengan ID terurut descending") : (asc ? "dengan nama terurut ascending" : "dengan nama terurut descending"));
    else if (mode == 1) printf("Menampilkan pasien %s...\n", byId ? (asc ? "dengan ID terurut ascending" : "dengan ID terurut descending") : (asc ? "dengan nama terurut ascending" : "dengan nama terurut descending"));
    else if (mode == 2) printf("Menampilkan dokter %s...\n", byId ? (asc ? "dengan ID terurut ascending" : "dengan ID terurut descending") : (asc ? "dengan nama terurut ascending" : "dengan nama terurut descending"));
    
    // Display
    displayHeader(mode);
    for (int i = 0; i < count; i++) {
        displayUser(&temp[i], mode);
    }
}