#include "../header/login.h"
#include <ctype.h>


void login(ListUser *users, User *current_user) {
    char username[MAX_FIELD];
    char password[MAX_FIELD];

    PasswordSalah = false;
    SudahLogin = false;

    //printf("Username: ");
    scanf("%127s", username);
    //printf("Password: ");
    scanf("%127s", password);

    while (getchar() != '\n'); // Bersihkan buffer

    // Cari user 
    User *user = NULL; // dari ListUser
    for (int i = 0; i < users->jumlahuser; i++) {
        if (strcmp(users->users[i].username, username) == 0) {
            user = &users->users[i];
            break;
        }
    }

    if (user == NULL) { // nama salah
        //printf("username tidak ditemukan!")
        return;
    }

    if (strcmp(user->password, password) != 0) { // username atau password salah
        PasswordSalah = true; // variable global PasswordSalah terisi true
        return;
    }

    current_user = user; // variable global current_user kini terisi dengan user
    SudahLogin = true; // variabel global SudahLogin terisi true

    return;
}