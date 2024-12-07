#ifndef score_h
#define score_h

#include "player.h"

#define SCORE_FILE "score.dat"

typedef struct {
    char initial[3];
    int score;
} Score;

// Scoreboard modules
void ViewScore();
int SortScore();
int printScores();
void printNoScore();
// End Scoreboard

// file score handling modules
int PutPlayerToScore(PlayerData *player, Score *score);
int PutScoreToFile(Score score);
// end file score handling

// Highscore handling modules
int loadHighscore(Score *highscore);
void initializeHighscore(Score *highscore);
// End Highscore handling

#endif