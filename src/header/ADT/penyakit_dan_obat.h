/* File: penyakit_dan_obat.h */
/* Deklarasi ADT obat,penyakit, dan formula sebagai container data obat.csv, penyakit.csv, obat_penyakit.csv */

#ifndef PENYAKIT_DAN_OBAT_H
#define PENYAKIT_DAN_OBAT_H

#include <string.h>
#include <stdio.h>

#define MAX_OBAT 100
#define MAX_PENYAKIT 100
#define MAX_FORMULA 100
#define MAX_NAMA 100
#define MAX_FIELD 128

/* ********** TYPE OBAT ********** */
typedef struct {
    int id;
    char nama[MAX_NAMA];
} Obat;

typedef struct {
    Obat obats[MAX_OBAT];
    int jumlahobat;
} ListObat;  // ListObat adalah list rata kiri yang diurut menaik berdasarkan ID obat
             // Semua jenis operasi terhadap obat menggunakan ID obat, bukan index
             // ID obat > 0

/* ********** SELEKTOR OBAT ********** */
#define ID_OBAT(o) (o).id
#define NAMA_OBAT(o) (o).nama
#define OBAT_LIST(l, i) (l).obats[i]
#define JUMLAH_OBAT(l) (l).jumlahobat

/* ********** KONSTRUKTOR ********** */
// Membuat obat kosong (default value)
void CreateObat(Obat *o);
// Membuat ListObat kosong
void InitializeListObat(ListObat *l);

/* ********** OPERASI ********** */
// Mengambil obat berdasarkan ID (jika tidak ditemukan, kembalikan obat dengan ID = -1)
Obat GetObat(ListObat l, int id);
// Menghapus obat berdasarkan ID, hasil hapus disimpan di buffer
void DelObat(ListObat *l, int id, Obat *buffer);
// Menambah obat ke ListObat (jika penuh, tidak melakukan apa-apa)
void InsObat(ListObat *l, Obat buffer);
// Menampilkan semua obat dalam ListObat
void tampilkan_obat(ListObat l);



/* ********** TYPE PENYAKIT ********** */
typedef struct {
    int id;
    char nama[MAX_NAMA];
    float suhu_min, suhu_max;
    int sys_min, sys_max;
    int dias_min, dias_max;
    int detak_min, detak_max;
    float saturasi_min, saturasi_max;
    float gula_min, gula_max;
    float berat_min, berat_max;
    int tinggi_min, tinggi_max;
    int kolesterol_min, kolesterol_max;
    int trombosit_min, trombosit_max;
} Penyakit;

typedef struct {
    Penyakit penyakits[MAX_PENYAKIT];
    int jumlahpenyakit;
} ListPenyakit;  // ListPenyakit rata kiri diurut menaik berdasarkan ID penyakit

/* ********** SELEKTOR PENYAKIT ********** */
#define ID_PENYAKIT(p) (p).id
#define NAMA_PENYAKIT(p) (p).nama
#define PENYAKIT_LIST(l, i) (l).penyakits[i]
#define JUMLAH_PENYAKIT(l) (l).jumlahpenyakit
#define SUHU_MIN(p) (p).suhu_min
#define SUHU_MAX(p) (p).suhu_max
#define SYS_MIN(p) (p).sys_min
#define SYS_MAX(p) (p).sys_max
#define DIAS_MIN(p) (p).dias_min
#define DIAS_MAX(p) (p).dias_max
#define DETAK_MIN(p) (p).detak_min
#define DETAK_MAX(p) (p).detak_max
#define SATURASI_MIN(p) (p).saturasi_min
#define SATURASI_MAX(p) (p).saturasi_max
#define GULA_MIN(p) (p).gula_min
#define GULA_MAX(p) (p).gula_max
#define BERAT_MIN(p) (p).berat_min
#define BERAT_MAX(p) (p).berat_max
#define TINGGI_MIN(p) (p).tinggi_min
#define TINGGI_MAX(p) (p).tinggi_max
#define KOLESTEROL_MIN(p) (p).kolesterol_min
#define KOLESTEROL_MAX(p) (p).kolesterol_max
#define TROMBOSIT_MIN(p) (p).trombosit_min
#define TROMBOSIT_MAX(p) (p).trombosit_max
#define PENYAKIT_LIST(l, i) (l).penyakits[i]
#define JUMLAH_PENYAKIT(l) (l).jumlahpenyakit

/* ********** KONSTRUKTOR ********** */
void CreatePenyakit(Penyakit *p);
void InitializeListPenyakit(ListPenyakit *l);

/* ********** OPERASI ********** */
Penyakit GetPenyakit(ListPenyakit l, int id);
void DelPenyakit(ListPenyakit *l, int id, Penyakit *buffer);
void InsPenyakit(ListPenyakit *l, Penyakit buffer);
void tampilkan_penyakit(ListPenyakit l);



/* ********** TYPE FORMULA ********** */
typedef struct {
    int obat_id;
    int penyakit_id;
    int urutan;
} Formula;

typedef struct {
    Formula formulas[MAX_FORMULA];
    int jumlahformula;
} ListFormula;  // List formula yang menghubungkan obat dan penyakit

/* ********** SELEKTOR FORMULA ********** */
#define OBAT_ID(f) (f).obat_id
#define PENYAKIT_ID(f) (f).penyakit_id
#define URUTAN(f) (f).urutan
#define FORMULA_LIST(l, i) (l).formulas[i]
#define JUMLAH_FORMULA(l) (l).jumlahformula

/* ********** KONSTRUKTOR ********** */
void CreateFormula(Formula *f);
void InitializeListFormula(ListFormula *l);

/* ********** OPERASI ********** */
Formula GetFormula(ListFormula l, int obat_id, int penyakit_id);
void DelFormula(ListFormula *l, int obat_id, int penyakit_id, Formula *buffer);
void InsFormula(ListFormula *l, Formula buffer);
void tampilkan_formula(ListFormula l);

#endif
