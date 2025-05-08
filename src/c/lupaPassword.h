#include "parse_user_csv.h"
#include "boolean.h"
#include <stdio.h>
#include <string.h>


boolean usernameFound(const char *username, const char *filename) 
{
    User ListUser[MAX_ROWS];
    int jumlah_user;

    parse_user_csv(filename, ListUser, &jumlah_user);

    for (int i = 0; i < jumlah_user; i++) {
        if (strcmp(ListUser[i].username, username) == 0) 
        {
            return true;
        }
    }
    return false;
}

void runLengthEncoding(const char *username, char *username_encoded) {
    int len = strlen(username);
    int count = 1;
    int j = 0; 

    for (int i = 0; i < len; i++) {

        // Menghitung jumlah pengulangan karakter (jika ditemukan)
        if (username[i] == username[i+1]) count++;
    
        else
        {
            // Kasus saat karakter muncul lebih dari satu kali
            if(count > 1) {
                j += sprintf(username_encoded + j, "%d%c", count, username[i]);
            }
            
            // Kasus saat karakter muncul satu kali
            else {
                username_encoded[j++] = username[i];
            }

            // Set ulang counter sebelum di loop lagi
            count = 1;
        }
    }
    username_encoded[j] = '\0'; 

}

boolean kodeUnik(const char *username_dicari, const char *kode) {
    char encoded[MAX_FIELD];
    runLengthEncoding(username_dicari, encoded);

    return(strcmp(encoded, kode) == 0);
}

void getRole(const char *username_dicari, const char *filename, char *role) {
    User ListUser[MAX_ROWS];
    int jumlah_user = 0;

    parse_user_csv(filename, ListUser, &jumlah_user);

    for (int i = 0; i < jumlah_user; i++) {
        if (strcmp(ListUser[i].username, username_dicari) == 0) {
            strcpy(role, ListUser[i].role);
            return;
        }
    }

    // Jika username kosong, kosongkan role
    strcpy(role, ""); 
    
}
// Dalam CSV, untuk modifikasi satu bagian pada file kita perlu menyalin ulang seluruh file

void updatePassword(const char *username_dicari, const char *password_baru, const char *filename) {
    User ListUser[MAX_ROWS];  
    int jumlah = 0;  

    // Parse file CSV dan simpan dalam ListUser[]
    parse_user_csv(filename, ListUser, &jumlah);

    // Cari user dengan username_dicari dan update passwordnya
    for (int i = 0; i < jumlah; i++) {
        if (strcmp(ListUser[i].username, username_dicari) == 0) {
            strcpy(ListUser[i].password, password_baru);
            break;
        }
    }

    // Membuka file sementara untuk menyimpan data yang telah diperbarui
    FILE *file_temp = fopen("temp.csv", "w");
    if (!file_temp) {
        printf("Gagal membuat temp.csv, cek ulang line (x)\n");
        return;
    }

    // Tulis header CSV ke file sementara
    fprintf(file_temp, "id;username;password;role;riwayat_penyakit;suhu_tubuh;tekanan_darah_sistolik;tekanan_darah_diastolik;detak_jantung;saturasi_oksigen;kadar_gula_darah;berat_badan;tinggi_badan;kadar_kolesterol;kadar_kolesterol_ldl;trombosit\n");

    // Tulis seluruh data pengguna yang sudah diperbarui ke file sementara
    for (int i = 0; i < jumlah; i++) {
        fprintf(file_temp, "%d;%s;%s;%s;%s;%.2f;%d;%d;%d;%.2f;%d;%.2f;%d;%d;%d;%d\n",
            ListUser[i].id,
            ListUser[i].username,
            ListUser[i].password,
            ListUser[i].role,
            ListUser[i].riwayat_penyakit,
            ListUser[i].suhu_tubuh,
            ListUser[i].tekanan_darah_sistolik,
            ListUser[i].tekanan_darah_diastolik,
            ListUser[i].detak_jantung,
            ListUser[i].saturasi_oksigen,
            ListUser[i].kadar_gula_darah,
            ListUser[i].berat_badan,
            ListUser[i].tinggi_badan,
            ListUser[i].kadar_kolesterol,
            ListUser[i].kadar_kolesterol_ldl,
            ListUser[i].trombosit);
    }

    fclose(file_temp);

    // Hapus file lama dan ganti dengan file temp
    remove(filename);
    rename("temp.csv", filename);

}
