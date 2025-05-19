#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH_LEN 256

int folder_exists(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        closedir(dir);
        return 1;
    }
    return 0;
}

void load(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Tidak ada nama folder yang diberikan!\n");
        printf("Usage : ./main <<nama_folder>>\n");
        return ;
    }
    if (!folder_exists(argv[1])) {
        printf("Folder \"%s\" tidak ditemukan.\n", argv[1]);
        return ;
    }
    printf("Loading...\n");
    printf("Selamat datang kembali di rumah sakit Nimons!\n");
    printf("Silakan ketik perintah (register/login/...): ");
}