#ifndef NGOBATIN_H
#define NGOBATIN_H

#include "../src/header/ADT/user.h"
#include "../src/header/ADT/penyakit_dan_obat.h"
#include "../src/header/ADT/map.h"
#include "../src/header/ADT/liststatik.h"
#include "../src/header/ADT/room.h"
#include <stdbool.h>

void ngobatin(User current_user, RumahSakit *rs, ListUser *lUser, ListObat *lObat, ListFormula *lFormula, ListPenyakit *lPenyakit, Inventory *inv);

#endif
