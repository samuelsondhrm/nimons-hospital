#include "../header/register.h"


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

    // Input username
    if (scanf("%127s", username) != 1) {
        while (getchar() != '\n');
        return;
    }

    if (!is_username_valid(username)) {
        //printf("Format username tidak valid.\n");
        return;
    }

    // Input password
    if (scanf("%127s", password) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    // Cek username unik
    for (int i = 0; i < lUser->jumlahuser; i++) {
        if (compare_case_insensitive(lUser->users[i].username, username)) {
           // printf("Username sudah digunakan.\n");
            return;
        }
    }

    // Buat user baru
    CreateUser(new_user);
    new_user->id = (lUser->jumlahuser == 0) ? 1 : (lUser->users[lUser->jumlahuser - 1].id + 1); // ID baru
    strncpy(new_user->username, username, MAX_FIELD);
    strncpy(new_user->password, password, MAX_FIELD);
    strncpy(new_user->role, "pasien", MAX_FIELD);

    // Tambah ke list 
    InsUser(lUser, *new_user);
}
