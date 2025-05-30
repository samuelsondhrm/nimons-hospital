#include "../../header/ADT/queue.h"

/* *** Kreator *** */
void CreateQueue(Queue *q){
    q->idxHead = IDX_UNDEF;
    q->idxTail = IDX_UNDEF;
}


/* ********* Prototype ********* */
boolean isEmptyQueue(Queue q){
    if(IDX_HEAD(q) == IDX_UNDEF && IDX_TAIL(q) == IDX_UNDEF){
        return true;
    }
    return false;
}

boolean isFullQueue(Queue q){
    if (!(isEmptyQueue(q))){
        int idxtail2 = (IDX_TAIL(q)+1) % CAPACITY_QUEUE;
        if(IDX_HEAD(q) == idxtail2){
            return true;
        }
    }
    return false;
}

int lengthQueue(Queue q){
    if (isEmptyQueue(q)) return 0;
    if (IDX_TAIL(q) >= IDX_HEAD(q)) {
        return IDX_TAIL(q) - IDX_HEAD(q) + 1;
    } else {
        return (CAPACITY_QUEUE - IDX_HEAD(q)) + (IDX_TAIL(q) + 1);
    }
}

/* *** Primitif Add/Delete *** */
void enqueue(Queue *q, ElType val){
    if(isEmptyQueue(*q)){
        q->buffer[0] = val;
        q->idxHead = 0;
        q->idxTail = 0;
    }
    else if(!isFullQueue(*q)){
        q->idxTail = (IDX_TAIL(*q) + 1) % CAPACITY_QUEUE;
        q->buffer[IDX_TAIL(*q)] = val;
    }
}

void dequeue(Queue *q, ElType *val){
    if(!isEmptyQueue(*q)){
        *val = q->buffer[IDX_HEAD(*q)];
        if (IDX_HEAD(*q) == IDX_TAIL(*q)) {
            q->idxHead = IDX_UNDEF;
            q->idxTail = IDX_UNDEF;
        } else {
            q->idxHead = (IDX_HEAD(*q)+1) % CAPACITY_QUEUE;
        }
    }
}

/* *** Display Queue *** */
void displayQueue(Queue q){
    if(isEmptyQueue(q)) printf("[]\n");
    else{
        printf("[");
        for(int i = 0; i < lengthQueue(q); i++){
            ElType elmt = q.buffer[(q.idxHead + i) % CAPACITY_QUEUE];
            if(i == lengthQueue(q) - 1) printf("%d]\n", elmt);
            else printf("%d,", elmt);
        }
    }
}
