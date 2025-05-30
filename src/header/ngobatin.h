#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "ADT/map.h"
#include "diagnosis.h"

void TambahObatKeInventory(Inventory *inv, int pasienId, int id_obat);
void ngobatin(User current_user, RumahSakit *rs, ListUser *lUser, ListObat *lObat, ListFormula *lFormula, ListPenyakit *lPenyakit, Inventory *inv);

#endif
