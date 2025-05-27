#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "../src/header/ADT/user.h"
#include "../src/header/ADT/penyakit_dan_obat.h"
#include "../src/header/ADT/room.h"

void diagnosis(User *current_user, RumahSakit *rs, ListUser *lUser, ListPenyakit *lPenyakit);

#endif