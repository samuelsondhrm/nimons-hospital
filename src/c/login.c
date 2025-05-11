#include "login.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Implementasi global variabel
User* current_user = NULL;
bool SudahLogin = false;
bool PasswordSalah = false;

// Fungsi ctype manual
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// Fungsi strcasecmp manual
int str_case_cmp(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        char c1 = to_lower(*s1);
        char c2 = to_lower(*s2);
        if (c1 != c2) {
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    return to_lower(*s1) - to_lower(*s2);
}

User* find_user_by_username(User users[], int count, const char* username) {
    for (int i = 0; i < count; i++) {
        if (str_case_cmp(users[i].username, username) == 0) {
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
    if (scanf("%127s", username) != 1) {
        printf("Input username tidak valid!\n");
        while (getchar() != '\n'); // hapus memori temporer
        return false;
    }

    printf("Password: ");
    if (scanf("%127s", password) != 1) {
        printf("Input password tidak valid!\n");
        while (getchar() != '\n'); // hapus memori temporer
        return false;
    }

    while (getchar() != '\n'); // Clear buffer

    User* user = find_user_by_username(users, user_count, username);

    if (user == NULL) {
        printf("\nTidak ada Manager, Dokter, atau Pasien yang bernama %s!\n", username);
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