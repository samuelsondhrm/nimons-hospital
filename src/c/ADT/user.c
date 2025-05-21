#include <string.h>
#include "../../header/ADT/user.h"

// Konstruktor: inisialisasi User dengan nilai default
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

void InitializeListUser(ListUser *l){
    l->jumlahuser = 0;
}
