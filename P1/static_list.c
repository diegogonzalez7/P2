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

}

void deleteAtPosition(tPosL p, tList *L){

}

tItemL getItem(tPosL p, tList L){
    return L.data[p];
}

void updateItem(tItemL d, tPosL p, tList *L){
    L -> data[p] = d;
}

tPosL findItem(tParticipantName d, tList L){

}
