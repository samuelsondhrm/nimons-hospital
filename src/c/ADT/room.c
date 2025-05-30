#include "../../header/ADT/room.h"

void InitializeRumahSakit(RumahSakit *rs){
    rs->rows = 0;
    rs->cols = 0;
    for(int i = 0; i < MAX_BARIS_RUANGAN; i++){
        for(int j = 0; j < MAX_KOLOM_RUANGAN; j++){
            rs->data[i][j].dokterId = 0;
            rs->data[i][j].jumlahPasien = 0;
            CreateQueue(&rs->data[i][j].baris);
        }
    }
    rs->kapasitasPerRuangan = 0;
    rs->kapasitasBaris = 0;
}
void InitializePasien(Pasien *P){
    P->jumlahobat = 0;
    CreateEmptyStack(&P->perut);
}

void InitializeInventory(Inventory *I){
    I->jumlahPasienwObat = 0;
}