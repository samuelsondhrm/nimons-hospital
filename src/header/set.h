#include <stdio.h>
#ifndef SET_H
#define SET_H
#include <stdbool.h>
#define MAX_SET_SIZE 100

typedef int ElType;
typedef struct {
    ElType elements[MAX_SET_SIZE]; // Array untuk menyimpan elemen-elemen set
    int count;                     // Jumlah elemen dalam set
} Set;

/* *** SELEKTOR MAKRO *** */
#define SELMT(s, i) s.elements[i]; 
#define COUNT(s) s.count;          

/* *** KONSTRUKTOR *** */
/* I.S. Sembarang */
/* F.S. Terbentuk set kosong */
void CreateEmptySet(Set *s) {
    s->count = 0;
}

/* *** PREDIKAT *** */
/* Mengirim true jika val adalah member dari set s */
bool IsMember(Set s, ElType val) {
    for (int i = 0; i < s.count; i++) {
        if (s.elements[i] == val) return true;
    }
    return false;
}

/* Mengirim true jika set penuh (jumlah elemen mencapai MAX_SET_SIZE) */
bool IsSetFull(Set s) {
    return s.count == MAX_SET_SIZE;
}

/* Mengirim true jika set kosong */
bool IsSetEmpty(Set s) {
    return s.count == 0;
}

/* *** OPERASI DASAR PADA SET *** */
/* Menambahkan val ke dalam set s jika belum ada dan belum penuh */
/* I.S. Set mungkin kosong, belum penuh */
/* F.S. val masuk ke dalam set jika belum ada */
void InsertSet(Set *s, ElType val) {
    if (!IsMember(*s, val) && !IsSetFull(*s)) {
        s->elements[s->count++] = val;
    }
}

/* Menghapus elemen val dari set s jika ada */
/* I.S. Set terdefinisi */
/* F.S. val tidak ada dalam set (jika ada, dihapus) */
void DeleteSet(Set *s, ElType val) {
    for (int i = 0; i < s->count; i++) {
        if (s->elements[i] == val) {
            for (int j = i; j < s->count - 1; j++) {
                s->elements[j] = s->elements[j + 1];
            }
            s->count--;
            break;
        }
    }
}

/* *** OPERASI LAIN *** */
/* Mengembalikan union dari dua set */
/* I.S. s1 dan s2 terdefinisi */
/* F.S. Menghasilkan set yang berisi semua elemen unik dari s1 dan s2 */
/* Contoh: s1 = {1,2,3} dan s2 = {2,3,4}. Maka Union = {1, 2, 3, 4}*/
Set SetUnion(Set s1, Set s2) {
    Set result;
    CreateEmptySet(&result);
    for (int i = 0; i < s1.count; i++) {
        InsertSet(&result, s1.elements[i]);
    }
    for (int i = 0; i < s2.count; i++) {
        InsertSet(&result, s2.elements[i]);
    }
    return result;
}

/* Mengembalikan irisan (intersection) dari dua set */
/* I.S. s1 dan s2 terdefinisi */
/* F.S. Menghasilkan set yang berisi elemen yang terdapat di kedua set */
/* Contoh: s1 = {1,2,3} dan s2 = {2,3,4}. Maka Intersection = {2, 3}*/
Set SetIntersection(Set s1, Set s2) {
    Set result;
    CreateEmptySet(&result);
    for (int i = 0; i < s1.count; i++) {
        if (IsMember(s2, s1.elements[i])) {
            InsertSet(&result, s1.elements[i]);
        }
    }
    return result;
}

/* Mengembalikan selisih dari dua set (elemen di s1 yang tidak ada di s2) */
/* I.S. s1 dan s2 terdefinisi */
/* F.S. Menghasilkan set dengan elemen di s1 yang bukan anggota s2 */
/* Contoh: s1 = {1,2,3} dan s2 = {2,3,4}. Maka Difference = {1}*/
Set SetDifference(Set s1, Set s2) {
    Set result;
    CreateEmptySet(&result);
    for (int i = 0; i < s1.count; i++) {
        if (!IsMember(s2, s1.elements[i])) {
            InsertSet(&result, s1.elements[i]);
        }
    }
    return result;
}

/* Menampilkan isi set s dengan format {a, b, c} */
/* I.S. Set s terdefinisi */
/* F.S. Isi set tercetak di layar */
/* Hasil output: {1, 2, ..., 3} (Tidak ada apa apa setelah }, baik newline atau spasi)*/
void PrintSet(Set s) {
    printf("{");
    for (int i = 0; i < s.count; i++) {
        printf("%d", s.elements[i]);
        if (i != s.count - 1) printf(", ");
    }
    printf("}");
}

#endif
