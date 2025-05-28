#include "../header/pulangDok.h"

void salinPerutKeArray(Stack s, int arr[], int *count) {
    *count = 0;
    Stack temp;
    CreateEmptyStack(&temp);
    while (!IsEmptyStack(s)) {
        int val;
        Pop(&s, &val);
        temp.T[temp.TOP + 1] = val;
        temp.TOP++;
    }
    while (!IsEmptyStack(temp)) {
        int val;
        Pop(&temp, &val);
        arr[*count] = val;
        (*count)++;
    }
}

int cariPenyakitId(ListPenyakit lp, const char *nama) {
    for (int i = 0; i < JUMLAH_PENYAKIT(lp); i++) {
        if (strcmp(NAMA_PENYAKIT(PENYAKIT_LIST(lp, i)), nama) == 0) {
            return ID_PENYAKIT(PENYAKIT_LIST(lp, i));
        }
    }
    return -1;
}

void ambilResepUrut(ListFormula lf, int penyakitId, int resep[], int *count) {
    *count = 0;
    for (int urut = 1; urut <= MAX_OBAT; urut++) {
        for (int i = 0; i < JUMLAH_FORMULA(lf); i++) {
            Formula f = FORMULA_LIST(lf, i);
            if (f.penyakit_id == penyakitId && f.urutan == urut) {
                resep[*count] = f.obat_id;
                (*count)++;
            }
        }
    }
}

void cetakUrutanObat(int list[], int len, ListObat *lObat) {
    for (int i = 0; i < len; i++) {
        Obat o = GetObat(*lObat, list[i]);
        printf("%s", o.nama);
        if (i < len - 1) {
            printf(" -> ");
        }
    }
    printf("\n");
}

boolean samaUrutan(int a[], int na, int b[], int nb) {
    if (na != nb) return false;
    for (int i = 0; i < na; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

void pulangDok(User current_user, RumahSakit *rs, ListUser *lUser, Inventory *inv, ListFormula *lFormula, ListPenyakit *lPenyakit, ListObat *lObat) {
    int pasienId = USER_ID(current_user);

    if (strcmp(RIWAYAT_PENYAKIT(current_user), "-") == 0 || strlen(RIWAYAT_PENYAKIT(current_user)) == 0) {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return;
    }

    printf("Dokter sedang memeriksa keadaanmu...\n");

    Pasien *pasien = NULL;
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == pasienId) {
            pasien = &inv->data[i];
            break;
        }
    }

    if (!pasien) {
        printf("Data pasien tidak ditemukan di inventory.\n");
        return;
    }

    int penyakitId = cariPenyakitId(*lPenyakit, RIWAYAT_PENYAKIT(current_user));

    if (penyakitId == -1) {
        printf("Riwayat penyakit tidak dikenali.\n");
        return;
    }

    int resep[MAX_OBAT], nResep;
    ambilResepUrut(*lFormula, penyakitId, resep, &nResep);

    int perut[MAX_OBAT], nPerut;
    salinPerutKeArray(pasien->perut, perut, &nPerut);

    // Kasus 2: belum habis
    if (nPerut < nResep) {
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }

    // Kasus 3: salah urutan
    if (!samaUrutan(resep, nResep, perut, nPerut)) {
        printf("Maaf, tapi kamu masih belum bisa pulang!\n");
        printf("Urutan peminuman obat yang diharapkan:\n");
        cetakUrutanObat(resep, nResep, lObat);
        printf("Urutan obat yang kamu minum\n");
        cetakUrutanObat(perut, nPerut, lObat);
        printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai !\n");
        return;
    }

    // Kasus 4: sembuh
    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");

    // Hapus pasien dari ruangan
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            Ruangan *r = &rs->data[i][j];
            for (int k = 0; k < r->jumlahPasien; k++) {
                if (r->pasienIds[k] == pasienId) {
                    for (int l = k; l < r->jumlahPasien - 1; l++) {
                        r->pasienIds[l] = r->pasienIds[l + 1];
                    }
                    r->jumlahPasien--;
                    break;
                }
            }
        }
    }

    CreateEmptyStack(&pasien->perut);
    pasien->jumlahobat = 0;
}
