#include "../header/load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_FOLDER "data/"

// Validasi keberadaan folder
int validate_folder(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

// Validasi keberadaan akun manajer
void check_manager_account(ListUser *listUser) {
    for (int i = 0; i < listUser->jumlahuser; i++) {
        if (strcmp(listUser->users[i].role, "manajer") == 0) {
            return;
        }
    }
    printf("Error: Tidak ada akun manajer dalam user.csv!\n");
    exit(1);
}

// Prosedur load utama
void load_data(const char *folder_name, ListUser *listUser, RumahSakit *rs, Pasien pasienData[]) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%s", BASE_FOLDER, folder_name);

    // Validasi folder
    if (!validate_folder(full_path)) {
        printf("Folder \"%s\" tidak ditemukan.\n", folder_name);
        exit(1);
    }

    printf("Loading...\n");

    // Load user.csv
    char user_csv_path[256];
    snprintf(user_csv_path, sizeof(user_csv_path), "%s/user.csv", full_path);
    parse_user_csv(user_csv_path, listUser);
    check_manager_account(listUser);

    // Load config.txt
    char config_path[256];
    snprintf(config_path, sizeof(config_path), "%s/config.txt", full_path);
    readHospitalConfig(config_path, rs, pasienData);

    // (Tambahkan load untuk penyakit.csv, obat.csv, obat_penyakit.csv jika diperlukan)

    printf("Selamat datang kembali di rumah sakit Nimons!\n");
}