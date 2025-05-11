#ifndef PARSER_USER_CSV_H
#define PARSER_USER_CSV_H

#include "user.h"

// Mengubah string menjadi integer (alternatif dari atoi)
int string_to_int(const char *str);

// Mengubah string menjadi float (alternatif dari atof)
float string_to_float(const char *str);

// Membaca isi file CSV dan menyimpannya ke array User, serta memperbarui jumlah user
void parse_user_csv(const char *filename, ListUser *ListUser);

// Menuliskan isi array User ke file CSV dengan format yang sama seperti dibaca
void tulis_user_csv(const char *filename, ListUser ListUser);

// Menampilkan isi array User ke layar secara terformat
void tampilkan_pasien(ListUser ListUser);

#endif
