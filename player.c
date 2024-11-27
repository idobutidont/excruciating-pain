/***************************************************************
* FILENAME: player.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "player.h"
#include <stdio.h>
#include <stdlib.h>

int save(PlayerData player) {
    FILE *f;

    if ( (f = fopen("save.dat", "w")) == NULL ) {
        return -1;
    }

    fwrite(&player, sizeof(PlayerData), 1, f);
    fclose(f);
    return 1;
}

int load(PlayerData *player) {
    FILE *f;

    if ( (f = fopen("save.dat", "r")) == NULL ) {
        return -1;
    }

    fread(&(*player), sizeof(PlayerData), 1, f);

    fclose(f);
    return 1;
}

// void initializePlayer(PlayerData *player) {

// }