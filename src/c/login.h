#ifndef LOGIN_H
#define LOGIN_H

<<<<<<< HEAD
#include "../header/user.h"
#include "../header/parser_user_csv.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Variabel global
extern User* current_user;
extern bool SudahLogin;
extern bool PasswordSalah;

// Deklarasi fungsi login
User* find_user_by_username(User users[], int count, const char* username);
bool login(User users[], int user_count);

#endif 
=======
#include "user.h"
#include "parser_user_csv.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

User* current_user = NULL;
bool SudahLogin = false;
bool PasswordSalah = false;

User* find_user_by_username(User users[], int count, const char* username) {
    for (int i = 0; i < count; i++) {
        if (strcasecmp(users[i].username, username) == 0) {
            return &users[i];
        }
    }
    return NULL;
}

bool login(User users[], int user_count) {
    char username[MAX_FIELD];
    char password[MAX_FIELD];

    PasswordSalah = false;
    SudahLogin = false;

    printf("\n>>> LOGIN\n");
    printf("Username: ");
    if (scanf("%128s", username) != 1) {
        printf("Input username tidak valid!\n");
        return false;
    }

    printf("Password: ");
    if (scanf("%128s", password) != 1) {
        printf("Input password tidak valid!\n");
        return false;
    }

    while (getchar() != '\n');

    User* user = find_user_by_username(users, user_count, username);

    if (user == NULL) {
        printf("\nTidak ada Manager, Dokter, atau pun Pasien yang bernama %s!\n", username);
        return false;
    }

    if (strcmp(user->password, password) != 0) {
        printf("\nUsername atau password salah untuk pengguna yang bernama %s!\n", username);
        PasswordSalah = true;
        return false;
    }

    current_user = user;
    SudahLogin = true;

    if (strcmp(user->role, "manager") == 0) {
        printf("\nSelamat pagi Manager %s!\n", user->username);
    } else if (strcmp(user->role, "dokter") == 0) {
        printf("\nSelamat pagi Dokter %s!\n", user->username);
    } else if (strcmp(user->role, "pasien") == 0) {
        printf("\nSelamat pagi %s! Ada keluhan apa ?\n", user->username);
    }

    return true;
}

#endif
>>>>>>> fcd01e99a8409bc9f8b8437aad2fd123f24be983
