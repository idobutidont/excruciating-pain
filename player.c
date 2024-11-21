#include "player.h"
#include <stdio.h>
#include <stdlib.h>

void save(PlayerData player) {
    FILE *f;

    if ( (f = fopen("save.dat", "w")) == NULL ) {
        printf("\nFailed to save file, file not found.");
        exit(1);
    }

    fwrite(&player, sizeof(PlayerData), 1, f);
    printf("\nFile has been saved.");
    fclose(f);
}

void load(PlayerData *player) {
    FILE *f;

    if ( (f = fopen("save.dat", "r")) == NULL ) {
        printf("\nFailed to load file, file not found.");
        exit(1);
    }

    fread(&(*player), sizeof(PlayerData), 1, f);

    printf("\nFile has been loaded.");
    exit(1);
}