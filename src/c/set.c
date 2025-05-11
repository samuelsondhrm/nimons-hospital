#include "../header/set.h"

/* *** KONSTRUKTOR *** */
void CreateEmptySet(Set *s) {
    s->count = 0;
}

/* *** PREDIKAT *** */
boolean IsMember(Set s, ElType val) {
    for (int i = 0; i < s.count; i++) {
        if (s.elements[i] == val) return true;
    }
    return false;
}

boolean IsSetFull(Set s) {
    return s.count == MAX_SET_SIZE;
}

boolean IsSetEmpty(Set s) {
    return s.count == 0;
}

/* *** OPERASI DASAR PADA SET *** */
void InsertSet(Set *s, ElType val) {
    if (!IsMember(*s, val) && !IsSetFull(*s)) {
        s->elements[s->count++] = val;
    }
}

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

void PrintSet(Set s) {
    printf("{");
    for (int i = 0; i < s.count; i++) {
        printf("%d", s.elements[i]);
        if (i != s.count - 1) printf(", ");
    }
    printf("}");
}
