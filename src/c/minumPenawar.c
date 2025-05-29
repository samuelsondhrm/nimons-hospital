#include "../header/minumPenawar.h"

void minumPenawar(User current_user, Inventory *inv) {
    int pasienId = USER_ID(current_user);

    int idxInv = -1;
    for (int i = 0; i < inv->jumlahPasienwObat; i++) {
        if (inv->data[i].id == pasienId) {
            idxInv = i;
            break;
        }
    }

    Stack *perut = &inv->data[idxInv].perut;

    if (idxInv == -1 || isEmptyStack(*perut)) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }


    int obatId;
    Pop(perut, &obatId);

    // Penambahan kembali ke inventory
    if (inv->data[idxInv].jumlahobat < MAX_OBAT) {
        inv->data[idxInv].obat[inv->data[idxInv].jumlahobat++] = obatId;
    }

    printf("Uwekkk!!! Obat dengan ID %d keluar dan kembali ke inventory\n", obatId);
}
