/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include "dynamic_list.h"

void createEmptyList(tList *L){             //Crea una lista vacía haciendo que L apunte a un NULL.
    *L = LNULL;
}

bool isEmptyList (tList L){                 //Comprueba si la lista está vacía viendo si L apunta a un NULL.
    return L == LNULL;
}

tPosL first (tList L){                      //Devuelve la primera posición de la lista viendo a qué apunta L.
    return L;
}

tPosL last(tList L){                        //Recorre la lista hasta llegar a un LNULL (última posición de la lista).
    tPosL q;
    q = L;
    while(q->next != LNULL)
        q = q->next;
    return q;
}
tPosL next(tPosL p, tList L){               //Devuelve el siguiente elemento al introducido usando el campo next.
    return p->next;
}
tPosL previous(tPosL p, tList L){           //Devuelve la posición anterior a la introducida valorando dos casos:
    tPosL q;
    if(p==L) return LNULL;                  //Si el elemento introducido es el primero de la lista entonces devolverá un NULL.
    else{                                   //En caso contrario devolverá la posición correspondiente, incluso si es la última porque también devolverá un NULL.
        q=L;
        while ((q->next)!=p){
            q = q->next;
        }
        return q;
    }
}

bool createNode(tPosL *p) {                   //Crea un Nodo reservando la memoria correspondiente a un struct Nodo
    *p = malloc(sizeof(struct Node));
    return *p != LNULL;                      //verdadero si *p!=LNULL
}

bool insertItem(tItemL d, tPosL p, tList * L){      //Inserta un elemento en la lista valorando 4 casos:
    tPosL q;
    if (!createNode(&q))
        return false;
    else {
        q->data=d;
        q->next=LNULL;
        if (isEmptyList(*L))
            *L=q;
        else if (p==*L){
            q->next=p;
            *L=q;
        }
        else if (p==LNULL){
            last(*L)->next=q;
            q->next=LNULL;
        }
        else {
            q->next=p->next;
            p->next=q;
            q->data=p->data;
            p->data=d;
        }
        return true;
    }
}
void deleteAtPosition(tPosL p, tList * L){      //Elimina un elemento de la lista valorando 3 casos:
    tPosL q;

    if (p==*L) *L = (*L)->next;    //Caso 1: elimina el elemento situado en la primera posición de L.
    else if (p->next==LNULL) {          //Caso 2: elimina el elemento situado en la última posición de la lista.
        previous(p, *L)-> next = LNULL;
    }
    else {          //Caso 3: elimina el elemento de una posición intermedia de la lista (ni el último ni el primero).
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p=q;
    }
    free(p);       //Libera la variable apuntada p para que no quede memoria inaccesible.
}
tItemL getItem(tPosL p, tList L){       //Devuelve el elemento correspondiente a la posición introducida.
    return(p->data);
}
void updateItem(tItemL d, tPosL p, tList * L){      //Modifica el contenido de un elemento de la lista
    p->data = d;
}
tPosL findItem(tProductId i, tList L) {              //Encuentra el primer elemento con cierto contenido en la lista.
    tPosL q;
    if (isEmptyList(L))
        q = LNULL;
    else {
        for (q = L;(q != LNULL) && (strcmp(q->data.productId,i) != 0);q = q->next);
    }
    return q;
}