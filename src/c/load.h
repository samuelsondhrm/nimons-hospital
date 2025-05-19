#ifndef LOAD_H
#define LOAD_H
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_PATH_LEN 256


int folder_exists(const char *path);
// Fungsi cek keberadaan folder

void load(int argc, char *argv[]);
// mengecek kasus di fitur load
// [Kasus 1] Tidak ada argumen folder   
// [Kasus 3] Folder valid
// Asumsi:
// 1. File user.csv ada di folder tersebut
// 2. Sudah ada minimal 1 akun manajer (tidak perlu validasi)
#endif