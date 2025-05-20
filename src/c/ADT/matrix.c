#include "../header/matrix.h"

// Membuat matrix dengan ukuran nRows x nCols
void createMatrix(int nRows, int nCols, Matrix *m) {
    ROW_EFF(*m) = nRows;
    COL_EFF(*m) = nCols;
}

// Memastikan indeks berada dalam kapasitas maksimum
boolean isIdxValidMatrix(int i, int j) {
    return (i >= IDX_MIN && i < ROW_CAP && j >= IDX_MIN && j < COL_CAP);
}

// Memastikan indeks berada dalam ukuran efektif
boolean isMatrixIdxEff(Matrix m, int i, int j) {
    return (i >= 0 && i < ROW_EFF(m) && j >= 0 && j < COL_EFF(m));
}

// Membaca matrix dari input
void readMatrix(Matrix *m, int nRows, int nCols) {
    createMatrix(nRows, nCols, m);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            scanf("%d", &ELMT(*m, i, j));
        }
    }
}

// Menampilkan matrix ke layar
void displayMatrix(Matrix m) {
    for (int i = 0; i < ROW_EFF(m); i++) {
        for (int j = 0; j < COL_EFF(m); j++) {
            printf("%d", ELMT(m, i, j));
            if (j < COL_EFF(m) - 1) printf(" ");
        }
        printf("\n");
    }
}

// Penjumlahan dua matrix
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

// Pengurangan dua matrix
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

// Perkalian dua matrix
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

// Mengalikan matrix dengan konstanta
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

// Mengecek apakah matrix berbentuk persegi
boolean isSquare(Matrix m) {
    return (ROW_EFF(m) == COL_EFF(m));
}

// Transpos dari matrix
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

// Determinan untuk matrix 2x2
ElType determinant2x2(Matrix m) {
    if (ROW_EFF(m) == 2 && COL_EFF(m) == 2) {
        return ELMT(m, 0, 0) * ELMT(m, 1, 1) - ELMT(m, 0, 1) * ELMT(m, 1, 0);
    } else {
        return 0; // Bukan matrix 2x2
    }
}
