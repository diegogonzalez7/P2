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

void new(char *commandNumber, char operacion, char *param1, char *param2, tList *L, int *votosnulos);
void stats(char *commandNumber, char operacion, char* param1, tList L, const int *votosnulos);
void vote(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos);
void disqualify(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos);


void processCommand(char *commandNumber, char operacion, char *param1, char*param2, tList *L, int *votosnulos) {

    switch (operacion) {
        case 'N':
            //printf("Command: %s %c %s %s\n", commandNumber, operacion, nacionalidad, param2);
            new(commandNumber, operacion, param1, param2, L, votosnulos);
            break;
        case 'V':
            vote(commandNumber, operacion, param1, L, votosnulos);
            break;
        case 'D':
            disqualify(commandNumber, operacion, param1, L, votosnulos);
            break;
        case 'S':
            stats(commandNumber, operacion, param1, *L, votosnulos);
            break;
        default:
            break;
    }
}

void new(char *commandNumber, char operacion, char *param1, char *param2, tList *L, int *votosnulos){
    tItemL r;
    r.numVotes = 0;
    (*votosnulos) = 0;
    strcpy(r.participantName, param1);
    if (strcmp(param2, "eu")!=0){
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

void vote(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos){
    tItemL r;
    tPosL p;
    char *EU;
    (*votosnulos) = 0;
    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);
    p = (findItem(param1, *L));
    if((p == LNULL) || isEmptyList(*L)){
        printf("+ Error: Vote not possible. Participant %s not found. NULLVOTE\n", param1);
        (*votosnulos)++;
    }else{
        r = getItem(p, *L);
        r.numVotes++;
        updateItem(r, p, L);
        if(!r.EUParticipant) EU = "eu"; else EU = "non-eu" ;
        printf("* Vote: participant %s location %s", param1, EU);
        printf(" numvotes %d\n", r.numVotes);
    }
}


void disqualify(char *commandNumber, char operacion, char* param1, tList *L, int *votosnulos){
    tItemL r;
    tPosL p;
    char *EU;
    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);
    p = (findItem(param1, *L));
    if(p == LNULL){
        printf("+ Error: Disqualify not possible");
        (*votosnulos)++;
    }else{
        r = getItem(p, *L);
        (*votosnulos) += r.numVotes;
        deleteAtPosition(p, L);
        if(!r.EUParticipant) EU = "eu"; else EU = "non-eu" ;
        printf("* Disqualify: participant %s location %s\n", param1, EU);
    }
}


void stats(char *commandNumber, char operacion, char* param1, tList L, const int *votosnulos){
    tItemL r;
    tPosL p;
    char *EU;
    int votosnuloss;
    int votos = atoi(param1);
    if(votosnulos == NULL){
        votosnuloss = 0;
    }else{
        votosnuloss = (*votosnulos);
    }

    int votostotales = 0;
    printf("********************\n");

    printf("%s %c: totalvoters %d\n", commandNumber, operacion, votos);
    if(isEmptyList(L) != true){
        for(p = first(L); p != LNULL; p = next(p, L)){
            r = getItem(p, L);
            votostotales = votosnuloss + r.numVotes;
            if(!r.EUParticipant) EU = "eu"; else EU = "non-eu" ;
            printf("Participant %s location %s", r.participantName, EU);
            printf(" numvotes %d ", r.numVotes);
            if (r.numVotes == 0){
                printf("(0.00%%)\n");

            } else printf("(%.2f%%)\n", (float)r.numVotes * 100.0);
        }

        printf("Null votes %d\n", votosnuloss);
        printf("Participation: %d votes from %d voters (%.2f%%)\n", votostotales, votos, (float)votostotales/(float)votos *100.0);


    }else{
        printf("+ Error: Stats not possible\n");
    }

}

void readTasks(char *filename, tList *L, int *votosnulos) {
    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, L, votosnulos);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tList L;
    createEmptyList(&L);
    int *votosnulos = malloc(sizeof (int));
    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name, &L, votosnulos);

    return 0;
}




