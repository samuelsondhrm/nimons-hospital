#include "ngobatin.h"
#include <string.h>
#include <stdio.h>

// cari ruangan dokter berdasarkan ID
Ruangan* cariRuanganDokter(RumahSakit *rs, int dokterId) {
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            if (rs->data[i][j].dokterId == dokterId) {
                return &rs->data[i][j]; 
            }
        }
    }
    return NULL;
}

void ngobatin(User current_user, RumahSakit *rs, ListUser *lUser, ListObat *lObat, ListFormula *lFormula, ListPenyakit *lPenyakit) {
    if (strcmp(ROLE(current_user), "Dokter") != 0) { // cuma dokter yang bisa
        return;
    }

    // Cari ruangan dokter
    Ruangan *ruang = cariRuanganDokter(rs, USER_ID(current_user));
    if (ruang == NULL || ruang->jumlahPasien == 0) {
        return;
    }

    // Ambil ID pasien paling pertama di ruangan
    int pasienId = ruang->pasienIds[0];
    User pasien = GetUser(*lUser, pasienId);

    printf("Dokter sedang mengobati pasien!\n");

    // Cek apakah sudah ada diagnosis
    if (strcmp(RIWAYAT_PENYAKIT(pasien), "-") == 0 || strlen(RIWAYAT_PENYAKIT(pasien)) == 0) {
        return;
    }

    int count = 1;

    // mencari obat sesuai penyakit
    for (int i = 0; i < JUMLAH_FORMULA(*lFormula); i++) {
        Formula f = FORMULA_LIST(*lFormula, i);

        // mencocokkan ID penyakit dan nama 
        for (int j = 0; j < JUMLAH_PENYAKIT(*lPenyakit); j++) {
            Penyakit p = PENYAKIT_LIST(*lPenyakit, j);

            // tampilkan obat kalau cocok
            if (ID_PENYAKIT(p) == f.penyakit_id && strcmp(NAMA_PENYAKIT(p), RIWAYAT_PENYAKIT(pasien)) == 0) {
                Obat o = GetObat(*lObat, f.obat_id);
            }
        }
    }
}