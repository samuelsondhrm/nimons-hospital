/* File: map.h */
/* Deklarasi ADT Map = [[key,val],[key,val],...] */

#ifndef MAP_H
#define MAP_H

#include "../Boolean.h"
#include <stdio.h>
#include <string.h> // If KeyType or ValueType are strings, this will be necessary for string operations.

/* ------------- TIPE DATA MAP ------------- */
typedef char KeyType[50];
typedef int ValueType;
typedef struct {
    KeyType key;     // key untuk map
    ValueType value; // value terkait dengan key
} MapElType;

#define CAPACITY 100 
typedef struct {
    MapElType elements[CAPACITY]; // Array untuk menyimpan elemen map
    int count;                    // Jumlah elemen dalam map
} Map;

/* ------------- KONSTRUKTOR ------------- */
// Fungsi ini untuk membuat map kosong (mengatur count ke 0). */
void CreateEmptyMap(Map *m);

/* ------------- PREDIKAT ------------- */
// Fungsi ini mengembalikan true jika map kosong (count == 0), false jika tidak. 
boolean IsMapEmpty(Map m);

// Fungsi ini mengembalikan true jika map penuh (count == CAPACITY), false jika tidak.
boolean IsMapFull(Map m);

// Fungsi mencari key dalam array elemen map, jika ditemukan, mengembalikan true.
boolean IsKeyMember(Map m, KeyType k);

/* ------------- OPERASI DASAR ------------- */
// Fungsi untuk menambahkan pasangan key dan value ke dalam map.
void InsertMap(Map *m, KeyType k, ValueType v);

// Fungsi akan mencari elemen dengan key yang sesuai, lalu menggeser elemen setelahnya untuk menghapusnya.
void DeleteMap(Map *m, KeyType k);

// Fungsi untuk mendapatkan value dari suatu key, diasumsikan bahwa key yang dicari pasti ada dalam map.
ValueType GetValue(Map m, KeyType k);

/* Menampilkan seluruh isi map */
void PrintMap(Map m) {
    printf("{\n");
    for (int i = 0; i < m.count; i++) {
        printf("{""%s"", %d}", m.elements[i].key, m.elements[i].value);
        if(i != m.count - 1) printf(",");
        printf("\n");
    }
    printf("}");
}

#endif
