#include "score.h"
#include <windows.h>

void printScoreMenu() {

    int type, mode;

    system("cls");

    printScores();


    getchar();
    getchar();

}

int printScores() {

    FILE *f;
    PlayerData player;

    if ( (f = fopen("score.dat", "r")) == NULL ) {
        return -1;
    }

    while (fread(&player, sizeof(PlayerData), 1, f)) 
        printf("%s %d %d/%d %d %d\n", player.username, player.score, player.moves, player.max_moves, player.max_disks, player.max_towers);
    
    fclose(f);

    return 1;
}

int PutPlayerToScore(PlayerData player) {
    FILE *f;

    if ( (f = fopen("score.dat", "a")) == NULL) {
        return -1;
    }

    fwrite(&player, sizeof(PlayerData), 1, f);

    fclose(f);
    return 1;
}

// Struct File sort based on bubble sort algorithm, yes, mental illness.
// VERY BROKEN, MIGHT NUKE YOUR COMPUTER (REAL)
int Sort(int mode, int type) {

    FILE *f;
    PlayerData player, temp;
    int i, j, itemplayer, itemtemp;

    unsigned long long sizePlayer = sizeof(PlayerData);

    if ( (f = fopen("score.dat", "r+")) == NULL ) {
        return -1;
    }

    i = 0;

    while (!feof(f)) {

        fseek(f, i * sizeof(PlayerData), SEEK_SET);
        fread(&player, sizeof(PlayerData), 1, f);

        j = i;
        while (!feof(f)) {

            ++j;

            fseek(f, j*sizePlayer, SEEK_SET);
            fread(&temp, sizePlayer, 1, f);

            itemplayer = TypeToSort(type, player);
            itemtemp = TypeToSort(type, temp);

            if (compare(mode, itemplayer, itemtemp)) {

                fseek(f, i*sizePlayer, SEEK_SET);
                fwrite(&temp, sizePlayer, 1, f);

                fseek(f, j*sizePlayer, SEEK_SET);
                fwrite(&player, sizePlayer, 1, f);

                player = temp;

            }

        }

        if ( i < j ) {  // if j hits eof then i would also hit eof, effectively leaving the loop
            fseek(f, 0, SEEK_SET);
            ++i;
        }
    }

    fclose(f);
    printf("\nSorted.\n");

    return 1;

}

int compare(int mode, int x, int y) {

    if (mode == 0) {
        return x < y; // ascending
    } else {
        return x > y; // descending
    }

}

int TypeToSort(int type, PlayerData player) {

    switch (type) {

        case 0: return player.score;
        case 1: return player.moves;
        case 2: return player.max_disks;
        case 3: return player.max_towers;

        default: printf("error at sorting type"); getchar(); return -1;
    }
    
}