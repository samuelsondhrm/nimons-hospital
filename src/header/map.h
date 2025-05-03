#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h> // Jika KeyType atau ValueType berupa string (Masih kurang tahu implementasinya gimana, komunikasikan aja)

/* ------------- TIPE DATA MAP ------------- */
typedef char KeyType[50];     
typedef int ValueType;        
typedef struct {
    KeyType key;
    ValueType value;
} MapElType;

#define CAPACITY 100
typedef struct {
    MapElType elements[CAPACITY];
    int count;
} Map;

/* ------------- KONSTRUKTOR ------------- */
/* Membuat map kosong */
void CreateEmptyMap(Map *m) {
    m->count = 0;
}

/* ------------- PREDIKAT ------------- */
/* Mengembalikan true jika m kosong */
bool IsMapEmpty(Map m) {
    return m.count == 0;
}
/* Mengembalikan true jika m full */
bool IsMapFull(Map m) {
    return m.count == CAPACITY;
}

/* Mengembalikan true jika k ada sebagai key di Map */
bool IsKeyMember(Map m, KeyType k) {
    for (int i = 0; i < m.count; i++) {
        if (strcmp(m.elements[i].key, k) == 0) {
            return true;
        }
    }
    return false;
}

/* ------------- OPERASI DASAR ------------- */
/* Menambahkan key dan value ke Map, jika key belum ada */
void InsertMap(Map *m, KeyType k, ValueType v) {
    if (!IsMapFull(*m) && !IsKeyMember(*m, k)) {
        strcpy(m->elements[m->count].key, k);
        m->elements[m->count].value = v;
        m->count++;
    }
}

/* Menghapus elemen dengan key k (jika ada) */
void DeleteMap(Map *m, KeyType k) {
    for (int i = 0; i < m->count; i++) {
        if (strcmp(m->elements[i].key, k) == 0) {
            for (int j = i; j < m->count - 1; j++) {
                m->elements[j] = m->elements[j + 1];
            }
            m->count--;
            break;
        }
    }
}

/* Mengambil value dari key (asumsikan key pasti ada) */
ValueType GetValue(Map m, KeyType k) {
    for (int i = 0; i < m.count; i++) {
        if (strcmp(m.elements[i].key, k) == 0) {
            return m.elements[i].value;
        }
    }
    return -1; // default, asumsi key pasti ada
}

/* Menampilkan seluruh isi map */
void PrintMap(Map m) {
    printf("{\n")
    for (int i = 0; i < m.count; i++) {
        printf("{""%s"", %d}", m.elements[i].key, m.elements[i].value);
        if(i != m.count - 1) printf(",");
        printf("\n");
    }
    printf("}")
}

/*Format output:
{
    {"Sarah", 50},
    {"Joe", 20},
    {"Kevin", 10}
}  
    (Tidak ada newline atau spasi setelah)                     */
#endif
