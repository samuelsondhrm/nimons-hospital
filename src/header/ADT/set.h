/* File: set.h */
/* Deklarasi ADT set yang berupa array satu dimensi berisikan elemen yang unik */

#ifndef SET_H
#define SET_H

#include "../Boolean.h"
#include <stdio.h>

#define CAPACITY_SET 100 // Maksimal jumlah elemen dalam set

/* *** TIPE DATA SET *** */
typedef int ElType;
typedef struct {
    ElType elements[CAPACITY_SET]; // Array untuk menyimpan elemen-elemen set
    int count;                     // Jumlah elemen dalam set
} Set;

/* *** SELEKTOR MAKRO *** */
#define SELMT(s, i) s.elements[i]
#define COUNT(s) s.count

/* *** KONSTRUKTOR *** */
// Fungsi untuk membuat set kosong. 
void CreateEmptySet(Set *s);

/* *** PREDIKAT *** */
// Mengembalikan true jika val ada dalam set s, false jika tidak.
boolean IsMember(Set s, ElType val);

// Mengembalikan true jika jumlah elemen dalam set mencapai CAPACITY_SET.
boolean IsSetFull(Set s);

// Mengembalikan true jika set tidak memiliki elemen (count == 0).
boolean IsSetEmpty(Set s);

/* *** OPERASI DASAR PADA SET *** */
// Menambahkan val ke dalam set jika elemen tersebut belum ada dan set belum penuh.
void InsertSet(Set *s, ElType val);

// Menghapus elemen dengan nilai val pertama dari set jika ada.
void DeleteSet(Set *s, ElType val);

/* *** OPERASI LAIN *** */
/* 
 * Fungsi untuk mengembalikan union dari dua set.
 * Union menghasilkan set baru yang berisi semua elemen unik dari kedua set.
 * Contoh: {1,2,3} dan {2,3,4} menghasilkan {1,2,3,4}.
 */
Set SetUnion(Set s1, Set s2);

/* 
 * Fungsi untuk mengembalikan irisan (intersection) dari dua set.
 * Intersection menghasilkan set baru yang berisi elemen yang ada di kedua set.
 * Contoh: {1,2,3} dan {2,3,4} menghasilkan {2,3}.
 */
Set SetIntersection(Set s1, Set s2);

/* 
 * Fungsi untuk mengembalikan selisih (difference) antara dua set.
 * Menghasilkan set baru yang berisi elemen di set s1 yang tidak ada di set s2.
 * Contoh: {1,2,3} dan {2,3,4} menghasilkan {1}.
 */
Set SetDifference(Set s1, Set s2);

/* 
 * Fungsi untuk menampilkan isi set ke layar.
 * Menampilkan set dalam format {a, b, c, ...}, tanpa spasi atau newline setelah '}'.
 */
void PrintSet(Set s);

#endif
