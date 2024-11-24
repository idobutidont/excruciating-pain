#include "score.h"
#include <stdio.h>
#include <windows.h>
#include "helper.h"

void printScoreMenu() {

    int type, mode;

    do
    {
        system("cls");   
        printScores();

        printf("Mode (0: Descending) / (1: Ascending): ");  scanf("%d", &mode);
        printf("Type (0 score) (1 moves) (2 max_move) (3 disks) (4 towers): "); scanf("%d", &type);

        switch(PlayerInput()) {
            case 4: Sort(mode, type); break;
            default: break;
        }

    } while (1);
    
    
}

int printScores() {

    FILE *f;
    Score player;

    if ( (f = fopen("score.dat", "r")) == NULL ) {
        return -1;
    }

    while (fread(&player, sizeof(Score), 1, f)) 
        printf("%s %d %d/%d %d %d\n", player.username, player.score, player.moves, player.max_moves, player.max_disk, player.max_tower);
    
    fclose(f);

    return 1;
}

int PutPlayerToScore(PlayerData player) {
    
    Score score;

    strcpy(score.username, player.username);
    score.score = player.score;
    score.moves = player.moves;
    score.max_moves = player.max_moves;
    score.max_disk = player.max_disks;
    score.max_tower = player.max_towers;

    PutScoreToFile(score);

    return 1;
}

int PutScoreToFile(Score score) {

    FILE *f;

    if ( (f = fopen("score.dat", "a")) == NULL ) {
        return -1;
    }

    fwrite(&score, sizeof(Score), 1, f);

    fclose(f);

    return 1;

}

// Struct File sort based on bubble sort algorithm, yes, mental illness.
// VERY BROKEN, MIGHT NUKE YOUR COMPUTER (REAL)
int Sort(int mode, int type) {

    FILE *f;
    int itemplayer, itemtemp, fileSize, structAmount, sub;

    if ( (f = fopen("score.dat", "r+")) == NULL ) {
        return -1;
    }

    unsigned long long sizeScore = sizeof(Score);

    fseek(f, 0, SEEK_END);
    fileSize = ftell(f);
    structAmount = fileSize / sizeScore;

    Score score[structAmount], temp;

    rewind(f);

    for (int i = 0; i < structAmount; ++i)
        fread(&score[i], sizeScore, 1, f);

    for (int i = 0; i < structAmount - 1; ++i) {
        sub = i;
        for (int j = i + 1; j < structAmount; ++j) {
            itemplayer = TypeToSort(type, score[sub]);
            itemtemp = TypeToSort(type, score[j]);

            if (compare(mode, itemplayer, itemtemp))
                sub = j;

        }

        temp = score[sub];
        score[sub] = score[i];
        score[i] = temp;

    }

    rewind(f);

    for (int i = 0; i < structAmount; ++i)
        fwrite(&score[i], sizeScore, 1, f);

    fclose(f);
    printf("\nSorted.\n");

    return 1;

}

int compare(int mode, int x, int y) {

    if (mode == 0) {
        return x < y; // descending
    } else {
        return x > y; // ascending
    }

}

int TypeToSort(int type, Score score) {

    switch (type) {

        case 0: return score.score;
        case 1: return score.moves;
        case 2: return score.max_moves;
        case 3: return score.max_disk;
        case 4: return score.max_tower;

        default: printf("error at sorting type"); getchar(); return -1;
    }
    
}