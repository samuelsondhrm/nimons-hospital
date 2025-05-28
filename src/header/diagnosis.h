#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "ADT/user.h"
#include "ADT/penyakit_dan_obat.h"
#include "ADT/room.h"
#include "checkUp.h"

void diagnosis(User *current_user, RumahSakit *rs, ListUser *lUser, ListPenyakit *lPenyakit);

#endif