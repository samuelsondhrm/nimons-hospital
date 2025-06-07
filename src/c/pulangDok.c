#include "../header/pulangDok.h"

// Hilangkan karakter newline atau carriage return
static void strip_newline(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            break;
        }
    }
}

void bolehPulang(User current_user, Inventory *inv, const ListObat *lObat, const ListFormula *lFormula, const ListPenyakit *lPenyakit, RumahSakit *rs, ListUser *lUser) {
    int pasienId = USER_ID(current_user);

    // Kasus 1: Belum menerima diagnosis
    if (!SudahDiagnosis[pasienId]) {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
        return;
    }

    // Ambil riwayat penyakit
    const char *penyakitPasien = RIWAYAT_PENYAKIT(current_user);
    if (penyakitPasien == NULL || strcmp(penyakitPasien, "-") == 0) {
        printf("Kamu tidak memiliki penyakit terdeteksi, jadi tidak perlu pengobatan.\n");
        return;
    }

    int idxInv = -1;
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == pasienId) {
            idxInv = i;
            break;
        }
    }

    // Kasus 2: Masih ada obat di inventory atau belum minum apa-apa
    if (idxInv == -1) {
        printf("Dokter sedang memeriksa keadaanmu...\n");
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }

    Stack *perut = &inv->data[idxInv].perut;

    if (inv->data[idxInv].jumlahobat > 0 || IsEmptyStack(*perut)) {
        printf("Dokter sedang memeriksa keadaanmu...\n");
        printf("Masih ada obat yang belum kamu habiskan, minum semuanya dulu yukk!\n");
        return;
    }

    // Kasus 3: Urutan obat tidak sesuai
    ListStatik obatSeharusnya;
    CreateListStatik(&obatSeharusnya);

    int penyakitId = -1;
    for (int i = 0; i < JUMLAH_PENYAKIT(*lPenyakit); i++) {
        Penyakit p = PENYAKIT_LIST(*lPenyakit, i);

        char nama[100];
        strncpy(nama, NAMA_PENYAKIT(p), sizeof(nama) - 1);
        nama[sizeof(nama) - 1] = '\0';
        strip_newline(nama);

        if (strcmp(nama, penyakitPasien) == 0) {
            penyakitId = ID_PENYAKIT(p);
            break;
        }
    }

    if (penyakitId != -1) {
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

        // Bubble sort berdasarkan urutan
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (urutans[j] > urutans[j + 1]) {
                    int tmp = urutans[j]; urutans[j] = urutans[j + 1]; urutans[j + 1] = tmp;
                    int tmpid = ids[j]; ids[j] = ids[j + 1]; ids[j + 1] = tmpid;
                }
            }
        }

        // Masukkan ke list obat yang seharusnya
        for (int i = 0; i < count; i++) {
            insertLastList(&obatSeharusnya, ids[i]);
        }
    }

    boolean urutanBenar = true;
    Stack salinanPerut = *perut;

    // Buat array isi stack valid (> 0)
    int stackValid[CAPACITY_STCK];
    int countValid = 0;
    for (int i = 0; i <= salinanPerut.TOP; i++) {
        if (salinanPerut.T[i] > 0) {
            stackValid[countValid++] = salinanPerut.T[i];
        }
    }

    if (listLength(obatSeharusnya) != countValid) {
        urutanBenar = false;
    } else {
        for (int i = 0; i < countValid; i++) {
            int expected = ELMT_LIST(obatSeharusnya, i);
            int actual = stackValid[i];  // FIX: tidak dibalik
            if (expected != actual) {
                urutanBenar = false;
                break;
            }
        }
    }

    if (!urutanBenar) {
        printf("Dokter sedang memeriksa keadaanmu...\n");
        printf("Maaf, tapi kamu masih belum bisa pulang!\n");

        printf("Urutan peminuman obat yang diharapkan:\n");
        for (int i = 0; i < listLength(obatSeharusnya); i++) {
            Obat o = GetObat(*lObat, ELMT_LIST(obatSeharusnya, i));
            char nama[100];
            strncpy(nama, NAMA_OBAT(o), sizeof(nama) - 1);
            nama[sizeof(nama) - 1] = '\0';
            strip_newline(nama);
            if (i > 0) printf(" -> ");
            printf("%s", nama);
        }
        printf("\n");

        printf("Urutan obat yang kamu minum:\n");
        for (int i = 0; i < countValid; i++) {
            Obat o = GetObat(*lObat, stackValid[i]);
            char nama[100];
            strncpy(nama, NAMA_OBAT(o), sizeof(nama) - 1);
            nama[sizeof(nama) - 1] = '\0';
            strip_newline(nama);
            if (i > 0) printf(" -> ");
            printf("%s", nama);
            }
            
        printf("\nSilahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
        return;
    }

    // Kasus 4: Semua syarat terpenuhi
    printf("Dokter sedang memeriksa keadaanmu...\n");
    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");

    // Reset status
    SudahDiagnosis[pasienId] = false;
    inv->data[idxInv].jumlahobat = 0;
    CreateEmptyStack(perut);
    
    // Reset riwayat penyakit pasien
    for (int i = 0; i < JUMLAHUSER(*lUser); i++) {
        if (USER_ID(USERS(*lUser, i)) == pasienId) {
            strcpy(RIWAYAT_PENYAKIT(USERS(*lUser, i)), "-");
            break;
        }
    }

    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            Queue *q = &rs->data[i][j].antrianPasienIds;
            int kapasitas = rs->kapasitasPerRuangan;
            int len = lengthQueue(*q);

            for (int k = 0; k < kapasitas && k < len; k++) {
                int idx = (q->idxHead + k) % CAPACITY_QUEUE;
                if (q->buffer[idx] == pasienId && k == 0) {
                    int pasienKeluar;
                    dequeue(q, &pasienKeluar);
                    return;
                }
            }
        }
    }
}
