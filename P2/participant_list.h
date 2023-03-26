/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: ***************************** LOGIN 1: **********
 * AUTHOR 2: ***************************** LOGIN 2: **********
 * GROUP: *.*
 * DATE: ** / ** / **
 */

#ifndef PARTICIPANT_LIST_H
#define PARTICIPANT_LIST_H

#include "stddef.h"
#include "types.h"

#define NULLP NULL

typedef struct tItemP {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
} tItemP;
typedef struct Node* tPosP;
struct Node{
    tItemP data;
    tPosP next;
};

typedef tPosP tListP;

//GENERADORAS
void createEmptyListP(tListP *L);
bool isEmptyListP(tListP L);

//OBSERVADORAS
tPosP firstP(tListP L);
tPosP lastP(tListP L);
tPosP nextP(tPosP p, tListP L);
tPosP previousP(tPosP p, tListP L);
tPosP findItemP(tParticipantName d, tListP L);
tItemP getItemP(tPosP p, tListP L);

//MODIFICADORAS
bool insertItemP(tItemP d, tListP * L);
void updateItemP(tItemP d, tPosP p, tListP *L);

//DESTRUCTORAS
void deleteAtPositionP(tPosP p, tListP *L);
#endif
