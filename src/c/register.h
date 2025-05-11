#ifndef REGISTER_H
#define REGISTER_H

#include "../header/user.h"
#include "../header/set.h"

#define MAX_FIELD 128

// Validasi format username
bool is_username_valid(const char* username);

// Menulis data user ke file CSV
bool write_users_to_csv(const char* filename, User users[], int count);

// Fungsi registrasi pasien
void register_pasien(User users[], int* user_count, const char* filename);

#endif