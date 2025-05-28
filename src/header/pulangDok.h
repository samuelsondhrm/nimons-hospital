#ifndef PULANGDOK_H
#define PULANGDOK_H

#include <stdio.h>
#include <string.h>
#include "ADT/room.h"
#include "ADT/stack.h"
#include "ADT/user.h"
#include "ADT/penyakit_dan_obat.h"

void salinPerutKeArray(Stack s, int arr[], int *count);

int cariPenyakitId(ListPenyakit lp, const char *nama);

void ambilResepUrut(ListFormula lf, int penyakitId, int resep[], int *count);

void cetakUrutanObat(int list[], int len, ListObat *lObat);

boolean samaUrutan(int a[], int na, int b[], int nb);

void pulangDok(User current_user, RumahSakit *rs, ListUser *lUser, Inventory *inv, ListFormula *lFormula, ListPenyakit *lPenyakit, ListObat *lObat);

#endif