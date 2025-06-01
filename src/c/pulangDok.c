#include "../header/pulangDok.h"

void bolehPulang(User current_user, Inventory *inv, const ListObat *lObat, const ListFormula *lFormula, const ListPenyakit *lPenyakit, RumahSakit *rs) {
    int pasienId = USER_ID(current_user);

    // Kasus 1: Belum menerima diagnosis
    if (!SudahDiagnosis[pasienId]) {
        printf("Kamu belum menerima diagnosis apapun dari dokter, jangan buru-buru pulang!\n");
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
    const char *penyakitPasien = RIWAYAT_PENYAKIT(current_user);
    ListStatik obatSeharusnya;
    CreateListStatik(&obatSeharusnya);

    for (int i = 0; i < JUMLAH_FORMULA(*lFormula); i++) {
        Formula f = FORMULA_LIST(*lFormula, i);

        for (int j = 0; j < JUMLAH_PENYAKIT(*lPenyakit); j++) {
            Penyakit p = PENYAKIT_LIST(*lPenyakit, j);
            if (ID_PENYAKIT(p) == f.penyakit_id && strcmp(NAMA_PENYAKIT(p), penyakitPasien) == 0) {
                insertLastList(&obatSeharusnya, f.obat_id);
                break;
            }
        }
    }

    boolean urutanBenar = true;
    Stack salinanPerut = *perut;

    if (listLength(obatSeharusnya) != salinanPerut.TOP + 1) {
        urutanBenar = false;
    } else {
        for (int i = listLength(obatSeharusnya) - 1; i >= 0; i--) {
            int top;
            Pop(&salinanPerut, &top);
            if (top != ELMT_LIST(obatSeharusnya, i)) {
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
            printf("%s", NAMA_OBAT(o));
            if (i != listLength(obatSeharusnya) - 1) printf(" -> ");
        }
        printf("\n");

        printf("Urutan obat yang kamu minum:\n");
        Stack tampilPerut = *perut;
        while (!IsEmptyStack(tampilPerut)) {
            int id;
            Pop(&tampilPerut, &id);
            Obat o = GetObat(*lObat, id);
            printf("%s", NAMA_OBAT(o));
            if (!IsEmptyStack(tampilPerut)) printf(" -> ");
        }
        printf("\n");

        printf("Silahkan kunjungi dokter untuk meminta penawar yang sesuai!\n");
        return;
    }

    // Kasus 4: Semua syarat terpenuhi
    printf("Dokter sedang memeriksa keadaanmu...\n");
    printf("Selamat! Kamu sudah dinyatakan sembuh oleh dokter. Silahkan pulang dan semoga sehat selalu!\n");

    // Reset status
    SudahDiagnosis[pasienId] = false;
    inv->data[idxInv].jumlahobat = 0;
    CreateEmptyStack(perut);

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