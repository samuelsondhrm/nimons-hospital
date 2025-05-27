#include "diagnosis.h"
#include <stdio.h>
#include <string.h>

// cari ruangan dari ID dokter
static Ruangan* cariRuanganDokter(RumahSakit *rs, int dokterId) {
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            if (rs->data[i][j].dokterId == dokterId) {
                return &rs->data[i][j];
            }
        }
    }
    return NULL;
}

void diagnosis(User *current_user, RumahSakit *rs, ListUser *lUser, ListPenyakit *lPenyakit) {
    if (strcmp(ROLE(*current_user), "Dokter") != 0) {
        return; // cuman dokter yang bisa
    }

    Ruangan *ruang = cariRuanganDokter(rs, USER_ID(*current_user));
    if (ruang == NULL || ruang->jumlahPasien == 0) {
        return; // tidak ada pasien
    }

    int pasienId = ruang->pasienIds[0];
    User *pasien = NULL;
    for (int i = 0; i < JUMLAHUSER(*lUser); i++) {
        if (USER_ID(USERS(*lUser, i)) == pasienId) {
            pasien = &USERS(*lUser, i);
            break;
        }
    }

    if (pasien == NULL) {
        return; // pasien tidak ada
    }

    // Diagnosis penyakit 
    for (int i = 0; i < JUMLAH_PENYAKIT(*lPenyakit); i++) {
        Penyakit p = PENYAKIT_LIST(*lPenyakit, i);

        if (SUHU_TUBUH(*pasien) >= SUHU_MIN(p) && SUHU_TUBUH(*pasien) <= SUHU_MAX(p) &&
            TEKANAN_SISTOLIK(*pasien) >= SYS_MIN(p) && TEKANAN_SISTOLIK(*pasien) <= SYS_MAX(p) &&
            TEKANAN_DIASTOLIK(*pasien) >= DIAS_MIN(p) && TEKANAN_DIASTOLIK(*pasien) <= DIAS_MAX(p) &&
            DETAK_JANTUNG(*pasien) >= DETAK_MIN(p) && DETAK_JANTUNG(*pasien) <= DETAK_MAX(p) &&
            OKSIGEN(*pasien) >= SATURASI_MIN(p) && OKSIGEN(*pasien) <= SATURASI_MAX(p) &&
            GULA_DARAH(*pasien) >= GULA_MIN(p) && GULA_DARAH(*pasien) <= GULA_MAX(p) &&
            BERAT_BADAN(*pasien) >= BERAT_MIN(p) && BERAT_BADAN(*pasien) <= BERAT_MAX(p) &&
            TINGGI_BADAN(*pasien) >= TINGGI_MIN(p) && TINGGI_BADAN(*pasien) <= TINGGI_MAX(p) &&
            KOLESTEROL(*pasien) >= KOLESTEROL_MIN(p) && KOLESTEROL(*pasien) <= KOLESTEROL_MAX(p) &&
            TROMBOSIT(*pasien) >= TROMBOSIT_MIN(p) && TROMBOSIT(*pasien) <= TROMBOSIT_MAX(p)) {

            // Diagnosis bisa
            strcpy(RIWAYAT_PENYAKIT(*pasien), NAMA_PENYAKIT(p));
            return;
        }
    }

    // tidak ada diagnosis cocok
    strcpy(RIWAYAT_PENYAKIT(*pasien), "-"); 
}
