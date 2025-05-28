#include "../header/minumPenawar.h"

Pasien* cariPasienById(Inventory *inv, int userId) {
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == userId) {
            return &inv->data[i];
        }
    }
    return NULL;
}

void minumPenawar(int userId, ListObat *lObat, Inventory *inv) {
    Pasien *pasien = cariPasienById(inv, userId);
    if (pasien == NULL) {
        printf("Data pasien tidak ditemukan.\n");
        return;
    }

    if (IsEmpty(pasien->perut)) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    int obatId;
    Pop(&pasien->perut, &obatId);

    if (pasien->jumlahobat < MAX_OBAT) {
        pasien->obat[pasien->jumlahobat++] = obatId;
        Obat o = GetObat(*lObat, obatId);
        printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", o.nama);
    } else {
        printf("Inventory penuh! Tidak bisa mengembalikan obat.\n");
    }
}
