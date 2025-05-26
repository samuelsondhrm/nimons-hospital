#include "../../header/ADT/stack.h"

/* *** Konstruktor/Kreator *** */
void CreateEmpty(Stack *S){
    S->TOP = Nil;
}

/* ************   Predikat   ************ */
boolean IsEmpty(Stack S){
    if(Top(S) == Nil) return true;
    else return false;
}

boolean IsFull(Stack S){
    if(Top(S) == CAPACITY_STCK-1) return true;
    else return false;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push(Stack * S, infotype X){
    S->T[S->TOP+1] = X;
    S->TOP ++;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop(Stack * S, infotype* X){
    *X = S->T[S->TOP];
    S->TOP --;
}
