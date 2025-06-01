#include "../header/ngobatin.h"
#include "../header/ngobatin.h"

// cari ruangan dokter berdasarkan ID

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

void TambahObatKeInventory(Inventory *inv, int pasienId, int id_obat) {
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == pasienId) {
            if (inv->data[i].jumlahobat < MAX_OBAT) {
                inv->data[i].obat[inv->data[i].jumlahobat++] = id_obat;
            }
            return;
        }
    }
    
    inv->data[inv->jumlahPasienwObat].id = pasienId;
    inv->data[inv->jumlahPasienwObat].jumlahobat = 1;
    inv->data[inv->jumlahPasienwObat].obat[0] = id_obat;
    inv->jumlahPasienwObat++;
}

void ngobatin(User current_user, RumahSakit *rs, ListUser *lUser, ListObat *lObat, ListFormula *lFormula, ListPenyakit *lPenyakit, Inventory *inv) {
    if (strcmp(ROLE(current_user), "Dokter") != 0) { // cuma dokter yang bisa
        return;
    }

    // Cari ruangan dokter
    Ruangan *ruang = cariRuanganDokter(rs, USER_ID(current_user));
     if (ruang == NULL || isEmptyQueue(ruang->antrianPasienIds)) {
        
        return; // tidak ada pasien
    }

    // Ambil ID pasien paling pertama di ruangan
    int pasienId =  ruang->antrianPasienIds.buffer[ruang->antrianPasienIds.idxHead];
    User pasien = GetUser(*lUser, pasienId);

    printf("Dokter sedang mengobati pasien!\n");

    // Cek apakah sudah ada diagnosis
    if (!SudahDiagnosis[pasienId]) {
        printf("anda belum di diagnosis");
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
            if (strcmp(NAMA_PENYAKIT(p), RIWAYAT_PENYAKIT(pasien)) == 0 || ID_PENYAKIT(p) == f.penyakit_id) {
                 printf("-> obat cocok, dan akan ditambahkan ke inventory pasien.\n");
                Obat o = GetObat(*lObat, f.obat_id);

                printf("%d. %s\n", count++, NAMA_OBAT(o));

                TambahObatKeInventory(inv, pasienId, f.obat_id);
            }
        }
    }

    if (count == 1) {
    printf("Tidak ada obat yang cocok untuk penyakit %s.\n", RIWAYAT_PENYAKIT(pasien));
    }

}