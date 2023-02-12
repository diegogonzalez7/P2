/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include "static_list.h"

void createEmptyList(tList *L){
    L -> lastPos = LNULL;
}

bool isEmptyList(tList L){
    return L.lastPos == LNULL;
}

tPosL first(tList L){
    return 0;
}

tPosL last(tList L){
    return L.lastPos;
}

tPosL next(tPosL p, tList L){
    if(p == L.lastPos){
        return LNULL;   
    }else{
        return ++p; //es el equivalente a poner (p+1);
    }
}

tPosL previous(tPosL p, tList L){
    return --p;
}

bool insertItem(tItemL d, tPosL p, tList *L){
    tPosL i;

    if(L->lastPos == MAX - 1){
        return false;
    }else{
        L->lastPos++;
        if(p == LNULL){
            tPosL q = L->lastPos;
            L->data[q] = d;
        }else{
            for(i = L->lastPos; i >= p+1; i--){
                L->data[i] = L->data[i - 1];
            }
            L->data[p] = d;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L){
    tPosL i;
    L -> lastPos --;
    for(i = p; i <= L->lastPos; i++){
        L->data[i] = L->data[i + 1];
    }
}

tItemL getItem(tPosL p, tList L){
    return L.data[p];
}

void updateItem(tItemL d, tPosL p, tList *L){
    L -> data[p] = d;
}

tPosL findItem(tParticipantName d, tList L){
    if(isEmptyList(L)) {return LNULL;}
    else{
        tPosL i;
        for(i = 0; (i < L.lastPos) && (strcmp(L.data[i].participantName, d) != 0); i++);
        if(strcmp(L.data[i].participantName, d) != 0){
            return LNULL;
        }else{
            return i;
        }
    }
}
