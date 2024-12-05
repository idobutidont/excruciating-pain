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
#include <conio.h>


void ViewScore() {

    clear_screen();
    setConsoleSize(64, 32);

    Sort();

    printf("SCOREBOARD\n");
    printf("Username\t\tScores\n");
    printScores();

    getch();
}


int printScores() {

    FILE *f;
    Score player;

    if ((f = fopen("score.dat", "r")) == NULL) {
        return -1;
    }

    while (fread (&player, sizeof(Score), 1, f)) {
        printf("%s\t", player.username);
        printEqualIndent( (int) strlen(player.username), 16); //16 as in username max size
        printf("%d\n", player.score);
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
    Score players[100];
    int count = 0;

    // Buka file untuk membaca
    if ((f = fopen("score.dat", "r")) == NULL) {
        return -1;
    }

    //Baca data dari file
    while (fread(&players[count], sizeof(Score), 1, f)) {
        count++;
    }
    fclose(f);

    //Sorting (descending)
    for (int i = 0; i < count -1; i++) {
        for (int j =0; j < count - i -1; j++) {
            if (players[j].score < players[j+1].score) {
                Score temp = players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }

    if ((f = fopen("score.dat", "w")) == NULL) {
        return -1;
    }

    //Tulis data yang sudah diurutkan ke dalam file
    for (int i = 0; i < count; i++) {
        fwrite(&players[i], sizeof(Score), 1, f);
    }
    fclose(f);

    return 1;
}

int HitungScore(int difficulty, int moves) {
    int score_difficulty;
    score_difficulty = (10000*difficulty)/moves;
    return score_difficulty;
}
