#include "../header/register.h"

int compare_case_insensitive(const char* a, const char* b) {
    while (*a && *b) {
        char ca = (*a >= 'A' && *a <= 'Z') ? *a + 32 : *a;
        char cb = (*b >= 'A' && *b <= 'Z') ? *b + 32 : *b;
        if (ca != cb) return 0;
        a++;
        b++;
    }
    return *a == *b;
}

boolean is_username_valid(const char* username) {
    if (!username || !username[0]) return false;
    for (int i = 0; username[i]; i++) {
        if (!((username[i] >= 'a' && username[i] <= 'z') ||
              (username[i] >= 'A' && username[i] <= 'Z'))) {
            return false;
        }
    }
    return true;
}

void register_pasien(ListUser *lUser, User *new_user) {
    char username[MAX_FIELD];
    char password[MAX_FIELD];

     while (1) {
        printf("Masukkan username: ");
        if (scanf("%127s", username) != 1) {
            while (getchar() != '\n');
            continue;
        }

        // Cek format
        if (!is_username_valid(username)) {
            printf("Format username tidak valid. Hanya boleh Huruf!\n");
            continue;
        }

        // Cek unik
        int i;
        for (i = 0; i < lUser->jumlahuser; i++) {
            if (compare_case_insensitive(lUser->users[i].username, username)) {
                printf("Username sudah digunakan.\n");
                break;
            }
        }

        if (i == lUser->jumlahuser) {
            // Username valid dan unik
            break;
        }
    }

    // Input password
    if (scanf("%127s", password) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    // Buat user baru
    CreateUser(new_user);
    new_user->id = (lUser->jumlahuser == 0) ? 1 : (lUser->users[lUser->jumlahuser - 1].id + 1); // ID baru
    strncpy(new_user->username, username, MAX_FIELD);
    strncpy(new_user->password, password, MAX_FIELD);
    strncpy(new_user->role, "pasien", MAX_FIELD);

    // Tambah ke list 
    InsUser(lUser, *new_user);
}
