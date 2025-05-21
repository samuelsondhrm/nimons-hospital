/*

PROSEDUR PEMANGGILAN:
tambahDokter(&listUser);
assignDokter(&rs, &listUser)

*/

#include "../header/user.h"
#include "../header/room.h"
#include <stdio.h>
#include <string.h>

void tambahDokter(ListUser *lUser) {
    char username[MAX_FIELD], password[MAX_FIELD];

    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Cek apakah username sudah dipakai oleh dokter lain
    for (int i = 0; i < lUser->jumlahuser; i++) {
        if (strcmp(lUser->users[i].role, "dokter") == 0 && strcmp(lUser->users[i].username, username) == 0) {
            printf("Sudah ada Dokter bernama %s!\n", username);
            return;
        }
    }

    // Tambahkan user baru
    User newUser;
    lUser->jumlahuser++;
    CreateUser(&newUser);
    newUser.id = lUser->jumlahuser;
    strcpy(newUser.username, username);
    strcpy(newUser.password, password);
    strcpy(newUser.role, "dokter");
    lUser->users[lUser->jumlahuser-1] = newUser;

    printf("Dokter %s berhasil ditambahkan!\n", username);
}

void assignDokter(RumahSakit *rs, ListUser *lUser) {
    char username[MAX_FIELD], ruangan[4];

    printf("Username: ");
    scanf("%s", username);
    printf("Ruangan: ");
    scanf("%s", ruangan);

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
        return;
    }

    int row = ruangan[0] - 'A';
    int col = ruangan[1] - '1';

    if (row < 0 || row >= rs->rows || col < 0 || col >= rs->cols) {
        printf("Ruangan tidak valid.\n");
        return;
    }

    // Cek apakah dokter sudah ditempatkan di ruangan manapun
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            if (rs->data[i][j].dokterId == dokterId) {
                if (rs->data[row][col].dokterId == 0) {
                    printf("Dokter %s sudah diassign ke ruangan %c%d!\n", username, i + 'A', j + 1);
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
                return;
            }
        }
    }

    // Cek apakah ruangan sudah diisi dokter lain
    if (rs->data[row][col].dokterId != 0) {
        for (int i = 0; i < lUser->jumlahuser; i++) {
            if (lUser->users[i].id == rs->data[row][col].dokterId) {
                printf("Dokter %s sudah menempati ruangan %c%d!\n", lUser->users[i].username, row + 'A', col + 1);
                printf("Ruangan %c%d juga sudah ditempati dokter %s!\n", row + 'A', col + 1, lUser->users[i].username);
                return;
            }
        }
    }

    // Assign dokter ke ruangan
    rs->data[row][col].dokterId = dokterId;
    printf("Dokter %s berhasil diassign ke ruangan %c%d!\n", username, row + 'A', col + 1);
}