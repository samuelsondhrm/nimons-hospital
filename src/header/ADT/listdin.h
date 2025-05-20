/* File: listdin.h */
/* Deklarasi ADT List Dinamis */

#ifndef LISTDIN_H
#define LISTDIN_H

#include "Boolean.h"

#define IDX_MIN 0
#define IDX_UNDEF -1

typedef int ElType;
typedef int IdxType;

typedef struct {
    ElType *buffer;
    int nEff;
    int capacity;
} ListDin;

/* ********** SELEKTOR ********** */
#define NEFF(l) (l).nEff
#define BUFFER(l) (l).buffer
#define ELMT(l, i) (l).buffer[i]
#define CAPACITY(l) (l).capacity

/* ********** KONSTRUKTOR ********** */
void CreateListDin(ListDin *l, int capacity);
void dealocateList(ListDin *l);

/* ********** SELEKTOR TAMBAHAN ********** */
int listLength(ListDin l);
IdxType getFirstIdx(ListDin l);
IdxType getLastIdx(ListDin l);
boolean isIdxValid(ListDin l, IdxType i);
boolean isIdxEff(ListDin l, IdxType i);

/* ********** TEST KOSONG/PENUH ********** */
boolean isEmpty(ListDin l);
boolean isFull(ListDin l);

/* ********** BACA/TULIS ********** */
void readList(ListDin *l);
void printList(ListDin l);

/* ********** ARITMATIKA ********** */
ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus);

/* ********** RELASIONAL ********** */
boolean isListEqual(ListDin l1, ListDin l2);

/* ********** SEARCHING ********** */
IdxType indexOf(ListDin l, ElType val);

/* ********** NILAI EKSTREM ********** */
void extremeValues(ListDin l, ElType *max, ElType *min);

/* ********** OPERASI LAIN ********** */
void copyList(ListDin lIn, ListDin *lOut);
ElType sumList(ListDin l);
int countVal(ListDin l, ElType val);

/* ********** SORTING ********** */
void sort(ListDin *l, boolean asc);

/* ********** MENAMBAH/MENGHAPUS ELEMEN ********** */
void insertLast(ListDin *l, ElType val);
void deleteLast(ListDin *l, ElType *val);

/* ********** RESIZE ********** */
void expandList(ListDin *l, int num);
void shrinkList(ListDin *l, int num);
void compressList(ListDin *l);

#endif
