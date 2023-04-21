/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include "participant_list.h"

void createEmptyListP(tListP *L){
    *L = NULLP;
}

bool isEmptyListP(tListP L){
    return L == NULLP;
}

tPosP firstP(tListP L){
    return L;
}

tPosP lastP(tListP L){
    tPosP q;
    q = L;
    while (q->next != NULLP)
        q = q->next;
    return q;
}

tPosP nextP(tPosP p, tListP L){
    return p->next;
}

tPosP previousP(tPosP p, tListP L){
    tPosP q;
    if (p == L) {
        return NULLP;
    } else {
        q = L;
        while ((q->next) != p){
            q = q->next;
        }
        return q;
    }
}

bool createNode(tPosP *p){
    *p = malloc(sizeof(struct Node));
    return *p != NULLP;
}

tPosP findPosition(tListP L, tItemP d){   //Funcion auxiliar para insertItem
    tPosP p;
    p = L;
    while ((p->next != NULLP) && (strcmp(p->next->data.participantName, d.participantName) < 0)){
        p = p->next;
    }
    return p;
}

tPosP findItemP(tParticipantName i, tListP L){
    tPosP q;
    if (isEmptyListP(L)){   //Lista vacía, no existe el item
        return NULLP;
    } else {
        for (q = L; (q != NULLP) && (strcmp(q->data.participantName, i) < 0); q = q->next);
        if ((q != NULLP) && (strcmp(q->data.participantName, i) == 0)){ //importante que primero compruebe si es nulo
            return q;
        } else {
            return NULLP;
        }
    }
}

tItemP getItemP(tPosP p, tListP L){
    return (p->data);
}

bool insertItemP(tItemP d, tListP * L){
    tPosP q, p;
    if (!createNode(&q)){        //Comprobamos que se pueda crear el nuevo item
        return false;
    }else{
        q -> data = d;
        q -> next = NULLP;
        if (*L == NULLP){        //Caso 1: insertar en lista vacía
            *L = q;
        } else if (strcmp(d.participantName, (*L)->data.participantName) < 0){   //Caso 2: insertar al principio
            q -> next = *L;
            *L = q;
        } else {                //Caso 3: insertar en cualquier posición
            p = findPosition(*L, d);
            q->next = p->next;
            p->next = q;
        }
        return true;
    }
}

void updateItemP(tItemP d, tPosP p, tListP *L){
    p->data = d;
}

void deleteAtPositionP(tPosP p, tListP *L){
    tPosP q;
    if (p == *L) {       //Caso 1: eliminar el primer elemento
        *L = (*L)->next;
    }
    else if (p->next == NULLP){     //Caso 2: eliminar el último elemento
        for (q = *L; q->next != p; q = q->next);
        q->next = NULLP;
    }
    else{       //Caso 3: eliminar cualquier posición
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

