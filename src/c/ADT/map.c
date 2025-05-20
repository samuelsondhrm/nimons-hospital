#include "../header/map.h"

/* ------------- KONSTRUKTOR ------------- */
void CreateEmptyMap(Map *m) {
    m->count = 0;
}

/* ------------- PREDIKAT ------------- */
boolean IsMapEmpty(Map m) {
    return m.count == 0;
}

boolean IsMapFull(Map m) {
    return m.count == CAPACITY;
}

boolean IsKeyMember(Map m, KeyType k) {
    for (int i = 0; i < m.count; i++) {
        if (strcmp(m.elements[i].key, k) == 0) {
            return true;
        }
    }
    return false;
}

/* ------------- OPERASI DASAR ------------- */
void InsertMap(Map *m, KeyType k, ValueType v) {
    if (!IsMapFull(*m) && !IsKeyMember(*m, k)) {
        strcpy(m->elements[m->count].key, k);
        m->elements[m->count].value = v;
        m->count++;
    }
}

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

ValueType GetValue(Map m, KeyType k) {
    for (int i = 0; i < m.count; i++) {
        if (strcmp(m.elements[i].key, k) == 0) {
            return m.elements[i].value;
        }
    }
    return -1; // default, asumsi key pasti ada
}

void PrintMap(Map m) {
    printf("{\n");
    for (int i = 0; i < m.count; i++) {
        printf("{\"%s\", %d}", m.elements[i].key, m.elements[i].value);
        if (i != m.count - 1) printf(",");
        printf("\n");
    }
    printf("}\n");
}
