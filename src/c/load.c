#include "../header/load.h"

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

    // Panggil loadConfig langsung
    Inventory inv;
    int maxAntrianLuar;
    if (!loadConfig(config_path, rs, &inv, &maxAntrianLuar)) {
        printf("Gagal memuat konfigurasi rumah sakit dari %s\n", config_path);
        exit(1);
    }
    // Salin data pasien dari Inventory ke array Pasien
    for (int i = 0; i < inv.jumlahPasienwObat; i++) {
        pasienData[i] = inv.data[i];
    }

    printf("Selamat datang kembali di rumah sakit Nimons!\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
        return 1;
    }

    // Deklarasi struktur data utama
    ListUser listUser;
    RumahSakit rs;
    Pasien pasienData[100]; // Ukuran bisa disesuaikan

    load_data(argv[1], &listUser, &rs, pasienData);

    // Program lanjut ke menu utama, dst...
    // Misal: menu_interaktif(&listUser, &rs, pasienData);

    return 0;
}