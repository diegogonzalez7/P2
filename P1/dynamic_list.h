/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#ifndef DYNAMIC_LIST_H
#define DYNAMIC_LIST_H

#include "types.h"
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdio.h>
#define LNULL NULL

typedef struct Node* tPosL;
struct Node{
    tItemL data;
    tPosL next;
};
typedef tPosL tList;

//GENERADORAS
void createEmptyList(tList *L);
bool isEmptyList(tList L);

//OBSERVADORAS
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL p, tList L);
tPosL previous(tPosL p, tList L);
tPosL findItem(tParticipantName d, tList L);
tItemL getItem(tPosL p, tList L);

//MODIFICADORAS
bool insertItem(tItemL d, tPosL p, tList *L);
void updateItem(tItemL d, tPosL p, tList *L);

//DESTRUCTORAS
void deleteAtPosition(tPosL p, tList *L);

#endif
