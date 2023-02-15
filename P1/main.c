/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 1
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#define MAX_BUFFER 255

#ifdef DYNAMIC_LIST
#include "dynamic_list.h"
#endif
#ifdef STATIC_LIST
#include "static_list.h"
#endif

void new(char *commandNumber, char operacion, char *param1, char *param2, tList *L);
void stats(char *commandNumber, char operacion, char* pais, tList L);
void vote(char *commandNumber, char operacion, char* param1, tList *L, int votosnulos, int votostotales);
void disqualify(char *commandNumber, char operacion, char* param1, tList *L, int votosnulos, int votostotales);


void processCommand(char *commandNumber, char operacion, char *param1, char*param2, tList *L, int votosnulos, int votostotales) {

    switch (operacion) {
        case 'N':
            new(commandNumber, operacion, param1, param2, L);
            break;
        case 'V':
            vote(commandNumber, operacion, param1, L, votosnulos, votostotales);
            break;
        case 'D':
            disqualify(commandNumber, operacion, param1, L, votosnulos, votostotales);
            break;
        case 'S':
            stats(commandNumber, operacion, param1, *L);
            break;
        default:
            break;
    }
}

void new(char *commandNumber, char operacion, char *param1, char *param2, tList *L){
    tItemL r;
    r.numVotes = 0;
    strcpy(r.participantName, param1);
    if (strcmp(param2, "eu")==0){
        r.EUParticipant = true;
    }
    else r.EUParticipant = false;
    /*if(strcmp("eu", param2) != 0 && strcmp("non-eu", param2) != 0){
        printf("+⎵Error:⎵New⎵not⎵possible");
    }else{

    }*/
    printf("********************\n");
    printf("%s %c: participant %s location %s\n", commandNumber, operacion, param1, param2);

    if((findItem(param1, *L)) != LNULL){
        printf("+ Error: New not possible");
    }else{
        insertItem(r, LNULL, L);
        printf("* New: participant %s location %s\n", param1, param2);
    }
}

void vote(char *commandNumber, char operacion, char* param1, tList *L, int votosnulos, int votostotales){
    tItemL r;
    tPosL p;
    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);
    p = (findItem(param1, *L));
    if(p == LNULL){
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE", param1);
    }else{
        r = getItem(p, *L);
        r.numVotes++;
        printf("* Vote: participant %s location %s numvotes %d\n", param1, (char*) r.EUParticipant, r.numVotes);
    }
}

void disqualify(char *commandNumber, char operacion, char* param1, tList *L, int votosnulos, int votostotales){
    tItemL r;
    tPosL p;
    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);
    p = (findItem(param1, *L));
    if(p == LNULL){
        printf("+ Error: Disqualify not possible");
    }else{
        votosnulos += r.numVotes;
        votostotales -= r.numVotes;
        deleteAtPosition(p, L);
        printf("* Disqualify: participant %s location %s\n", param1, (char*) r.EUParticipant);
    }
}


void stats(char *commandNumber, char operacion, char* param1, tList L){
    tItemL r;
    tPosL p;
    int votos = atoi(param1);
    char Europeo[7];

    printf("********************\n");
    float totalvotes = 0;

    printf("%s %c: totalvoters %d\n", commandNumber, operacion, votos);
    if(isEmptyList(L) != true){
        for (p = first(L); p != LNULL; p = next(p, L)){
            r = getItem(p, L);
            printf("Participant %s location ", r.participantName);
            if (r.EUParticipant == true) {
                printf("eu ");
            }
            else printf("non-eu ");
            printf("numvotes %d (%.2f%%)\n", r.numVotes);
        }
    }else
        printf("+ Error: Stats not possible"); //lista vacía
}

void readTasks(char *filename, tList *L, int votosnulos, int votostotales) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    int param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, L, votosnulos, votostotales);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tList L;
    createEmptyList(&L);
    int votosnulos=0, votostotales=0;
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &L, votosnulos, votostotales);

    return 0;
}






