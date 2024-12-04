/***************************************************************
* FILENAME: score.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "score.h"
#include <stdio.h>
#include <windows.h>
#include "helper.h"


void printScoreMenu() {

    
    system("cls");

    printf("SCOREBOARD\n");
    printf("Username           Scores\n");
    printScores();

    getchar();
    
}


int printScores() {

    FILE *f;
    Score player;

    if ((f = fopen("score.dat", "r")) == NULL) {
        return -1;
    }

    while (fread (&player, sizeof(Score), 1, f)) {
        printf("%s              %d\n", player.username, player.score);
    }
    
    fclose(f);
    return 1;

}


int PutPlayerToScore(PlayerData player) {

    Score score;
    
    strcpy(score.username, player.username);
    score.score = player.score;

    PutScoreToFile(score);

    return 1;
}

int PutScoreToFile(Score score) {

    FILE *f;

    if ((f = fopen("score.dat", "a")) == NULL) {
        return -1;
    }

    fwrite(&score, sizeof(Score), 1, f);
        
    fclose(f);
    return 1;
}


int Sort() {
    FILE *f;
    long i=0, j;
    Score player, temp;

    if ((f = fopen("score.dat", "r")) == NULL) {
        return -1;
    }
    
    while (!feof(f)) {
        fseek (f, (i*(sizeof(Score)+1)) + i, SEEK_SET);
        fscanf (f, "%s %d", &player.username, &player.score);
        j = i;
        while (!feof(f)) {
            j++;
            fseek (f, (j*(sizeof(Score)+1))+j, SEEK_SET);
            fscanf(f, "%s %d", &temp.username, &temp.score);
            
            if (player.score > temp.score) {
                fseek (f, i*(sizeof(Score)+1)+i, SEEK_SET);
                fprintf(f, "%s %d", temp.username, temp.score);
                fseek (f, j*(sizeof(Score)+1)+j, SEEK_SET);
                fprintf(f, "%s %d", player.username, player.score);

                strcpy(player.username , temp.username);
                player.score = temp.score;
            }
        }
        if (i < j) {
            fseek (f, 0, SEEK_SET); 
            i++;
        }
    }
    fclose (f);
    printf("\nSorted.\n");

    return 1;
}