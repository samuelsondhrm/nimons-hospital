/* File: liststatik.h */
/* Deklarasi ADT List statik dengan MARK*/

#ifndef LISTSTATIK_H
#define LISTSTATIK_H

#include "../Boolean.h"
#include <stdio.h>

/* Kamus Umum */
#define CAPACITY_LIST 100
#define IDX_MIN 0
#define IDX_UNDEF -1
#define MARK -9999

/* Definisi elemen dan koleksi objek */
typedef int ElType;  /* type elemen List */
typedef int IdxType;
typedef struct {
   ElType contents[CAPACITY_LIST]; /* memori tempat penyimpan elemen (container) */
} ListStatik;

/* ********** SELEKTOR ********** */
#define ELMT_LIST(l, i) (l).contents[(i)]


/* ********** KONSTRUKTOR ********** */
void CreateListStatik(ListStatik *l);
/* Konstruktor: membuat List kosong */

/* ********** SELEKTOR (TAMBAHAN) ********** */
int listLength(ListStatik l);
/* Mengirimkan banyaknya elemen efektif List l */

/* Indeks yang digunakan [0..CAPACITY_LIST-1] */
IdxType getFirstIdx(ListStatik l);
/* Mengirimkan indeks elemen pertama */

IdxType getLastIdx(ListStatik l);
/* Mengirimkan indeks elemen terakhir */

/* Test Indeks yang valid */
boolean isIdxValid(ListStatik l, IdxType i);
/* Mengirimkan true jika i adalah indeks yang valid utk kapasitas List l */

boolean isIdxEff(ListStatik l, IdxType i);
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk List l */

/* Test kosong/penuh */
boolean isEmpty(ListStatik l);
/* Mengirimkan true jika List l kosong */

boolean isFull(ListStatik l);
/* Mengirimkan true jika List l penuh */

/* Baca dan tulis dengan input/output device */
void readList(ListStatik *l);
/* Mendefinisikan isi List dari pembacaan */

void printList(ListStatik l);
/* Menuliskan isi List */

/* Operator Aritmatika */
ListStatik plusMinusList(ListStatik l1, ListStatik l2, boolean plus);
/* Menjumlahkan atau mengurangkan dua list */

/* Operator Relasional */
boolean isListEqual(ListStatik l1, ListStatik l2);
/* Mengirimkan true jika l1 sama dengan l2 */

/* Searching */
int indexOf(ListStatik l, ElType val);
/* Mencari indeks dari elemen val */

/* Nilai Ekstrem */
void extremeValues(ListStatik l, ElType *max, ElType *min);
/* Mencari nilai terbesar dan terkecil dalam List */

/* Menambah elemen */
void insertFirst(ListStatik *l, ElType val);
/* Menambahkan elemen pertama */

void insertAt(ListStatik *l, ElType val, IdxType idx);
/* Menambahkan elemen pada indeks tertentu */

void insertLast(ListStatik *l, ElType val);
/* Menambahkan elemen terakhir */

/* Menghapus elemen */
void deleteFirst(ListStatik *l, ElType *val);
/* Menghapus elemen pertama */

void deleteAt(ListStatik *l, ElType *val, IdxType idx);
/* Menghapus elemen pada indeks tertentu */

void deleteLast(ListStatik *l, ElType *val);
/* Menghapus elemen terakhir */

/* Sorting */
void sortList(ListStatik *l, boolean asc);
/* Mengurutkan list */

#endif /* LISTSTATIK_H */
