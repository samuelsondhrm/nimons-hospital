#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "ADT/penyakit_dan_obat.h"
#include "checkUp.h"

// manggil variabel global dari main
extern boolean SudahDiagnosis[CAPACITY_QUEUE];

void diagnosis(User *current_user, RumahSakit *rs, ListUser *lUser, ListPenyakit *lPenyakit);

#endif