#include "../../header/ADT/liststatik.h"

/* ********** KONSTRUKTOR ********** */
void CreateListStatik(ListStatik *l) {
    for (int i = 0; i < CAPACITY_LIST; i++) {
        ELMT_LIST(*l, i) = MARK;
    }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
int listLength(ListStatik l) {
    int res = 0;
    for (int i = 0; i < CAPACITY_LIST; i++) {
        if (ELMT_LIST(l, i) != MARK) {
            res += 1;
        }
    }
    return res;
}

/* *** Selektor INDEKS *** */
IdxType getFirstIdx(ListStatik l) {
    for (int i = 0; i < CAPACITY_LIST; i++) {
        if (ELMT_LIST(l, i) != MARK) {
            return i;
        }
    }
    return IDX_UNDEF;  // Kembalikan IDX_UNDEF jika tidak ditemukan
}

IdxType getLastIdx(ListStatik l) {
    IdxType first = getFirstIdx(l);
    for (int i = first; i < CAPACITY_LIST; i++) {
        if (ELMT_LIST(l, i) == MARK) {
            return i - 1;
        }
    }
    return IDX_UNDEF;  // Kembalikan IDX_UNDEF jika tidak ditemukan
}

/* ********** TEST INDEKS YANG VALID ********** */
boolean isIdxValid(ListStatik l, IdxType i) {
    return (i >= IDX_MIN && i < CAPACITY_LIST);
}

boolean isIdxEff(ListStatik l, IdxType i) {
    return (i >= getFirstIdx(l) && i <= getLastIdx(l));
}

/* ********** TEST KOSONG/PENUH ********** */
boolean isEmpty(ListStatik l) {
    for (int i = 0; i < CAPACITY_LIST; i++) {
        if (ELMT_LIST(l, i) != MARK) {
            return false;
        }
    }
    return true;
}

boolean isFull(ListStatik l) {
    for (int i = 0; i < CAPACITY_LIST; i++) {
        if (ELMT_LIST(l, i) == MARK) {
            return false;
        }
    }
    return true;
}

/* ********** BACA DAN TULIS ********** */
void readList(ListStatik *l) {
    int n;
    CreateListStatik(l);
    scanf("%d", &n);
    while (n < 0 || n > CAPACITY_LIST) {
        scanf("%d", &n);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &ELMT_LIST(*l, i));
    }
}

void printList(ListStatik l) {
    printf("[");
    for (int i = 0; i < listLength(l); i++) {
        printf("%d", ELMT_LIST(l, i));
        if (i < listLength(l) - 1) {
            printf(",");
        }
    }
    printf("]");
}

/* ********** OPERATOR ARITMATIKA ********** */
ListStatik plusMinusList(ListStatik l1, ListStatik l2, boolean plus) {
    ListStatik result;
    CreateListStatik(&result);
    int len = listLength(l1);
    for (int i = 0; i < len; i++) {
        if (plus) {
            ELMT_LIST(result, i) = ELMT_LIST(l1, i) + ELMT_LIST(l2, i);
        } else {
            ELMT_LIST(result, i) = ELMT_LIST(l1, i) - ELMT_LIST(l2, i);
        }
    }
    return result;
}

/* ********** OPERATOR RELASIONAL ********** */
boolean isListEqual(ListStatik l1, ListStatik l2) {
    if (listLength(l1) != listLength(l2)) {
        return false;
    }
    for (int i = 0; i < listLength(l1); i++) {
        if (ELMT_LIST(l1, i) != ELMT_LIST(l2, i)) {
            return false;
        }
    }
    return true;
}

/* ********** SEARCHING ********** */
int indexOf(ListStatik l, ElType val) {
    for (int i = 0; i < listLength(l); i++) {
        if (ELMT_LIST(l, i) == val) {
            return i;
        }
    }
    return IDX_UNDEF;
}

/* ********** NILAI EKSTREM ********** */
void extremeValues(ListStatik l, ElType *max, ElType *min) {
    *max = ELMT_LIST(l, 0);
    *min = ELMT_LIST(l, 0);
    for (int i = 1; i < listLength(l); i++) {
        if (ELMT_LIST(l, i) > *max) {
            *max = ELMT_LIST(l, i);
        }
        if (ELMT_LIST(l, i) < *min) {
            *min = ELMT_LIST(l, i);
        }
    }
}

/* ********** MENAMBAH ELEMEN ********** */
void insertFirst(ListStatik *l, ElType val) {
    for (int i = listLength(*l); i > 0; i--) {
        ELMT_LIST(*l, i) = ELMT_LIST(*l, i - 1);
    }
    ELMT_LIST(*l, 0) = val;
}

void insertAt(ListStatik *l, ElType val, IdxType idx) {
    for (int i = listLength(*l); i > idx; i--) {
        ELMT_LIST(*l, i) = ELMT_LIST(*l, i - 1);
    }
    ELMT_LIST(*l, idx) = val;
}

void insertLast(ListStatik *l, ElType val) {
    ELMT_LIST(*l, listLength(*l)) = val;
}

/* ********** MENGHAPUS ELEMEN ********** */
void deleteFirst(ListStatik *l, ElType *val) {
    *val = ELMT_LIST(*l, 0);
    for (int i = 0; i < listLength(*l) - 1; i++) {
        ELMT_LIST(*l, i) = ELMT_LIST(*l, i + 1);
    }
    ELMT_LIST(*l, listLength(*l) - 1) = MARK;
}

void deleteAt(ListStatik *l, ElType *val, IdxType idx) {
    *val = ELMT_LIST(*l, idx);
    for (int i = idx; i < listLength(*l) - 1; i++) {
        ELMT_LIST(*l, i) = ELMT_LIST(*l, i + 1);
    }
    ELMT_LIST(*l, listLength(*l) - 1) = MARK;
}

void deleteLast(ListStatik *l, ElType *val) {
    *val = ELMT_LIST(*l, listLength(*l) - 1);
    ELMT_LIST(*l, listLength(*l) - 1) = MARK;
}

/* ********** SORTING ********** */
void sortList(ListStatik *l, boolean asc) {
    int len = listLength(*l);
    int temp;
    if (asc) {
        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                if (ELMT_LIST(*l, i) > ELMT_LIST(*l, j)) {
                    temp = ELMT_LIST(*l, i);
                    ELMT_LIST(*l, i) = ELMT_LIST(*l, j);
                    ELMT_LIST(*l, j) = temp;
                }
            }
        }
    } else {
        for (int i = 0; i < len - 1; i++) {
            for (int j = i + 1; j < len; j++) {
                if (ELMT_LIST(*l, i) < ELMT_LIST(*l, j)) {
                    temp = ELMT_LIST(*l, i);
                    ELMT_LIST(*l, i) = ELMT_LIST(*l, j);
                    ELMT_LIST(*l, j) = temp;
                }
            }
        }
    }
}
