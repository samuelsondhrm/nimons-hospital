#include "../header/login.h"
#include <ctype.h>


void login(ListUser *users, User *current_user, boolean *SudahLogin) {
    char username[MAX_FIELD];
    char password[MAX_FIELD];

    *SudahLogin = false;

    printf("Username: ");
    scanf("%127s", username);
    printf("Password: ");
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
        printf("username tidak ditemukan!");
        return;
    }

   while (1) {
        printf("Password: ");
        scanf("%127s", password);
        while (getchar() != '\n'); // Bersihkan buffer

        if (strcmp(user->password, password) == 0) {
            *current_user = *user;
            *SudahLogin = true;
            printf("Login berhasil! Selamat datang, %s.\n", *current_user->username);
            return;
        }

        // Password salah
        printf("Password salah!\n");
        printf("Pilih aksi:\n");
        printf("1. Coba lagi\n");
        printf("2. Keluar dari login\n");
        printf("3. Lupa password\n");
        printf("Masukkan pilihan (1/2/3): ");
        int pilihan;
        scanf("%d", &pilihan);

        while (getchar() != '\n'); // Bersihkan buffer

        if (pilihan == 1) {
            continue;
        } else if (pilihan == 2) {
            return;
        } else if (pilihan == 3) {
            lupaPassword(&users); 
            return;
        } else {
            printf("Pilihan tidak valid. Keluar dari login.\n");
            return;
        }
    }
}