/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#include "jury_list.h"
#include "participant_list.h"

void createEmptyListJ(tListJ *L){
    L -> lastPos = NULLJ;
}

bool isEmptyListJ(tListJ L){
    return L.lastPos == NULLJ;
}

tPosJ firstJ(tListJ L){
    return 0;
}

tPosJ lastJ(tListJ L){
    return L.lastPos;
}

tPosJ nextJ(tPosJ p, tListJ L){
    if(p == L.lastPos){
        return NULLJ;
    }else{
        return ++p; //es el equivalente a poner (p+1);
    }
}

tPosJ previousJ(tPosJ p, tListJ L){
    return --p;
}

bool insertItemJ(tItemJ d, tListJ *L){
    tPosJ i;
    if(L->lastPos == MAX-1){
        return false;
    }else{
        if(isEmptyListJ(*L) || (strcmp(d.juryName, L->data[L->lastPos].juryName) > 0)){
            L->lastPos++;
            L->data[L->lastPos] = d;
        }else{
            L->lastPos++;
            for(i = L->lastPos; i > 0 && (strcmp(d.juryName, L->data[i-1].juryName) < 0); i--){
                L->data[i] = L->data[i-1];
            }
            L->data[i] = d;
        }
        return true;
    }
}

void deleteAtPositionJ(tPosJ p, tListJ *L){
    tPosJ i;
    L -> lastPos --;
    for(i = p; i <= L->lastPos; i++){
        L->data[i] = L->data[i + 1];
    }
}

tItemJ getItemJ(tPosJ p, tListJ L){
    return L.data[p];
}

void updateItemJ(tItemJ d, tPosJ p, tListJ *L){
    L -> data[p] = d;
}

tPosJ findItemJ(tJuryName d, tListJ L){
    tPosJ q;

    if(isEmptyListJ(L)){
        return NULLJ;
    }else if((strcmp(d, L.data[0].juryName) < 0) || (strcmp(d, L.data[L.lastPos].juryName) > 0)){
        return NULLJ;
    }else{
        for(q = 0; (q < L.lastPos) && (strcmp(L.data[q].juryName, d) < 0); q++);
        if(strcmp(L.data[q].juryName, d) == 0){
            return q;
        }else{
            return NULLJ;
        }
    }
}
