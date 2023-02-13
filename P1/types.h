#ifndef PRO2_2023_P1_TYPES_H
#define PRO2_2023_P1_TYPES_H


#define NAME_LENGTH_LIMIT 25
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef char tParticipantName[NAME_LENGTH_LIMIT];
typedef int tNumVotes;
typedef bool tEUParticipant;

typedef struct tItemL {
    tParticipantName participantName;
    tNumVotes numVotes;
    tEUParticipant EUParticipant;
} tItemL;

#endif //PRO2_2023_P1_TYPES_H
