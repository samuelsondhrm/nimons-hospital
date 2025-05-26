#include "save.h"
#include "../header/parser_user_csv.h"
#include "../header/parser_config_txt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#ifdef _WIN32
#include <direct.h>  // Untuk mkdir di Windows
#define SEPARATOR '\\'
#else
#include <unistd.h>  // Untuk mkdir di UNIX
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
            #else
            if (mkdir(tmp, 0755) != 0 && errno != EEXIST) {
            #endif
                return -1;
            }
            *p = SEPARATOR;
        }
    }


    #ifdef _WIN32
    return _mkdir(tmp);
    #else
    return mkdir(tmp, 0755);
    #endif
}

void save_data(ListUser listUser, RumahSakit rs, Pasien pasienData[]) {
    char folder_name[128];
    printf("Masukkan nama folder: ");
    

    if (fgets(folder_name, sizeof(folder_name), stdin) == NULL) {
        printf("Error membaca input!\n");
        return;
    }
    folder_name[strcspn(folder_name, "\n")] = '\0';  


    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s%c%s", BASE_FOLDER, SEPARATOR, folder_name);


    struct stat st;
    if (stat(BASE_FOLDER, &st) == -1) {
        if (create_directory_recursive(BASE_FOLDER) != 0) {
            printf("Gagal membuat folder %s!\n", BASE_FOLDER);
            return;
        }
    }

    printf("Saving...\n");
    

    if (create_directory_recursive(full_path) != 0) {
        if (errno == EEXIST) {
            printf("Folder sudah ada, melakukan overwrite...\n");
        } else {
            printf("Gagal membuat folder %s!\n", full_path);
            return;
        }
    }

 
    char user_csv_path[256];
    snprintf(user_csv_path, sizeof(user_csv_path), "%s%cuser.csv", full_path, SEPARATOR);
    tulis_user_csv(user_csv_path, listUser);

 
    char config_path[256];
    snprintf(config_path, sizeof(config_path), "%s%cconfig.txt", full_path, SEPARATOR);
    simpanKonfigurasi(config_path, rs, pasienData);

    printf("Berhasil menyimpan data di folder %s!\n", full_path);
}
