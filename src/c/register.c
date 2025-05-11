#include "register.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Fungsi ctype versi manual
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

void register_pasien(ListUser *ListUser,const char* filename) {
    char username[MAX_FIELD];
    char password[MAX_FIELD];
    
    if (scanf("%127s", username) != 1) { //validasi input username
        while (getchar() != '\n');
        return;
    }
    
    if (!is_username_valid(username)) { // validasi input username
        while (getchar() != '\n');
        return;
    }
    
    printf("Password: ");
    if (scanf("%127s", password) != 1) { // validasi password
        while (getchar() != '\n');
        return;
    }
    
    while (getchar() != '\n');
    
    // Validasi username unik 
    Set username_set;
    CreateEmptySet(&username_set);
    
    for (int i = 0; i < ListUser->jumlahuser; i++) {
        char lower[MAX_FIELD];
        strcpy(lower, ListUser->users[i].username);
        for (int j = 0; lower[j]; j++) {
            lower[j] = to_lower(lower[j]);
        }
        InsertSet(&username_set, (ElType)lower);
    }
    
    char new_lower[MAX_FIELD];
    strcpy(new_lower, username);
    for (int j = 0; new_lower[j]; j++) {
        new_lower[j] = to_lower(new_lower[j]);
    }
    
    if (IsMember(username_set, (ElType)new_lower)) {  //cek apakah sudah terdaftar
        return;
    }
    
    // Tambahkan user baru
    User new_user;
    CreateUser(&new_user);
    new_user.id = (ListUser->jumlahuser == 0) ? 1 : (ListUser->users[ListUser->jumlahuser - 1].id + 1);
    strcpy(new_user.username, username);
    strcpy(new_user.password, password);
    strcpy(new_user.role, "pasien");
    
    ListUser->users[ListUser->jumlahuser] = new_user;
    ListUser->jumlahuser++;

} 