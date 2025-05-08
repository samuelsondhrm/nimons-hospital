#include "set.h"
#include <stdbool.h>
#include <user.h>

bool is_username_valid(const char* username) {
    for (int i = 0; username[i]; i++) {
        if (!isalpha(username[i])) {
            return false;
        }
    }
    return true;
}

bool write_users_to_csv(const char* filename, User users[], int count) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Gagal membuka file untuk ditulis!\n");
        return false;
    }
    
    // Tulis header
    fprintf(file, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;");
    fprintf(file, "tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;");
    fprintf(file, "berat_badan;tinggi_badan;kadar_kolesterol;kadar_kolesterol_ldl;trombosit\n");
    
    // Tulis data user
    for (int i = 0; i < count; i++) {
        fprintf(file, "%d;%s;%s;%s;%s;%.1f;%d;%d;%d;%.1f;%d;%.1f;%d;%d;%d;%d\n",
                users[i].id,
                users[i].username,
                users[i].password,
                users[i].role,
                users[i].riwayat_penyakit,
                users[i].suhu_tubuh,
                users[i].tekanan_darah_sistolik,
                users[i].tekanan_darah_diastolik,
                users[i].detak_jantung,
                users[i].saturasi_oksigen,
                users[i].kadar_gula_darah,
                users[i].berat_badan,
                users[i].tinggi_badan,
                users[i].kadar_kolesterol,
                users[i].kadar_kolesterol_ldl,
                users[i].trombosit);
    }
    
    fclose(file);
    return true;
}

void register_pasien(User users[], int* user_count, const char* filename) {
    char username[MAX_FIELD];
    char password[MAX_FIELD];
    
    printf("\n>>> REGISTER\n");
    printf("Username: ");
    if (scanf("%127s", username) != 1) {
        printf("Input username tidak valid!\n");
        return;
    }
    
    if (!is_username_valid(username)) {
        printf("Username hanya boleh berisi huruf!\n");
        return;
    }
    
    printf("Password: ");
    if (scanf("%127s", password) != 1) {
        printf("Input password tidak valid!\n");
        return;
    }
    
    // Membersihkan buffer
    while (getchar() != '\n');
    
    // Validasi username unik
    Set username_set;
    CreateEmptySet(&username_set);
    
    for (int i = 0; i < *user_count; i++) {
        char lower[MAX_FIELD];
        strcpy(lower, users[i].username);
        for (int j = 0; lower[j]; j++) {
            lower[j] = tolower(lower[j]);
        }
        InsertSet(&username_set, (ElType)lower);
    }
    
    char new_lower[MAX_FIELD];
    strcpy(new_lower, username);
    for (int j = 0; new_lower[j]; j++) {
        new_lower[j] = tolower(new_lower[j]);
    }
    
    if (IsMember(username_set, (ElType)new_lower)) {
        printf("\nRegistrasi gagal! Pasien dengan nama %s sudah terdaftar.\n", username);
        return;
    }
    
    // Tambahkan user baru
    User new_user;
    CreateUser(&new_user);
    new_user.id = (*user_count == 0) ? 1 : (users[*user_count - 1].id + 1);
    strcpy(new_user.username, username);
    strcpy(new_user.password, password);
    strcpy(new_user.role, "pasien");
    
    users[*user_count] = new_user;
    (*user_count)++;
    
    // Update file CSV
    if (write_users_to_csv(filename, users, *user_count)) {
        printf("\nPasien %s berhasil ditambahkan!\n", username);
    } else {
        printf("\nPasien %s berhasil ditambahkan, tetapi gagal menyimpan ke file!\n", username);
    }
}
