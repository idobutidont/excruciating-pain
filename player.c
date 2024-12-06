/***************************************************************
* FILENAME: player.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "player.h"
#include <stdio.h>

int savePlayer(PlayerData *player) {
    FILE *f;

    if ( (f = fopen(SAVE_FILE, "w")) == NULL ) {
        return -1;
    }

    fwrite(&*player, sizeof(PlayerData), 1, f);
    fclose(f);
    return 1;
}

int loadPlayer(PlayerData *player) {
    FILE *f;

    if ( (f = fopen(SAVE_FILE, "r")) == NULL ) {
        return -1;
    }

    fread(&(*player), sizeof(PlayerData), 1, f);
    fclose(f);
    return 1;
}