#include "../header/save.h"


#ifdef _WIN32
#include <direct.h>
#define SEPARATOR '\\'
#else
#include <unistd.h>
#define SEPARATOR '/'
#endif

#define BASE_FOLDER "data"

// Fungsi rekursif untuk membuat direktori
int create_directory_recursive(const char *path) {
    char tmp[256];
    char *p = NULL;
    size_t len;

    snprintf(tmp, sizeof(tmp), "%s", path);
    len = strlen(tmp);

    if (tmp[len - 1] == SEPARATOR) tmp[len - 1] = '\0';

    for (p = tmp + 1; *p; p++) {
        if (*p == SEPARATOR) {
            *p = '\0';
#ifdef _WIN32
            if (_mkdir(tmp) != 0 && errno != EEXIST) {
                return -1;
            }
#else
            if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
                return -1;
            }
#endif
            *p = SEPARATOR;
        }
    }
#ifdef _WIN32
    return _mkdir(tmp);
#else
    return mkdir(tmp, 0755);
#endif
}

// Cek apakah folder ada
int folder_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

// Prosedur utama save
void save_data(ListUser listUser, RumahSakit rs, Pasien pasienData[]) {
    char folder_name[128];
    printf("Masukkan nama folder: ");
    if (fgets(folder_name, sizeof(folder_name), stdin) == NULL) {
        printf("Error membaca input!\n");
        return;
    }
    folder_name[strcspn(folder_name, "\n")] = '\0';

    char base_path[256];
    snprintf(base_path, sizeof(base_path), "%s", BASE_FOLDER);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%c%s", BASE_FOLDER, SEPARATOR, folder_name);

    int base_exists = folder_exists(base_path);
    int folder_exists_flag = folder_exists(full_path);

    printf("Saving...\n");

    // Cek dan buat BASE_FOLDER jika belum ada
    if (!base_exists) {
        if (create_directory_recursive(base_path) == 0) {
            printf("Membuat folder %s...\n", base_path);
        } else {
            printf("Gagal membuat folder %s!\n", base_path);
            return;
        }
    }

    // Cek dan buat folder tujuan jika belum ada
    if (!folder_exists_flag) {
        if (create_directory_recursive(full_path) == 0) {
            printf("Membuat folder %s...\n", full_path);
        } else {
            printf("Gagal membuat folder %s!\n", full_path);
            return;
        }
    }

    // Tulis user.csv
    char user_csv_path[256];
    snprintf(user_csv_path, sizeof(user_csv_path), "%s%cuser.csv", full_path, SEPARATOR);
    tulis_user_csv(user_csv_path, &listUser);

    // Tulis config.txt
    char config_path[256];
    snprintf(config_path, sizeof(config_path), "%s%cconfig.txt", full_path, SEPARATOR);
    simpanKonfigurasi(config_path, rs, pasienData);

    // (Tambahkan tulis file lain jika perlu)

    printf("Berhasil menyimpan data di folder %s!\n", full_path);
}