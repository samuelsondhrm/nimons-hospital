/* File: user.h */
/* Deklarasi ADT User sebagai container data user.csv dan representasi akun */

#ifndef USER_H
#define USER_H

#include <string.h>
#include <stdio.h>
#define MAX_FIELD 128

// Struktur data untuk menyimpan informasi pasien
typedef struct {
    int id;
    char username[MAX_FIELD];
    char password[MAX_FIELD];
    char role[MAX_FIELD];
    char riwayat_penyakit[MAX_FIELD];
    float suhu_tubuh;
    int tekanan_darah_sistolik;
    int tekanan_darah_diastolik;
    int detak_jantung;
    float saturasi_oksigen;
    int kadar_gula_darah;
    float berat_badan;
    int tinggi_badan;
    int kadar_kolesterol;
    int kadar_kolesterol_ldl;
    int trombosit;
} User;

typedef struct {
    User users[MAX_FIELD];
    int jumlahuser;
} ListUser; // ListUser adalah list rata kiri yang diurut menaik berdasarkan USER_ID user
            // Semua jenis perilaku terhadap user menggunakan USER_ID (menghapus, insert, mencari), tidak menggunakan index
            // USER_ID user > 0

/* ********** SELEKTOR ********** */
// Makro untuk mempermudah akses elemen User
#define USER_ID(u) (u).id
#define USERNAME(u) (u).username
#define PASSWORD(u) (u).password
#define ROLE(u) (u).role
#define RIWAYAT_PENYAKIT(u) (u).riwayat_penyakit
#define SUHU_TUBUH(u) (u).suhu_tubuh
#define TEKANAN_SISTOLIK(u) (u).tekanan_darah_sistolik
#define TEKANAN_DIASTOLIK(u) (u).tekanan_darah_diastolik
#define DETAK_JANTUNG(u) (u).detak_jantung
#define OKSIGEN(u) (u).saturasi_oksigen
#define GULA_DARAH(u) (u).kadar_gula_darah
#define BERAT_BADAN(u) (u).berat_badan
#define TINGGI_BADAN(u) (u).tinggi_badan
#define KOLESTEROL(u) (u).kadar_kolesterol
#define KOLESTEROL_LDL(u) (u).kadar_kolesterol_ldl
#define TROMBOSIT(u) (u).trombosit
#define USERS(l,i) (l).users[i]
#define JUMLAHUSER(l) (l).jumlahuser

/* ********** KONSTRUKTOR ********** */
// Membuat user kosong (default value)
void CreateUser(User *u);
// Membuat ListUser kosong
void InitializeListUser(ListUser *l);

/* ********** ETC ********** */
// Menerima USER_ID, mengembalikan user dengan id tersebut (Jika tidak ada, akan direturn user dengan USER_ID = -1)
User GetUser(ListUser l, int id);
// Menghapus user dengan id tersebut
void DelUser(ListUser *l, int id, User *buffer);
// Memasukkan user ke dalam ListUser (Jika ListUser penuh, tidak dilakukan apa-apa)
void InsUser(ListUser *l, User buffer);
// Print semua isi ListUser beserta atributnya
void tampilkan_user(ListUser ListUser);


#endif
