#include "../header/ngobatin.h"

extern boolean SudahDiagnosis[CAPACITY_QUEUE];
boolean SudahNgobatin[CAPACITY_QUEUE] = {false};

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
            for (int j = 0; j < inv->data[i].jumlahobat; j++) {
                if (inv->data[i].obat[j] == id_obat) return;
            }
            if (inv->data[i].jumlahobat < MAX_OBAT) {
                inv->data[i].obat[inv->data[i].jumlahobat++] = id_obat;
            }
            return;
        }
    }

    if (inv->jumlahPasienwObat < CAPACITY) {
        int idx = inv->jumlahPasienwObat++;
        inv->data[idx].id = pasienId;
        inv->data[idx].jumlahobat = 1;
        inv->data[idx].obat[0] = id_obat;
        CreateEmptyStack(&inv->data[idx].perut);
    }
}

void ngobatin(User current_user, RumahSakit *rs, ListUser *lUser, ListObat *lObat,
              ListFormula *lFormula, ListPenyakit *lPenyakit, Inventory *inv) {
    if (strcmp(ROLE(current_user), "dokter") != 0) return;

    Ruangan *ruang = cariRuanganDokter(rs, USER_ID(current_user));
    if (!ruang || isEmptyQueue(ruang->antrianPasienIds)) return;

    int pasienId = ruang->antrianPasienIds.buffer[ruang->antrianPasienIds.idxHead];
    if (pasienId == 0) {
        printf("Pasien tidak valid.\n");
        return;
    }

    User pasien = GetUser(*lUser, pasienId);

    if (!SudahDiagnosis[pasienId]) {
        printf("Pasien belum didiagnosis.\n");
        return;
    }

    if (SudahNgobatin[pasienId]) {
        printf("Pasien sudah pernah diobati!\n");
        return;
    }

    // Temukan penyakitId dari nama penyakit
    int penyakitId = -1;
    for (int i = 0; i < JUMLAH_PENYAKIT(*lPenyakit); i++) {
        if (strcmp(NAMA_PENYAKIT(PENYAKIT_LIST(*lPenyakit, i)), RIWAYAT_PENYAKIT(pasien)) == 0) {
            penyakitId = ID_PENYAKIT(PENYAKIT_LIST(*lPenyakit, i));
            break;
        }
    }

    if (penyakitId == -1) {
        printf("Penyakit tidak ditemukan.\n");
        return;
    }

    // Kumpulkan semua obat untuk penyakit ini
    int ids[MAX_OBAT], urutans[MAX_OBAT];
    int count = 0;
    for (int i = 0; i < JUMLAH_FORMULA(*lFormula); i++) {
        Formula f = FORMULA_LIST(*lFormula, i);
        if (f.penyakit_id == penyakitId) {
            ids[count] = f.obat_id;
            urutans[count] = f.urutan;
            count++;
        }
    }

    if (count == 0) {
        printf("Tidak ada obat untuk penyakit ini.\n");
        return;
    }

    // Urutkan berdasarkan urutan_minum (bubble sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (urutans[j] > urutans[j + 1]) {
                int tmp = urutans[j]; urutans[j] = urutans[j + 1]; urutans[j + 1] = tmp;
                int tmpid = ids[j]; ids[j] = ids[j + 1]; ids[j + 1] = tmpid;
            }
        }
    }

    printf("Pasien %s akan menerima obat:\n", USERNAME(pasien));
    for (int i = 0; i < count; i++) {
        Obat o = GetObat(*lObat, ids[i]);
        printf("%d. %s\n", i + 1, NAMA_OBAT(o));
        TambahObatKeInventory(inv, pasienId, ids[i]);
    }

    SudahNgobatin[pasienId] = true;
}