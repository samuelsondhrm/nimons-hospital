/*

3 PROSEDUR PEMANGGILAN:
    lihatUser(&lu, 0); --> melihat semua user
    lihatUser(&lu, 1); --> melihat hanya pasien
    lihatUser(&lu, 2); --> melihat hanya dokter

*/

#include "../header/lihatuser.h"

// Convert string to lowercase for case-insensitive compare
void toLowerCase(char *dest, const char *src) {
    int i;
    for (i = 0; src[i] && i < MAX_FIELD - 1; i++) {
        dest[i] = tolower((unsigned char)src[i]);
    }
    dest[i] = '\0';
}

// Swap two User elements
void swapUser(User *a, User *b) {
    User temp = *a;
    *a = *b;
    *b = temp;
}

// Sort array of User by ID or username
void sortUsers(User arr[], int n, int byId, int asc) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int cmp = 0;
            if (byId) {
                if (arr[j].id < arr[j+1].id) cmp = -1;
                else if (arr[j].id > arr[j+1].id) cmp = 1;
            } else {
                char s1[MAX_FIELD], s2[MAX_FIELD];
                toLowerCase(s1, arr[j].username);
                toLowerCase(s2, arr[j+1].username);
                cmp = strcmp(s1, s2);
            }
            if ((asc && cmp > 0) || (!asc && cmp < 0)) {
                swapUser(&arr[j], &arr[j+1]);
            }
        }
    }
}

// Display format functions
void displayHeader(int mode) {
    // mode: 0 = all, 1 = pasien, 2 = dokter
    if (mode == 0) {
        printf("ID | Nama     | Role     | Penyakit\n");
        printf("-------------------------------------\n");
    } else if (mode == 1) {
        printf("ID | Nama     | Penyakit\n");
        printf("-------------------------\n");
    } else {
        printf("ID | Nama     \n");
        printf("--------------\n");
    }
}

void displayUser(const User *u, int mode) {
    // mode: 0 = all, 1 = pasien, 2 = dokter
    if (mode == 0) {
        printf("%d  | %-8s | %-8s | %s\n", u->id, u->username, u->role,
               (strcmp(u->role, "pasien") == 0 ? u->riwayat_penyakit : "-"));
    } else if (mode == 1) {
        printf("%d  | %-8s | %s\n", u->id, u->username, u->riwayat_penyakit);
    } else {
        printf("%d  | %-8s\n", u->id, u->username);
    }
}

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