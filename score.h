#ifndef score_h
#define score_h

#include "player.h"

#define SCORE_FILE "score.dat"
#define HIGHSCORE_FILE "highscore.dat"

typedef struct
{
    char initial[3];
    int score;
    
} Score;

void ViewScore();

int printScores();

int PutPlayerToScore(PlayerData player, Score *score);
int PutScoreToFile(Score score);

int SortScore();

int HitungScore();

int loadHighscore(Score *highscore);
int saveHighscore(Score *highscore);

void initializeHighscore(Score *Highscore);

int CalculateScoreWeight(PlayerData *player);

void CalculateScore(PlayerData *player, int scoreWeight);

#endif