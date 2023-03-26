/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef JURY_LIST_H
#define JURY_LIST_H

#include "types.h"
#include "participant_list.h"

#define NULLJ (-1) //Constante para indicar pos Nula.
#define MAX 10 //Tamaño máximo del array cuando usamos implementación Estática.

typedef int tPosJ;
typedef struct tItemJ {
    tJuryName juryName;
    tNumVotes totalVoters;
    tNumVotes validVoters;
    tNumVotes nullVotes;
    tListP participantList;
} tItemJ;
typedef struct {
    tItemJ data[MAX];
    tPosJ lastPos;
}tListJ;

void createEmptyListJ(tListJ *L);
bool isEmptyListJ(tListJ L);
tPosJ firstJ(tListJ L);
tPosJ lastJ(tListJ L);
tPosJ nextJ(tPosJ p, tListJ L);
tPosJ previousJ(tPosJ p, tListJ L);
bool insertItemJ(tItemJ d, tListJ *L);
void deleteAtPositionJ(tPosJ p, tListJ *L);
tItemJ getItemJ(tPosJ p, tListJ L);
void updateItemJ(tItemJ d, tPosJ p, tListJ *L);
tPosJ findItemJ(tJuryName d, tListJ L);

#endif
