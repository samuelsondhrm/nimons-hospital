#include "../header/minumPenawar.h"

static void strip_newline(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n' || str[i] == '\r') {
            str[i] = '\0';
            break;
        }
    }
}

void minumPenawar(User current_user, Inventory *inv, const ListObat *lObat) {
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

    if (IsEmptyStack(*perut)) {
        printf("Perut kosong!! Belum ada obat yang dimakan.\n");
        return;
    }

    int obatId;
    Pop(perut, &obatId);

    Obat o = GetObat(*lObat, obatId);

    // Copy nama to buffer 
    char nama[100];
    strncpy(nama, NAMA_OBAT(o), sizeof(nama) - 1);
    nama[sizeof(nama) - 1] = '\0';

    // Strip newline and carriage return
    strip_newline(nama);

    if (inv->data[idxInv].jumlahobat < MAX_OBAT) {
        inv->data[idxInv].obat[inv->data[idxInv].jumlahobat++] = obatId;
    }
    printf("Uwekkk!!! %s keluar dan kembali ke inventory\n", nama);
}
