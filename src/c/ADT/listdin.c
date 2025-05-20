#include <stdio.h>
#include <stdlib.h>
#include "../header/listdin.h"

void CreateListDin(ListDin *l, int capacity) {
    CAPACITY(*l) = capacity;
    l->buffer = (ElType *)malloc(capacity * sizeof(ElType));
    l->nEff = 0;
}

void dealocateList(ListDin *l) {
    free(l->buffer);
    l->capacity = 0;
    l->nEff = 0;
}

int listLength(ListDin l) {
    return l.nEff;
}

IdxType getFirstIdx(ListDin l) {
    return 0;
}

IdxType getLastIdx(ListDin l) {
    return l.nEff - 1;
}

boolean isIdxValid(ListDin l, IdxType i) {
    return (i >= 0 && i < l.capacity);
}

boolean isIdxEff(ListDin l, IdxType i) {
    return (i >= 0 && i < l.nEff);
}

boolean isEmpty(ListDin l) {
    return (l.nEff == 0);
}

boolean isFull(ListDin l) {
    return (l.nEff == l.capacity);
}

void readList(ListDin *l) {
    int n;
    do {
        scanf("%d", &n);
    } while (n < 0 || n > l->capacity);

    l->nEff = n;
    for (int i = 0; i < n; i++) {
        scanf("%d", &l->buffer[i]);
    }
}

void printList(ListDin l) {
    printf("[");
    for (int i = 0; i < l.nEff; i++) {
        printf("%d", l.buffer[i]);
        if (i < l.nEff - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

ListDin plusMinusList(ListDin l1, ListDin l2, boolean plus) {
    ListDin result;
    CreateListDin(&result, l1.capacity);
    result.nEff = l1.nEff;
    for (int i = 0; i < l1.nEff; i++) {
        if (plus) {
            result.buffer[i] = l1.buffer[i] + l2.buffer[i];
        } else {
            result.buffer[i] = l1.buffer[i] - l2.buffer[i];
        }
    }
    return result;
}

boolean isListEqual(ListDin l1, ListDin l2) {
    if (l1.nEff != l2.nEff) return false;
    for (int i = 0; i < l1.nEff; i++) {
        if (l1.buffer[i] != l2.buffer[i]) return false;
    }
    return true;
}

IdxType indexOf(ListDin l, ElType val) {
    for (int i = 0; i < l.nEff; i++) {
        if (l.buffer[i] == val) return i;
    }
    return IDX_UNDEF;
}

void extremeValues(ListDin l, ElType *max, ElType *min) {
    *max = l.buffer[0];
    *min = l.buffer[0];
    for (int i = 1; i < l.nEff; i++) {
        if (l.buffer[i] > *max) *max = l.buffer[i];
        if (l.buffer[i] < *min) *min = l.buffer[i];
    }
}

void copyList(ListDin lIn, ListDin *lOut) {
    CreateListDin(lOut, lIn.capacity);
    lOut->nEff = lIn.nEff;
    for (int i = 0; i < lIn.nEff; i++) {
        lOut->buffer[i] = lIn.buffer[i];
    }
}

ElType sumList(ListDin l) {
    ElType sum = 0;
    for (int i = 0; i < l.nEff; i++) {
        sum += l.buffer[i];
    }
    return sum;
}

int countVal(ListDin l, ElType val) {
    int count = 0;
    for (int i = 0; i < l.nEff; i++) {
        if (l.buffer[i] == val) count++;
    }
    return count;
}

void sort(ListDin *l, boolean asc) {
    int len = NEFF(*l);
    int temp;
    for (int i = 0; i < len - 1; i++) {
        for (int j = i + 1; j < len; j++) {
            if ((asc && ELMT(*l, i) > ELMT(*l, j)) ||
                (!asc && ELMT(*l, i) < ELMT(*l, j))) {
                temp = ELMT(*l, i);
                ELMT(*l, i) = ELMT(*l, j);
                ELMT(*l, j) = temp;
            }
        }
    }
}

void insertLast(ListDin *l, ElType val) {
    if (NEFF(*l) < CAPACITY(*l)) {
        ELMT(*l, NEFF(*l)) = val;
        l->nEff++;
    }
}

void deleteLast(ListDin *l, ElType *val) {
    *val = l->buffer[l->nEff - 1];
    l->nEff--;
}

void expandList(ListDin *l, int num) {
    l->capacity += num;
    l->buffer = (ElType *)realloc(l->buffer, l->capacity * sizeof(ElType));
}

void shrinkList(ListDin *l, int num) {
    l->capacity -= num;
    l->buffer = (ElType *)realloc(l->buffer, l->capacity * sizeof(ElType));
}

void compressList(ListDin *l) {
    l->capacity = l->nEff;
    l->buffer = (ElType *)realloc(l->buffer, l->capacity * sizeof(ElType));
}
