#ifndef USER_H
#define USER_H
#define MAX_FIELD 128

#include <string.h>

// ADT User
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

/* ********** SELEKTOR ********** */
#define ID(u) (u).id
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


/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create user kosong  */
void CreateUser(User *u) {
    u->id = 0;
    strcpy(u->username, "");
    strcpy(u->password, "");
    strcpy(u->role, "");
    strcpy(u->riwayat_penyakit, "");
    u->suhu_tubuh = 0.0;
    u->tekanan_darah_sistolik = 0;
    u->tekanan_darah_diastolik = 0;
    u->detak_jantung = 0;
    u->saturasi_oksigen = 0.0;
    u->kadar_gula_darah = 0;
    u->berat_badan = 0.0;
    u->tinggi_badan = 0;
    u->kadar_kolesterol = 0;
    u->kadar_kolesterol_ldl = 0;
    u->trombosit = 0;
}
#endif
