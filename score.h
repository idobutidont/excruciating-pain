#ifndef score_h
#define score_h
#include "player.h"

typedef struct
{
    char username[16];
    int score;
    
} Score;

void printScoreMenu();
/*
    SCOREBOARD

    Username                Scores              
    Guweh banget            42562               

*/

int printScores();

int PutPlayerToScore(PlayerData player);
int PutScoreToFile(Score score);

int Sort();

int HitungScore();
#endif