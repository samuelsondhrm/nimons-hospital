#include "../header/load.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <direct.h>
#define SEPARATOR '\\'
#else
#include <unistd.h>
#define SEPARATOR '/'
#endif
#include <sys/stat.h>



// Prosedur utama load
int load_data(const char *folder, ListUser *listUser, ListObat *listObat, ListPenyakit *listPenyakit, ListFormula *listFormula, RumahSakit *rs, Inventory *inventory) {
    char path[256];

    // Cek folder
    if (!folder_exists(folder)) {
        printf("Folder \"%s\" tidak ditemukan.\n", folder);
        return 0;
    }

    printf("Loading...\n");

    // Load user.csv
    snprintf(path, sizeof(path), "%s%cuser.csv", folder, SEPARATOR);
    parse_user_csv(path, listUser);

    // Load obat.csv
    snprintf(path, sizeof(path), "%s%cobat.csv", folder, SEPARATOR);
    parse_obat_csv(path, listObat);

    // Load penyakit.csv
    snprintf(path, sizeof(path), "%s%cpenyakit.csv", folder, SEPARATOR);
    parse_penyakit_csv(path, listPenyakit);

    // Load obat_penyakit.csv
    snprintf(path, sizeof(path), "%s%cobat_penyakit.csv", folder, SEPARATOR);
    parse_obatpenyakit_csv(path, listFormula);

    char config_path[512];
    int maxAntrianLuar;
    snprintf(config_path, sizeof(config_path), "%s%cconfig.txt", folder, SEPARATOR);
    if (!loadConfig(config_path, rs, inventory, &maxAntrianLuar)) {
        printf("Gagal membaca config.txt\n");
        return 0;
    }

    printf("Selamat datang kembali di rumah sakit Nimons !\n");
    return 1;
    return 1;
}