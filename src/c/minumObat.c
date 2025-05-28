#include "minumObat.h"

Pasien* cariPasienById(Inventory *inv, int userId) {
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == userId) {
            return &inv->data[i];
        }
    }
    return NULL;
}

void minumObat(int userId, ListObat *lObat, Inventory *inv) {

    Pasien *pasien = cariPasienById(inv, userId);
    if (pasien == NULL) {
        printf("Data pasien tidak ditemukan.\n");
        return;
    }

    if (pasien->jumlahobat == 0) {
        printf("Inventory kosong. Tidak ada obat untuk diminum!\n");
        return;
    }

    // Daftar obat
    printf("============ DAFTAR OBAT ============\n");
    for (int i = 0; i < pasien->jumlahobat; i++) {
        Obat o = GetObat(*lObat, pasien->obat[i]); 
        printf("%d. %s\n", i + 1, o.nama);
    }

    printf("Pilih obat untuk diminum: ");
    int pilihan;
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > pasien->jumlahobat) {
        printf("Pilihan obat tidak tersedia! Mohon masukkan ulang pilihan anda:\n");
        return;
    }

    int obatId = pasien->obat[pilihan - 1];
    Obat o = GetObat(*lObat, obatId);
    Push(&pasien->perut, obatId);       // Masukkan ke stack perut (F17)

    // Hapus dari inventory
    for (int i = pilihan - 1; i < pasien->jumlahobat - 1; i++) {
        pasien->obat[i] = pasien->obat[i + 1];
    }
    pasien->jumlahobat--;

    printf("GLEKGLEKGLEK... %s berhasil diminum!!!\n", o.nama);
}
