#ifndef SET_H
#define SET_H

#define MAX_OBAT 100
#include "room.h"

typedef struct {
    int id;
    int inventory[MAX_OBAT];
    int inventory_count;
} Pasien;                       // STRUCT INI MASIH HARUS DIGANTI SEIRING DIBUTUHKANNYA INVENTORY OBAT

/**
 * Mem-parse satu baris string yang berisi angka-angka dan menyimpannya ke array of int.
 * 
 * @param line      String input yang berisi angka-angka yang dipisahkan spasi.
 * @param arr       Output array untuk menyimpan hasil angka yang diparse.
 * @param count     Output jumlah angka yang berhasil diparse dan disimpan ke arr.
 */
void parseLineToInts(const char *line, int *arr, int *count);

/**
 * Membaca file konfigurasi rumah sakit dari file teks dan mengisi struktur RumahSakit dan data pasien.
 *
 * @param filename      Nama file konfigurasi (biasanya "config.txt").
 * @param rs            Pointer ke struktur RumahSakit yang akan diisi.
 * @param pasienData    Array data pasien (berisi ID dan inventory obat).
 */
void readHospitalConfig(const char *filename, RumahSakit *rs, Pasien pasienData[MAX_PASIEN]);

/**
 * Menyimpan keadaan rumah sakit dan data pasien (termasuk inventory obat) ke dalam file konfigurasi.
 *
 * @param filename      Nama file tempat konfigurasi disimpan.
 * @param rs            Struktur RumahSakit yang akan disimpan.
 * @param pasienData    Array data pasien yang akan disimpan ke file.
 */
void simpanKonfigurasi(const char *filename, RumahSakit rs, Pasien pasienData[MAX_PASIEN]);

#endif
