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

User GetUser(ListUser l, int id){
    for(int i = 0; i<JUMLAHUSER(l); i++){
        if(USER_ID(USERS(l, i)) == id){
            return USERS(l,i);
        }
    }
    User ERR_MSG;
    CreateUser(&ERR_MSG);
    USER_ID(ERR_MSG) = -1;
    return ERR_MSG; // Kalau id user -1, bearti error
}

void DelUser(ListUser *l, int id, User *buffer){
    for(int i = 0; i < JUMLAHUSER(*l); i++){
        if(USER_ID(USERS(*l, i)) == id){
            *buffer = l->users[i];
            for(int j = i; j < JUMLAHUSER(*l)-1; j++){
                l->users[j] = l->users[j+1];
            }
            l->jumlahuser--;
            break;
        }
    }
}

void InsUser(ListUser *l, User buffer){
    if(JUMLAHUSER(*l) <= MAX_FIELD && USER_ID(buffer) > 0){
        for(int i = 0; i < JUMLAHUSER(*l);i++){
            if(USER_ID(USERS(*l, i)) == USER_ID(buffer)){
                return;
            }
            else if(USER_ID(USERS(*l, i)) < USER_ID(buffer)){
                for(int j =JUMLAHUSER(*l); j > i;j--){
                    l->users[j] = l->users[j-1];
                }
                l->users[i] = buffer;
                l->jumlahuser++;
                return;
            }
        }
        l->users[JUMLAHUSER(*l)] = buffer; // USER_ID dia terbesar
        l->jumlahuser++;
    }
}

void tampilkan_user(ListUser l) {
    for (int i = 0; i < JUMLAHUSER(l); i++) {
        User p = USERS(l, i);
        printf("Pasien %d:\n", i + 1);
        printf("  USER_ID: %d\n", USER_ID(p));
        printf("  Username: %s\n", USERNAME(p));
        printf("  Role: %s\n", p.role);
        printf("  Riwayat Penyakit: %s\n", RIWAYAT_PENYAKIT(p));
        printf("  Suhu Tubuh: %.1f\n", SUHU_TUBUH(p));
        printf("  Tekanan Darah: %d/%d\n", TEKANAN_SISTOLIK(p), TEKANAN_DIASTOLIK(p));
        printf("  Detak Jantung: %d bpm\n", DETAK_JANTUNG(p));
        printf("  Saturasi Oksigen: %.1f %%\n", OKSIGEN(p));
        printf("  Gula Darah: %d mg/dL\n", GULA_DARAH(p));
        printf("  Berat Badan: %.1f kg\n", BERAT_BADAN(p));
        printf("  Tinggi Badan: %d cm\n", TINGGI_BADAN(p));
        printf("  Kolesterol Total: %d\n", KOLESTEROL(p));
        printf("  LDL: %d\n", KOLESTEROL_LDL(p));
        printf("  Trombosit: %d ribu/uL\n", TROMBOSIT(p));
        printf("\n");
    }
}
