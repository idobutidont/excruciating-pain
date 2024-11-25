/***************************************************************
* FILENAME: main.c
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
        printf("\nFailed to save file, file not found.\n");
        return -1;
    }

    fwrite(&player, sizeof(PlayerData), 1, f);
    printf("\nFile has been saved.\n");
    fclose(f);
    return 1;
}

int load(PlayerData *player) {
    FILE *f;

    if ( (f = fopen("save.dat", "r")) == NULL ) {
        printf("\nFailed to load file, file not found.\n");
        return -1;
    }

    fread(&(*player), sizeof(PlayerData), 1, f);

    printf("\nFile has been loaded.\n");
    fclose(f);
    return 1;
}

// void initializePlayer(PlayerData *player) {

// }