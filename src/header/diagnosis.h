#ifndef DIAGNOSIS_H
#define DIAGNOSIS_H

#include "ADT/penyakit_dan_obat.h"
#include "checkUp.h"

// variabel global
boolean SudahDiagnosis[CAPACITY_QUEUE];

void diagnosis(User *current_user, RumahSakit *rs, ListUser *lUser, ListPenyakit *lPenyakit, boolean SudahDiagnosis[CAPACITY_QUEUE]);

#endif