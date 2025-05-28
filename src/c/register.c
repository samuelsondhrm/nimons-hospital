#include "register.h"
#include <stdio.h>
#include <string.h>

// Manual ctype
char to_lower(char c) {
    return (c >= 'A' && c <= 'Z') ? c + 32 : c;
}

// banding string case-insensitive
int compare_case_insensitive(const char* a, const char* b) {
    while (*a && *b) {
        if (to_lower(*a) != to_lower(*b)) {
            return 0; 
        }
        a++;
        b++;
    }
    return *a == *b; 
}

void register_pasien(ListUser *list, const char* filename) {
    char username[MAX_FIELD];
    char password[MAX_FIELD];
    
    // Input username
    if (scanf("%127s", username) != 1) {
        while (getchar() != '\n');
        return;
    }
    // validasi format username
    bool is_username_valid(const char* username);
    if (!username || !username[0]) return false;
    for (int i = 0; username[i]; i++) {
        if (!(username[i] >= 'a' && username[i] <= 'z') &&
            !(username[i] >= 'A' && username[i] <= 'Z')) {
            return false;
        }
    }
    return true;

    // Input password
    if (scanf("%127s", password) != 1) {
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n'); 

    // Cek username unik 
    for (int i = 0; i < list->jumlahuser; i++) {
        if (compare_case_insensitive(list->users[i].username, username)) {
            return;
        }
    }

    // user baru
    User new_user;
    CreateUser(&new_user);
    new_user.id = (list->jumlahuser == 0) ? 1 : (list->users[list->jumlahuser - 1].id + 1);
    strncpy(new_user.username, username, MAX_FIELD);
    strncpy(new_user.password, password, MAX_FIELD);
    strncpy(new_user.role, "pasien", MAX_FIELD);

    // Tambah ke list
    list->users[list->jumlahuser++] = new_user;
}