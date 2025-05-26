#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/ADT/penyakit_dan_obat.h"
#include "../header/ADT/user.h"

// ==================== UTILITIES ====================
int string_to_int(const char *str);
float string_to_float(const char *str);

// ==================== BAGIAN OBAT ====================
void parse_obat_csv(const char *filename, ListObat *l);
void tulis_obat_csv(const char *filename, ListObat l);

// ==================== BAGIAN PENYAKIT ====================
void parse_penyakit_csv(const char *filename, ListPenyakit *l);
void tulis_penyakit_csv(const char *filename, ListPenyakit l);

// ==================== BAGIAN OBATPENYAKIT (FORMULA) ====================
void parse_obatpenyakit_csv(const char *filename, ListFormula *l);
void tulis_obatpenyakit_csv(const char *filename, ListFormula l);

// ==================== BAGIAN USER ====================
void parse_user_csv(const char *filename, ListUser *l);
void tulis_user_csv(const char *filename, ListUser *l);

#endif

