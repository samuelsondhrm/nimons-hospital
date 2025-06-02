// filepath: c:\Users\Miguel\VSCODE\if1210-tubes-2025-k01-e-3\src\c\load.c
#include "../header/load.h"

// Define SEPARATOR for directory paths
#ifdef _WIN32
#define SEPARATOR '\\'
#else
#define SEPARATOR '/'
#endif

int load_data(const char *folder, ListUser *listuser, ListObat *listobat, 
              ListPenyakit *listpenyakit, ListFormula *listformula, 
              RumahSakit *rs, Inventory *inventory) {
    char path[512];

    // Cek folder
    if (!folder_exists(folder)) {
        printf("Folder \"%s\" tidak ditemukan.\n", folder);
        return 0;
    }

    printf("Loading...\n");

    // Prepare all file paths
    char user_csv_path[512];
    char obat_csv_path[512];
    char penyakit_csv_path[512];
    char obatpenyakit_csv_path[512];
    char config_path[512];

    snprintf(user_csv_path, sizeof(user_csv_path), "%s%cuser.csv", folder, SEPARATOR);
    snprintf(obat_csv_path, sizeof(obat_csv_path), "%s%cobat.csv", folder, SEPARATOR);
    snprintf(penyakit_csv_path, sizeof(penyakit_csv_path), "%s%cpenyakit.csv", folder, SEPARATOR);
    snprintf(obatpenyakit_csv_path, sizeof(obatpenyakit_csv_path), "%s%cobat_penyakit.csv", folder, SEPARATOR);
    snprintf(config_path, sizeof(config_path), "%s%cconfig.txt", folder, SEPARATOR);

    // Check if all required files exist
    if (!file_exists(user_csv_path) || !file_exists(obat_csv_path) || 
        !file_exists(penyakit_csv_path) || !file_exists(obatpenyakit_csv_path) || 
        !file_exists(config_path)) {
        printf("File yang diperlukan tidak lengkap dalam folder \"%s\".\n", folder);
        return 0;
    }

    // Load all files
    parse_user_csv(user_csv_path, listuser);
    parse_obat_csv(obat_csv_path, listobat);
    parse_penyakit_csv(penyakit_csv_path, listpenyakit);
    parse_obatpenyakit_csv(obatpenyakit_csv_path, listformula);

    int maxAntrianLuar;
    if (!loadConfig(config_path, rs, inventory)) {
        printf("Gagal membaca config.txt\n");
        return 0;
    }

    // Check if there's at least one manager account
    boolean hasManager = false;
    for (int i = 0; i < listuser->jumlahuser; i++) {
        if (strcmp(listuser->users[i].role, "manager") == 0) {
            hasManager = true;
            break;
        }
    }

    if (!hasManager) {
        printf("File user.csv harus memiliki setidaknya satu akun manager.\n");
        return 0;
    }

    printf("Selamat datang kembali di rumah sakit Nimons !\n");
    return 1;
}

// Add helper function to check if file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}