#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include "Boolean.h"

#define ROW_CAP 100
#define COL_CAP 100
#define IDX_MIN 0
#define IDX_UNDEF -1

typedef int ElType;
typedef struct {
    ElType mem[ROW_CAP][COL_CAP];
    int rowEff;  // Banyak baris efektif
    int colEff;  // Banyak kolom efektif
} Matrix;

/* *** SELEKTOR *** */
#define ROW_EFF(m) (m).rowEff
#define COL_EFF(m) (m).colEff
#define ELMT(m, i, j) (m).mem[(i)][(j)]

/* Konstruktor */
void createMatrix(int nRows, int nCols, Matrix *m) {
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}

/* Validasi indeks */
boolean isIdxValidMatrix(int i, int j) {
    return (i >= IDX_MIN && i < ROW_CAP && j >= IDX_MIN && j < COL_CAP);
}

boolean isMatrixIdxEff(Matrix m, int i, int j) {
    return (i >= 0 && i < ROW_EFF(m) && j >= 0 && j < COL_EFF(m));
}

/* Baca dan tulis matrix */
void readMatrix(Matrix *m, int nRows, int nCols) {
    createMatrix(nRows, nCols, m);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            scanf("%d", &ELMT(*m, i, j));
        }
    }
}

void displayMatrix(Matrix m) {
    for (int i = 0; i < ROW_EFF(m); i++) {
        for (int j = 0; j < COL_EFF(m); j++) {
            printf("%d", ELMT(m, i, j));
            if (j < COL_EFF(m) - 1) printf(" ");
        }
        printf("\n");
    }
}

/* Operasi Aritmatika */
Matrix addMatrix(Matrix m1, Matrix m2) {
    Matrix mRes;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &mRes);
    for (int i = 0; i < ROW_EFF(m1); i++) {
        for (int j = 0; j < COL_EFF(m1); j++) {
            ELMT(mRes, i, j) = ELMT(m1, i, j) + ELMT(m2, i, j);
        }
    }
    return mRes;
}

Matrix subtractMatrix(Matrix m1, Matrix m2) {
    Matrix mRes;
    createMatrix(ROW_EFF(m1), COL_EFF(m1), &mRes);
    for (int i = 0; i < ROW_EFF(m1); i++) {
        for (int j = 0; j < COL_EFF(m1); j++) {
            ELMT(mRes, i, j) = ELMT(m1, i, j) - ELMT(m2, i, j);
        }
    }
    return mRes;
}

Matrix multiplyMatrix(Matrix m1, Matrix m2) {
    Matrix mRes;
    createMatrix(ROW_EFF(m1), COL_EFF(m2), &mRes);
    for (int i = 0; i < ROW_EFF(m1); i++) {
        for (int j = 0; j < COL_EFF(m2); j++) {
            ELMT(mRes, i, j) = 0;
            for (int k = 0; k < COL_EFF(m1); k++) {
                ELMT(mRes, i, j) += ELMT(m1, i, k) * ELMT(m2, k, j);
            }
        }
    }
    return mRes;
}

Matrix multiplyByConst(Matrix m, ElType x) {
    Matrix mRes;
    createMatrix(ROW_EFF(m), COL_EFF(m), &mRes);
    for (int i = 0; i < ROW_EFF(m); i++) {
        for (int j = 0; j < COL_EFF(m); j++) {
            ELMT(mRes, i, j) = ELMT(m, i, j) * x;
        }
    }
    return mRes;
}

/* Operasi lainnya */
boolean isSquare(Matrix m) {
    return (ROW_EFF(m) == COL_EFF(m));
}

Matrix transpose(Matrix m) {
    Matrix mT;
    createMatrix(COL_EFF(m), ROW_EFF(m), &mT);
    for (int i = 0; i < ROW_EFF(m); i++) {
        for (int j = 0; j < COL_EFF(m); j++) {
            ELMT(mT, j, i) = ELMT(m, i, j);
        }
    }
    return mT;
}

ElType determinant2x2(Matrix m) {
    if (ROW_EFF(m) == 2 && COL_EFF(m) == 2) {
        return ELMT(m, 0, 0) * ELMT(m, 1, 1) - ELMT(m, 0, 1) * ELMT(m, 1, 0);
    } else {
        return 0; // Bukan matriks 2x2
    }
}

#endif