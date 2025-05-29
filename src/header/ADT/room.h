/* File: room.h */
/* Deklarasi ADT Ruangan sebagai container config.txt */
#ifndef ROOM_H
#define ROOM_H

#define MAX_OBAT 10
#define MAX_KOLOM_RUANGAN 26
#define MAX_BARIS_RUANGAN 26
#include "queue.h"
#include "matrix.h"
#include "stack.h"

typedef struct {
    int dokterId;               // 0 jika tidak ada dokter
    Queue antrianPasienIds;            // max 100 pasien per ruangan
} Ruangan;

typedef struct {
    int rows, cols;
    Ruangan data[MAX_BARIS_RUANGAN][MAX_KOLOM_RUANGAN];     // Declaring ruangan di rumahsakit
    int kapasitasPerRuangan;                                // dibaca dari line 2 config file
    int kapasitasBaris;                                     // max panjang baris
} RumahSakit;

typedef struct{
    int id;
    int jumlahobat;
    int obat[MAX_OBAT];
    Stack perut;
} Pasien;

typedef struct {
    int jumlahPasienwObat;
    Pasien data[CAPACITY_QUEUE];                                            // data[ID_User][ID_Obat], ID_Obat valid kecuali -1 (MARK)
} Inventory;                                                // MIsal data[1][2,3,-1,-1,-1,..,-1] bearti pasien ID 1, punya obat ID 2 dan 3

void InitializeRumahSakit(RumahSakit *rs);
void InitializePasien(Pasien *P);
void InitializeInventory(Inventory *I);
#endif