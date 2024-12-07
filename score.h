#ifndef score_h
#define score_h

#include "player.h"

#define SCORE_FILE "score.dat"
#define HIGHSCORE_FILE "highscore.dat"

typedef struct {
    char initial[3];
    int score;
} Score;

// Scoreboard modules
void ViewScore();
int SortScore();
int printScores();
// End Scoreboard

// file score handling modules
int PutPlayerToScore(PlayerData *player, Score *score);
int PutScoreToFile(Score score);
// end file score handling

// Highscore handling modules
int loadHighscore(Score *highscore);
int saveHighscore(Score *highscore);
void initializeHighscore(Score *Highscore);
// End Highscore handling

#endif