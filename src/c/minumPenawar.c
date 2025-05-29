#include "../header/minumPenawar.h"

void minumPenawar(User current_user, Inventory *inv, ListObat *lObat) {
    int pasienId = USER_ID(current_user);

    int idxInv = -1;
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == pasienId) {
            idxInv = i;
            break;
        }
    }

    if (idxInv == -1) {
        printf("Pasien tidak ditemukan.\n");
        return;
    }

    Stack *perut = &inv->data[idxInv].perut;

    if (isEmptyStack(*perut)) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    int obatId;
    Pop(perut, &obatId);

    Obat o = GetObat(*lObat, obatId);

    if (inv->data[idxInv].jumlahobat < MAX_OBAT) {
        inv->data[idxInv].obat[inv->data[idxInv].jumlahobat++] = obatId;
    }

    printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", NAMA_OBAT(o));
}
