#include "../../header/ADT/penyakit_dan_obat.h"

/* ********** TYPE OBAT ********** */

void CreateObat(Obat *o) {
    o->id = 0;
    strcpy(o->nama, "");
}

void InitializeListObat(ListObat *l) {
    l->jumlahobat = 0;
}

Obat GetObat(ListObat l, int id){
    for(int i = 0; i<JUMLAH_OBAT(l); i++){
        if(ID_OBAT(OBAT_LIST(l, i)) == id){
            return OBAT_LIST(l,i);
        }
    }
    Obat ERR_MSG;
    CreateObat(&ERR_MSG);
    ID_OBAT(ERR_MSG) = -1;
    return ERR_MSG; // Kalau id Obat -1, bearti error
}

void DelObat(ListObat *l, int id, Obat *buffer) {
    for (int i = 0; i < JUMLAH_OBAT(*l); i++) {
        if (ID_OBAT(OBAT_LIST(*l, i)) == id) {
            *buffer = l->obats[i];
            for (int j = i; j < JUMLAH_OBAT(*l) - 1; j++) {
                l->obats[j] = l->obats[j + 1];
            }
            l->jumlahobat--;
            break;
        }
    }
}

void InsObat(ListObat *l, Obat buffer) {
    if (JUMLAH_OBAT(*l) < MAX_OBAT && ID_OBAT(buffer) > 0) {
        for (int i = 0; i < JUMLAH_OBAT(*l); i++) {
            if (ID_OBAT(OBAT_LIST(*l, i)) == ID_OBAT(buffer)) {
                return; 
            }
            else if (ID_OBAT(OBAT_LIST(*l, i)) > ID_OBAT(buffer)) {
                for (int j = JUMLAH_OBAT(*l); j > i; j--) {
                    l->obats[j] = l->obats[j - 1];
                }
                l->obats[i] = buffer;
                l->jumlahobat++;
                return;
            }
        }
        // Jika ID buffer paling besar, tambahkan di akhir
        l->obats[JUMLAH_OBAT(*l)] = buffer;
        l->jumlahobat++;
    }
}

void tampilkan_obat(ListObat l) {
    for (int i = 0; i < JUMLAH_OBAT(l); i++) {
        Obat o = OBAT_LIST(l, i);
        printf("Penyakit %d:\n", i + 1);
        printf("   ID: %d\n", ID_OBAT(o));
        printf("   Nama: %s\n", NAMA_OBAT(o));
    }
}



/* ********** TYPE PENYAKIT ********** */
void CreatePenyakit(Penyakit *p) {
    p->id = 0;
    strcpy(p->nama, "");
    p->suhu_min = 0;
    p->suhu_max = 0;
    p->sys_min = 0;
    p->sys_max = 0;
    p->dias_min = 0;
    p->dias_max = 0;
    p->detak_min = 0;
    p->detak_max = 0;
    p->saturasi_min = 0;
    p->saturasi_max = 0;
    p->gula_min = 0;
    p->gula_max = 0;
    p->berat_min = 0;
    p->berat_max = 0;
    p->tinggi_min = 0;
    p->tinggi_max = 0;
    p->kolesterol_min = 0;
    p->kolesterol_max = 0;
    p->trombosit_min = 0;
    p->trombosit_max = 0;
}

void InitializeListPenyakit(ListPenyakit *l) {
    l->jumlahpenyakit = 0;
}

Penyakit GetPenyakit(ListPenyakit l, int id) {
    for (int i = 0; i < JUMLAH_PENYAKIT(l); i++) {
        if (ID_PENYAKIT(PENYAKIT_LIST(l, i)) == id) {
            return PENYAKIT_LIST(l, i);
        }
    }
    Penyakit ERR_MSG;
    CreatePenyakit(&ERR_MSG);
    ID_PENYAKIT(ERR_MSG) = -1;
    return ERR_MSG; // Jika tidak ditemukan, kembalikan penyakit dengan id = -1
}

void DelPenyakit(ListPenyakit *l, int id, Penyakit *buffer) {
    for (int i = 0; i < JUMLAH_PENYAKIT(*l); i++) {
        if (ID_PENYAKIT(PENYAKIT_LIST(*l, i)) == id) {
            *buffer = l->penyakits[i];
            for (int j = i; j < JUMLAH_PENYAKIT(*l) - 1; j++) {
                l->penyakits[j] = l->penyakits[j + 1];
            }
            l->jumlahpenyakit--;
            break;
        }
    }
}

void InsPenyakit(ListPenyakit *l, Penyakit buffer) {
    if (JUMLAH_PENYAKIT(*l) < MAX_PENYAKIT && ID_PENYAKIT(buffer) > 0) {
        for (int i = 0; i < JUMLAH_PENYAKIT(*l); i++) {
            if (ID_PENYAKIT(PENYAKIT_LIST(*l, i)) == ID_PENYAKIT(buffer)) {
                return; 
            } 
            else if (ID_PENYAKIT(PENYAKIT_LIST(*l, i)) > ID_PENYAKIT(buffer)) {
                for (int j = JUMLAH_PENYAKIT(*l); j > i; j--) {
                    l->penyakits[j] = l->penyakits[j - 1];
                }
                l->penyakits[i] = buffer;
                l->jumlahpenyakit++;
                return;
            }
        }
        // jika id buffer terbesar, tambahkan di akhir
        l->penyakits[JUMLAH_PENYAKIT(*l)] = buffer;
        l->jumlahpenyakit++;
    }
}

void tampilkan_penyakit(ListPenyakit l) {
    for (int i = 0; i < JUMLAH_PENYAKIT(l); i++) {
        Penyakit p = PENYAKIT_LIST(l,i);
        printf("Penyakit %d:\n", i + 1);
        printf("  ID: %d\n", ID_PENYAKIT(p));
        printf("  Nama: %s\n", NAMA_PENYAKIT(p));
        printf("  Suhu Tubuh: %.1f - %.1f °C\n", SUHU_MIN(p), SUHU_MAX(p));
        printf("  Tekanan Darah: %d/%d - %d/%d mmHg\n", SYS_MIN(p), DIAS_MIN(p), SYS_MAX(p), DIAS_MAX(p));
        printf("  Detak Jantung: %d - %d bpm\n", DETAK_MIN(p), DETAK_MAX(p));
        printf("  Saturasi Oksigen: %.1f - %.1f %%\n", SATURASI_MIN(p), SATURASI_MAX(p));
        printf("  Gula Darah: %.1f - %.1f mg/dL\n", GULA_MIN(p), GULA_MAX(p));
        printf("  Berat Badan: %.1f - %.1f kg\n", BERAT_MIN(p), BERAT_MAX(p));
        printf("  Tinggi Badan: %d - %d cm\n", TINGGI_MIN(p), TINGGI_MAX(p));
        printf("  Kolesterol Total: %d - %d mg/dL\n", KOLESTEROL_MIN(p), KOLESTEROL_MAX(p));
        printf("  Trombosit: %d - %d ribu/uL\n", TROMBOSIT_MIN(p), TROMBOSIT_MAX(p));
        printf("\n");
    }
}



/* ********** TYPE FORMULA ********** */
void CreateFormula(Formula *f) {
    f->obat_id = 0;
    f->penyakit_id = 0;
    f->urutan = 0;
}

void InitializeListFormula(ListFormula *l) {
    l->jumlahformula = 0;
}

Formula GetFormula(ListFormula l, int obat_id, int penyakit_id) {
    for (int i = 0; i < JUMLAH_FORMULA(l); i++) {
        if (OBAT_ID(FORMULA_LIST(l, i)) == obat_id && PENYAKIT_ID(FORMULA_LIST(l, i)) == penyakit_id) {
            return FORMULA_LIST(l, i);
        }
    }
    Formula ERR_MSG;
    CreateFormula(&ERR_MSG);
    OBAT_ID(ERR_MSG) = -1;
    PENYAKIT_ID(ERR_MSG) = -1;
    return ERR_MSG; 
}

void DelFormula(ListFormula *l, int obat_id, int penyakit_id, Formula *buffer) {
    for (int i = 0; i < JUMLAH_FORMULA(*l); i++) {
        if (OBAT_ID(FORMULA_LIST(*l, i)) == obat_id && PENYAKIT_ID(FORMULA_LIST(*l, i)) == penyakit_id) {
            *buffer = l->formulas[i];
            for (int j = i; j < JUMLAH_FORMULA(*l) - 1; j++) {
                l->formulas[j] = l->formulas[j + 1];
            }
            l->jumlahformula--;
            break;
        }
    }
}

void InsFormula(ListFormula *l, Formula buffer) {
    if (JUMLAH_FORMULA(*l) < MAX_FORMULA && buffer.obat_id > 0 && buffer.penyakit_id > 0) {
        for (int i = 0; i < JUMLAH_FORMULA(*l); i++) {
            if (OBAT_ID(FORMULA_LIST(*l, i)) == buffer.obat_id && PENYAKIT_ID(FORMULA_LIST(*l, i)) == buffer.penyakit_id) {
                return; 
            }
        }
        l->formulas[JUMLAH_FORMULA(*l)] = buffer;
        l->jumlahformula++;
    }
}

void tampilkan_obatpenyakit(ListFormula l) {
    for (int i = 0; i < JUMLAH_FORMULA(l); i++) {
        Formula op = FORMULA_LIST(l,i);
        printf("Relasi %d:\n", i + 1);
        printf("   Obat ID     : %d\n", OBAT_ID(op));
        printf("   Penyakit ID : %d\n", PENYAKIT_ID(op));
        printf("   Urutan      : %d\n", URUTAN(op));
    }
}
