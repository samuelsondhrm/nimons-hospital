/* File: room.h */
/* Deklarasi ADT Ruangan sebagai container config.txt */
#ifndef ROOM_H
#define ROOM_H

#define MAX_PASIEN 100
#define MAX_KOLOM_RUANGAN 26
#define MAX_BARIS_RUANGAN 26

typedef struct {
    int dokterId;               // 0 jika tidak ada dokter
    int pasienIds[MAX_PASIEN];  // max 100 pasien per ruangan
    int jumlahPasien;    
} Ruangan;

typedef struct {
    int rows, cols;
    Ruangan data[MAX_BARIS_RUANGAN][MAX_KOLOM_RUANGAN];    // Declaring ruangan di rumahsakit
    int kapasitasPerRuangan; // dibaca dari line 2 config file
} RumahSakit;

#endif