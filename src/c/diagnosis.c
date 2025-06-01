#include "../header/diagnosis.h"

boolean SudahDiagnosis[CAPACITY_QUEUE];

// cari ruangan dari ID dokter
static Ruangan* cariRuanganDokter(RumahSakit *rs, int dokterId) {
    printf("Mencari ruangan untuk dokter dengan ID: %d\n", dokterId);
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            if (rs->data[i][j].dokterId == dokterId) {
                return &rs->data[i][j];
            }
        }
    }
    printf("Tidak ditemukan ruangan untuk dokter dengan ID: %d\n", dokterId);
    return NULL;
}

void diagnosis(User *current_user, RumahSakit *rs, ListUser *lUser, ListPenyakit *lPenyakit) {
    printf("Memulai proses diagnosis...\n");

    if (strcmp(ROLE(*current_user), "Dokter") != 0) {
        printf("Akses ditolak: hanya dokter yang bisa melakukan diagnosis.\n");
        return;
    }

    Ruangan *ruang = cariRuanganDokter(rs, USER_ID(*current_user));
    if (ruang == NULL) {
        printf("Dokter tidak terdaftar dalam ruangan manapun.\n");
        return;
    }

    if (isEmptyQueue(ruang->antrianPasienIds)) {
        printf("Tidak ada pasien dalam antrian.\n");
        return;
    }

    int pasienId = ruang->antrianPasienIds.buffer[ruang->antrianPasienIds.idxHead];
    printf("Mengambil pasien dengan ID: %d dari antrian.\n", pasienId);

    User *pasien = NULL;
    for (int i = 0; i < JUMLAHUSER(*lUser); i++) {
        if (USER_ID(USERS(*lUser, i)) == pasienId) {
            pasien = &USERS(*lUser, i);
            break;
        }
    }

    if (pasien == NULL) {
        printf("Pasien dengan ID %d tidak ditemukan.\n", pasienId);
        return;
    }

    printf("Melakukan pemeriksaan terhadap pasien: %s\n", USERNAME(*pasien));

    for (int i = 0; i < JUMLAH_PENYAKIT(*lPenyakit); i++) {
        Penyakit p = PENYAKIT_LIST(*lPenyakit, i);
        printf("Mengecek kemungkinan penyakit: %s\n", NAMA_PENYAKIT(p));

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

            strcpy(RIWAYAT_PENYAKIT(*pasien), NAMA_PENYAKIT(p));
            SudahDiagnosis[pasienId] = true;
            printf("Diagnosis berhasil! Pasien %s didiagnosis dengan: %s\n", USERNAME(*pasien), NAMA_PENYAKIT(p));
            return;
        } else {
            printf("Kriteria tidak cocok untuk penyakit: %s\n", NAMA_PENYAKIT(p));
        }
    }

    strcpy(RIWAYAT_PENYAKIT(*pasien), "-"); 
    SudahDiagnosis[pasienId] = false;
    printf("Diagnosis gagal: Tidak ada penyakit yang cocok untuk pasien %s.\n", USERNAME(*pasien));
}