/***************************************************************
* FILENAME: score.c
* DESCRIPTION: file untuk Scoreboard, simpan skor, dan highskor
* AUTHOR: NURAHMA, AZZAR
* DATE: 
****************************************************************/

#include "score.h"
#include "menu.h"

#include <stdio.h>
#include <windows.h>
#include <conio.h>


void ViewScore() {

    clear_screen();
    setConsoleSize(32, 26);

    SortScore();

    printf("\n\t  SCOREBOARD\n");
    printf("\tName\tScores\n");
    printScores();

    printf("\n    Press any key to exit...");

    getch();

}

int SortScore() {
    FILE *f;

    // Buka file untuk membaca
    if ((f = fopen(SCORE_FILE, "r")) == NULL) {
        return -1;
    }

    // Dapatkan jumlah struct dari, besar file dibagi besar struct nya.
    // Karena setiap kita nge "write" data ke file, kita tulis dengan besar satu struct.
    fseek(f, 0, SEEK_END);
    int structAmount = (int) ftell(f) / (int) sizeof(Score);

    Score players[structAmount];

    rewind(f);

    structAmount = 0;
    while (fread(&players[structAmount], sizeof(Score), 1, f)) {
        structAmount++;
    }

    fclose(f);

    //Sorting (descending)
    for (int i = 0; i < structAmount -1; i++) {
        for (int j =0; j < structAmount - i -1; j++) {
            if (players[j].score < players[j+1].score) {
                Score temp = players[j];
                players[j] = players[j+1];
                players[j+1] = temp;
            }
        }
    }

    if ((f = fopen(SCORE_FILE, "w")) == NULL) {
        return -1;
    }

    // hanya tulis 20 atau kurang score saja.
    structAmount = min(structAmount, 20);

    //Tulis data yang sudah diurutkan ke dalam file
    for (int i = 0; i < structAmount; i++) {
        fwrite(&players[i], sizeof(Score), 1, f);
    }
    fclose(f);

    return 1;
}

int printScores() {

    FILE *f;
    Score player;

    if ((f = fopen(SCORE_FILE, "r")) == NULL) {
        return -1;
    }

    while (fread (&player, sizeof(Score), 1, f)) {
        printf("\t%s\t%d\n", player.initial, player.score);
    }

    fclose(f);
    return 1;

}

int PutPlayerToScore(PlayerData *player, Score *score) {
    
    strcpy(score->initial, player->initial);
    score->score = player->score;

    return 1;
}

int PutScoreToFile(Score score) {

    FILE *f;

    if ((f = fopen(SCORE_FILE, "a")) == NULL) {
        return -1;
    }

    fwrite(&score, sizeof(Score), 1, f);
        
    fclose(f);
    return 1;
}

int loadHighscore(Score *highscore) {
    FILE *f;

    if ((f = fopen(HIGHSCORE_FILE, "r")) == NULL) {
        return -1;
    }

    fread (&(*highscore), sizeof(Score), 1, f);
    fclose(f);
    return 1;
}

int saveHighscore(Score *highscore) {
    FILE *f;

    if ((f = fopen(HIGHSCORE_FILE, "w")) == NULL) {
        return -1;
    }

    fwrite (&(*highscore), sizeof(Score), 1, f);
    fclose(f);
    return 1;
}

void initializeHighscore (Score *Highscore) {
    
    if (loadHighscore(&*Highscore) == -1) {
        Highscore->score = -1;
        strcpy(Highscore->initial, "NUL");
    }

}