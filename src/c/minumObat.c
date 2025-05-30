#include "../header/minumObat.h"


void minumObat(User current_user, Inventory *inv, RumahSakit *rs, ListObat *lObat) {

    int pasienId = USER_ID(current_user);

    // Cari inventory pasien
    int idxInv = -1;
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == pasienId) {
            idxInv = i;
            break;
        }
    }

    if (idxInv == -1 || inv->data[idxInv].jumlahobat == 0) {
        printf("Tidak ada obat dalam inventory!\n");
        return;
    }

    // Tampilkan daftar obat
    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < inv->data[idxInv].jumlahobat; i++) {
        int obatId = inv->data[idxInv].obat[i];
        Obat o = GetObat(*lObat, obatId);
        printf("%d. %s\n", i + 1, NAMA_OBAT(o));
    }

    printf("\nPilih obat untuk diminum: ");
    int pilihan;
    scanf("%d /n", &pilihan);

    if (pilihan < 1 || pilihan > inv->data[idxInv].jumlahobat) {
        printf("Pilihan nomor tidak tersedia!\n");
        return;
    }

    int obatId = inv->data[idxInv].obat[pilihan - 1];
    Obat o = GetObat(*lObat, obatId);

    // Push ke stack perut (untuk F17)
    for (int i = 0; i < rs->rows; i++) {
        for (int j = 0; j < rs->cols; j++) {
            Queue q = rs->data[i][j].antrianPasienIds;
            for (int k = 0; k < lengthQueue(q); k++) {
                int idx = (q.idxHead + k) % CAPACITY_QUEUE;
                if (q.buffer[idx] == pasienId) {
                    Push(&inv->data[idxInv].perut, obatId);
                    printf("\nGLEKGLEKGLEK... %s berhasil diminum!!!\n", NAMA_OBAT(o));

                    // Hapus obat diminum dari inventory
                    for (int x = pilihan - 1; x < inv->data[idxInv].jumlahobat - 1; x++) {
                        inv->data[idxInv].obat[x] = inv->data[idxInv].obat[x + 1];
                    }
                    inv->data[idxInv].jumlahobat--;
                    return;
                }
            }
        }
    }
}
