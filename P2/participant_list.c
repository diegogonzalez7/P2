/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
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
    return (L);
}

tPosP lastP(tListP L){
    tPosP q;
    for(q = L; q->next != NULLP; q = q->next);
    return q;
}

tPosP nextP(tPosP p, tListP L){
    if(lastP(L) == p){
        return NULLP;
    }else{
        return(p->next);
    }
}

tPosP previousP(tPosP p, tListP L){
    tPosP q;
    if(p == L) return NULLP;
    else{
        q=L;
        while((q->next)!= p){
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
    while((p->next != NULLP) && (strcmp(p->next->data.participantName, d.participantName) < 0)){
        p = p->next;
    }
    return p;
}

bool insertItemP(tItemP d, tListP * L){
    tPosP q, p;
    if(!createNode(&q)){
        return false;
    }else{
        q -> data = d;
        q -> next = NULLP;
        if(isEmptyListP(*L)){
            *L = q;
        }else if(strcmp(d.participantName, (*L)->data.participantName) < 0){
            q -> next = *L;
            *L = q;
        }else{
            p = findPosition(*L, d);
            q->next = p->next;
            p->next = q;
        }
        return true;
    }
}

void deleteAtPositionP(tPosP p, tListP *L){
    tPosP q;
    if(p == *L){*L = (*L)->next;}
    else if(p->next==NULLP){
        for(q = *L; q->next != p; q = q->next);
        q->next = NULLP;
    }
    else{
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

tItemP getItemP(tPosP p, tListP L){
    return(p->data);
}

void updateItemP(tItemP d, tPosP p, tListP *L){
    p->data = d;
}

tPosP findItemP(tParticipantName i, tListP L){
    tPosP q;
    if(isEmptyListP(L)){
        return NULLP;
    }else{
        for(q = L; (q != NULLP) && (strcmp(q->data.participantName, i) < 0); q = q->next);
        if(q != NULLP && (strcmp(q->data.participantName, i) == 0)){
            return q;
        }else{
            return NULLP;
        }
    }
}

