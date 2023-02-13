/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#ifndef STATIC_LIST_H
#define STATIC_LIST_H

#include "types.h"

#define LNULL (-1) //Constante para indicar pos Nula.
#define MAX 25 //Tamaño máximo del array cuando usamos implementación Estática.

typedef int tPosL;
typedef struct {
    tItemL data[MAX];
    tPosL lastPos;
}tList;

void createEmptyList(tList *L);
bool isEmptyList(tList L);
tPosL first(tList L);
tPosL last(tList L);
tPosL next(tPosL p, tList L);
tPosL previous(tPosL p, tList L);
bool insertItem(tItemL d, tPosL p, tList *L);
void deleteAtPosition(tPosL p, tList *L);
tItemL getItem(tPosL p, tList L);
void updateItem(tItemL d, tPosL p, tList *L);
tPosL findItem(tParticipantName d, tList L);

#endif
