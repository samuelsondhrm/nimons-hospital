/* File: parser_config_txt.h */
/* Parser config.txt, dan juga menulis */
#ifndef PARSER_CONFIG_TXT_H
#define PARSER_CONFIG_TXT_H

#include <stdio.h>
#include "ADT/room.h"   // Definisi RumahSakit, Ruangan, Inventory, Pasien, dll

// Membaca file konfigurasi rumah sakit dan mengisi data RumahSakit dan Inventory
// maxAntrianLuar akan diisi dengan kapasitas antrian baris
// Return 1 jika berhasil, 0 jika gagal
int loadConfig(const char *filename, RumahSakit *rs, Inventory *invntry, int *maxAntrianLuar);

// Membaca satu baris dari file ke buffer, return 0 jika EOF, 1 jika berhasil baca
int readLine(FILE *fp, char *buffer, int maxLen);

// Mendapatkan integer berikutnya dari pointer string, return -1 jika tidak ada angka lagi
int nextInt(const char **p);

// Parsing satu baris konfigurasi ruangan dan mengisi struktur Ruangan
void parseRuanganLine(char *line, Ruangan *ruangan, int kapasitasPerRuangan, int kapasitasBaris);

// Parsing satu baris data pasien dengan daftar obat dan mengisi Inventory
void parsePasienObatLine(char *line, Inventory *invntry);

#endif
