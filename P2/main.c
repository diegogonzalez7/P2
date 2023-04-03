/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: DIEGO FERNÁNDEZ GÓMEZ LOGIN 1: diego.fgomez
 * AUTHOR 2: DIEGO GONZÁLEZ GONZÁLEZ LOGIN 2: diego.gonzalez7
 * GROUP: 4.2
 * DATE: ** / ** / **
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "jury_list.h"

#define MAX_BUFFER 255

//PRIMERA ENTREGA
void create(char *commandNumber, char operacion, char *param1, char *param2, tListJ *J);
void new(char *commandNumber, char operacion, char *param1, char *param2, char *param3, tListJ *J);
void vote(char* commandNumber, char operacion, char *param1, char* param2, tListJ *J);
void stats(char *commandNumber, char operacion, tListJ *J);
//SEGUNDA ENTREGA
void disqualify (char *commandNumber, char operacion, char *param1, tListJ *J);
void remov(char *commandNumber, char operacion, tListJ *J);
void winners(char *commandNumber, char operacion, tListJ *J);

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, tListP *P, tListJ *J) {

    switch (command) {
        case 'C':
            create(commandNumber, command, param1, param2, J);
            break;
        case 'N':
            new(commandNumber, command, param1, param2, param3, J);
            break;
        case 'V':
            vote(commandNumber, command, param1, param2, J);
            break;
        case 'D':
            disqualify(commandNumber, command, param1, J);
            break;
        case 'S':
            stats(commandNumber, command, J);
            break;
        case 'R':
            remov(commandNumber, command, J);
            break;
        case 'W':
            winners(commandNumber, command, J);
            break;
        default:
            break;
    }
}

void create(char *commandNumber, char operacion, char *param1, char *param2, tListJ *J){            //ACABADO
    tItemJ jurado;
    tPosJ q;
    strcpy(jurado.juryName, param1);
    jurado.totalVoters = atoi(param2);
    jurado.nullVotes = 0;
    jurado.validVotes = 0;

    printf("********************\n");
    printf("%s %c: jury %s totalvoters %s\n", commandNumber, operacion, param1, param2);

    q = findItemJ(jurado.juryName, *J);
    if(insertItemJ(jurado, J) && q == NULLJ){    //puede insertar y el jurado no existe
        printf("* Create: jury %s totalvoters %s\n", param1, param2);
        createEmptyListP(&jurado.participantList);
        q = findItemJ(jurado.juryName, *J);
        updateItemJ(jurado, q, J);
    }else{
        printf("+ Error: Create not possible\n");
    }
}
void new(char *commandNumber, char operacion, char *param1, char *param2, char *param3, tListJ *J){ //ACABADO
    tItemJ jurado;
    tItemP participante;
    tPosP p; tPosJ j;

    participante.numVotes = 0;
    strcpy(participante.participantName, param2);
    if (strcmp(param3, "eu") != 0) {
        participante.EUParticipant = true;
    } else participante.EUParticipant = false;


    printf("********************\n");
    printf("%s %c: jury %s participant %s location %s\n", commandNumber, operacion, param1, param2, param3);

    j = findItemJ(param1, *J);  //busca en la lista de jurados

    if (j != NULLJ) {   //lo encuentra
        jurado = getItemJ(j, *J);
        p = findItemP(param2, jurado.participantList);   //busca en la lista de participantes
        if(p == NULLP){ //no existe en la lista
            if (insertItemP(participante, &jurado.participantList)){    //mira si puede insertar
                printf("* New: jury %s participant %s location %s\n", param1, param2, param3);
                updateItemJ(jurado,j,J);
            }
        }
        else printf("+ Error: New not possible\n");
    }else{
        printf("+ Error: New not possible\n");
    }
}

void vote(char *commandNumber, char operacion, char *param1, char* param2, tListJ *J) {             //ACABADO
    tItemJ jurado;
    tItemP participante;
    tPosJ j; tPosP p;
    char *EU;

    printf("********************\n");
    printf("%s %c: jury %s participant %s\n", commandNumber, operacion, param1, param2);
    j = (findItemJ(param1, *J));    //busca jurado

    if (j == NULLJ || isEmptyListJ(*J)) {   //no encuentra al jurado o lista vacía
        printf("+ Error: Vote not possible\n");
    } else {                //no encuentra al participante en la lista
        jurado = getItemJ(j, *J);
        p = findItemP(param2, jurado.participantList);
        if (p == NULLP) {
            printf("+ Error: Vote not possible. Participant %s not found in jury %s. NULLVOTE\n", param2, param1);
            jurado.nullVotes++;
            updateItemJ(jurado, j, J);
            //printf("Los votos nulos del %s son %d, y los validos son %d\n",jurado.juryName, jurado.nullVotes, jurado.validVotes);
        } else {
            participante = getItemP(p, jurado.participantList);
            jurado.validVotes++;
            participante.numVotes++;
            if (!participante.EUParticipant) EU = "eu"; else EU = "non-eu";
            printf("* Vote: jury %s participant %s location %s numvotes %d\n", jurado.juryName,
                   participante.participantName, EU, participante.numVotes);
            updateItemP(participante, p, &jurado.participantList);
            updateItemJ(jurado, j, J);
            //printf("Los votos nulos del %s son %d, y los validos son %d\n",jurado.juryName, jurado.nullVotes, jurado.validVotes);
        }
    }
}

void stats(char *commandNumber, char operacion, tListJ *J) {                                        //ACABADO :)
    tItemJ jurado;
    tItemP participante;
    tPosJ j;
    tPosP p;
    char *EU;

    printf("********************\n");
    printf("%s %c:\n", commandNumber, operacion);
    if (isEmptyListJ(*J)) {
        printf("+ Error: Stats not possible\n");

    } else {
        j = firstJ(*J);
        while (j != NULLJ) {
            jurado = getItemJ(j, *J);
            printf("Jury %s\n", jurado.juryName);
            if (isEmptyListP(jurado.participantList)) {
                printf("No participants\n");
            } else {
                p = firstP(jurado.participantList);
                while (p != NULLP) {
                    participante = getItemP(p, jurado.participantList);
                    if (!participante.EUParticipant) EU = "eu"; else EU = "non-eu";
                    printf("Participant %s location %s numvotes %d ", participante.participantName, EU,
                           participante.numVotes);
                    if (jurado.validVotes == 0) {
                        printf("(0.00%%)\n");
                    } else printf("(%.2f%%)\n", (float) participante.numVotes / ((float) jurado.validVotes) * 100.0);
                    p = nextP(p, jurado.participantList);
                }
            }
            printf("Nullvotes %d\n", jurado.nullVotes);
            printf("Participation: %d votes from %d voters (%.2f%%)\n\n", (jurado.validVotes + jurado.nullVotes), jurado.totalVoters,
                   ((float) jurado.validVotes + (float) jurado.nullVotes) / (float) jurado.totalVoters * 100.0);
            j = nextJ(j, *J);
        }
    }
}

void disqualify (char *commandNumber, char operacion, char *param1, tListJ *J) {
    tItemJ jurado;
    tItemP participante;
    tPosP p; tPosJ j;

    printf("********************\n");
    printf("%s %c: participant %s\n", commandNumber, operacion, param1);

    if (isEmptyListJ(*J)) {
        printf("+ Error: Disqualify not possible\n");
    }
    else {
        j = firstJ(*J);
        while (j != NULLJ) {
            jurado = getItemJ(j,*J);
            printf("Jury %s\n", jurado.juryName);
            p = findItemP(param1, jurado.participantList);
            if (p != NULLP) {
                participante = getItemP(p, jurado.participantList);
                printf("Participant %s disqualified\n\n", participante.participantName);
                jurado.nullVotes += participante.numVotes;
                jurado.validVotes -= participante.numVotes;
                deleteAtPositionP(p,&jurado.participantList);
                updateItemJ(jurado, j, J);
                //printf("Los votos nulos de %s son %d\n", jurado.juryName, jurado.nullVotes);
            } else {
                printf("No participant %s\n\n", param1);
            }
            j = nextJ(j,*J);
        }
    }
}

void remov(char *commandNumber, char operacion, tListJ *J) {
    tItemJ jurado;
    tItemP participante;
    tPosJ j; tPosP p;
    int contador_jurados = 0;
    bool flag = false;

    printf("********************\n");
    printf("%s %c: \n", commandNumber, operacion);

    if (isEmptyListJ(*J)) {
        printf("+ Error: Remove not possible\n");
    } else {
        j = firstJ(*J);
        while (j != NULLJ) {
            j = firstJ(*J); // Te faltaba esto, saltaba al jurado3 porque el deleteatPosition ya te manda a la siguiente posicion por tanto hacias dos saltos
            //entonces teniamos que mandar al first arriba del while para que siempre empezara a comprobar desde la primera posicion.
            jurado = getItemJ(j,*J);
            if (jurado.validVotes == 0) {
                printf("* Remove: jury %s\n", jurado.juryName);
                deleteAtPositionJ(j,J);
                contador_jurados ++;
            }
            j = nextJ(j, *J);
            if (contador_jurados == 0) {
                printf("+ Error: Remove not possible\n");
            }
        }
    }
}
void winners(char *commandNumber, char operacion, tListJ *J){
    tItemJ jurado;
    tItemP participante, participante2;
    tPosJ j; tPosP p;
    int cont_participantes = 0;
    int aux = 0, aux1 = 0;


    printf("********************\n");
    printf("%s %c: \n", commandNumber, operacion);

    if(isEmptyListJ(*J)){
        printf("+ Error: Winners not possible\n");
    }else{
        j = firstJ(*J);
        while(j != NULLJ){
            jurado = getItemJ(j, *J);
            printf("Jury %s\n", jurado.juryName);
            if (isEmptyListP(jurado.participantList)) {
                printf("Location eu: No winner\n");
                printf("Location non-eu: No winner\n");
            } else {
                p = firstP(jurado.participantList);
                while (p != NULLP) {
                    participante = getItemP(p, jurado.participantList);
                    if(!participante.EUParticipant){
                        if(aux1 < participante.numVotes){
                            printf("Location eu: Participant %s numvotes %d\n", participante.participantName, participante.numVotes);
                        }
                        aux1 = participante.numVotes;
                    }else{
                        if(aux < participante.numVotes){
                            printf("Location non-eu: Participant %s numvotes %d\n", participante.participantName, participante.numVotes);
                        }
                        aux = participante.numVotes;
                    }
                    p = nextP(p, jurado.participantList);
                }
            }
            j = nextJ(j, *J);
        }
    }
}

void readTasks(char *filename, tListP *P, tListJ *J) {

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, P, J);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {
    tListP P;
    tListJ J;

    createEmptyListJ(&J);
    char *file_name = "create.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
        #ifdef INPUT_FILE
        file_name = INPUT_FILE;
        #endif
    }

    readTasks(file_name, &P, &J);

    return 0;
}
