/* File: listdin.h */
/* Deklarasi ADT List Dinamis */

#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include "../Boolean.h"

#define ROW_CAP 100
#define COL_CAP 100
#define IDX_MIN 0
#define IDX_UNDEF -1

typedef int ElType;

// Definisi tipe Matrix
typedef struct {
    ElType mem[ROW_CAP][COL_CAP];
    int rowEff;  // Banyak baris efektif
    int colEff;  // Banyak kolom efektif
} Matrix;

/* *** SELEKTOR *** */
#define ROW_EFF(m) (m).rowEff
#define COL_EFF(m) (m).colEff
#define ELMT_MTRX(m, i, j) (m).mem[(i)][(j)]

/* *** FUNGSI & PROSEDUR *** */
// Konstruktor
void createMatrix(int nRows, int nCols, Matrix *m);

// Validasi indeks
boolean isIdxValidMatrix(int i, int j);
boolean isMatrixIdxEff(Matrix m, int i, int j);

// Baca dan tulis matrix
void readMatrix(Matrix *m, int nRows, int nCols);
void displayMatrix(Matrix m);

// Operasi aritmatika matrix
Matrix addMatrix(Matrix m1, Matrix m2);
Matrix subtractMatrix(Matrix m1, Matrix m2);
Matrix multiplyMatrix(Matrix m1, Matrix m2);
Matrix multiplyByConst(Matrix m, ElType x);

// Operasi lain
boolean isSquare(Matrix m);
Matrix transpose(Matrix m);
ElType determinant2x2(Matrix m);

#endif
