#include "../header/login.h"

// Implementasi global variabel
User* current_user = NULL;
boolean SudahLogin = false;
boolean PasswordSalah = false;

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

static User* find_user_by_username(const ListUser* list, const char* username) {
    for (int i = 0; i < list->jumlahuser; i++) {
        if (strcmp(list->users[i].username, username) == 0) {
            return &list->users[i];
        }
    }
}

boolean login(User users[], int user_count);
    char username[MAX_FIELD];
    char password[MAX_FIELD];

    PasswordSalah = false;
    SudahLogin = false;

    if (scanf("%127s", username) != 1) { // username tidak valid
        while (getchar() != '\n'); // hapus memori temporer
        return false;
    }

    if (scanf("%127s", password) != 1) { // password tidak valid
        while (getchar() != '\n'); // hapus memori temporer
        return false;
    }

    while (getchar() != '\n'); // hapus memori temporer

    User* user = find_user_by_username(ListUsers, username);

    if (user == NULL) { // nama salah
        return false;
    }

    if (strcmp(user->password, password) != 0) { // username atau password salah
        PasswordSalah = true;
        return false;
    }

    current_user = user;
    SudahLogin = true;


    return true;
}