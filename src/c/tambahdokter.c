/*

PROSEDUR PEMANGGILAN:
tambahDokter(&listUser);
assignDokter(&rs, &listUser)

*/

#include "../header/tambahdokter.h"

int idTerkecil(ListUser list) {
    // Anggap jumlah user tidak lebih dari MAX_FIELD
    // Kita buat array penanda apakah suatu id sudah digunakan
    boolean used[MAX_FIELD * 2] = {false}; // Boleh 2x MAX_FIELD untuk aman

    // Tandai semua ID yang digunakan
    for (int i = 0; i < list.jumlahuser; i++) {
        int id = list.users[i].id;
        if (id > 0 && id < MAX_FIELD * 2) {
            used[id] = true;
        }
    }

    // Cari ID terkecil yang belum digunakan, dimulai dari 1
    for (int i = 1; i < MAX_FIELD * 2; i++) {
        if (!used[i]) {
            return i;
        }
    }

    // Kalau semua id dari 1 sampai MAX_FIELD*2 sudah dipakai, tidak kembalikan apa-apa
    return;
}


void tambahDokter(ListUser *lUser) {
    char username[MAX_FIELD], password[MAX_FIELD];

    printf("Username: ");
    scanf("%s", username);

    // Cek apakah username sudah dipakai oleh dokter lain
    for (int i = 0; i < lUser->jumlahuser; i++) {
        if (strcmp(lUser->users[i].role, "dokter") == 0 && strcmp(lUser->users[i].username, username) == 0) {
            printf("Sudah ada Dokter bernama %s!\n", username);
            while (getchar() != '\n');
            return;
        }
    }

    printf("Password: ");
    scanf("%s", password);

    // Tambahkan user baru
    User newUser;
    lUser->jumlahuser++;
    CreateUser(&newUser);
    newUser.id = idTerkecil(*lUser);
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    strcpy(newUser.role, "dokter");
    lUser->users[lUser->jumlahuser-1] = newUser;

    printf("Dokter %s berhasil ditambahkan!\n", username);
    while (getchar() != '\n');
}

void assignDokter(RumahSakit *rs, ListUser *lUser) {
    char username[MAX_FIELD], ruangan[4];

    printf("Username: ");
    scanf("%s", username);

    // Cari ID dokter berdasarkan username
    int dokterId = -1;
    for (int i = 0; i < lUser->jumlahuser; i++) {
        if (strcmp(lUser->users[i].username, username) == 0 && strcmp(lUser->users[i].role, "dokter") == 0) {
            dokterId = lUser->users[i].id;
            break;
        }
    }

    if (dokterId == -1) {
        printf("Dokter dengan username %s tidak ditemukan.\n", username);
        while (getchar() != '\n');
        return;
    }

    printf("Ruangan: ");
    scanf("%s", ruangan);

    int row = ruangan[0] - 'A';
    int col = ruangan[1] - '1';

    if (row < 0 || row >= rs->rows || col < 0 || col >= rs->cols) {
        printf("Ruangan tidak valid.\n");
        while (getchar() != '\n');
        return;
    }

    // Cek apakah dokter sudah ditempatkan di ruangan manapun
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            if (rs->data[i][j].dokterId == dokterId) {
                if (rs->data[row][col].dokterId == 0) {
                    printf("Dokter %s sudah diassign ke ruangan %c%d!\n", username, row + 'A', col + 1);
                } else {
                    // Ruangan target juga sudah ditempati
                    for (int k = 0; k < lUser->jumlahuser; k++) {
                        if (lUser->users[k].id == rs->data[row][col].dokterId) {
                            printf("Dokter %s sudah menempati ruangan %c%d!\n", lUser->users[k].username, row + 'A', col + 1);
                            break;
                        }
                    }
                    printf("Silakan cari ruangan lain untuk dokter %s.\n", username);
                }
                while (getchar() != '\n');
                return;
            }
        }
    }

    // Cek apakah ruangan sudah diisi dokter lain
    if (rs->data[row][col].dokterId != 0) {
        for (int i = 0; i < lUser->jumlahuser; i++) {
            if (lUser->users[i].id == rs->data[row][col].dokterId) {
                printf("Dokter %s sudah menempati ruangan %c%d!\n", lUser->users[i].username, row + 'A', col + 1);
                printf("Silakan cari ruangan lain untuk dokter %s.\n", username);
                while (getchar() != '\n');
                return;
            }
        }
    }

    // Assign dokter ke ruangan
    rs->data[row][col].dokterId = dokterId;
    printf("Dokter %s berhasil diassign ke ruangan %c%d!\n", username, row + 'A', col + 1);
    while (getchar() != '\n');
}