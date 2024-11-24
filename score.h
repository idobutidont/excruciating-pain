#ifndef score_h
#define score_h

#include "player.h"

typedef struct
{
    char username[64];
    int score;
    int moves;
    int max_moves;
    int max_disk;
    int max_tower;
    
} Score;


void printScoreMenu();
/*
    VERY OPTIMISTIC DEMO

    Username                Scores              Moves / Max             Disks          Towers
    Guweh banget            42562               240/255                 7              3


    Sort:           < Scores >
    Sort Mode:      < Ascending

    > Exit Menu

    Press Enter to confirm....
*/

int printScores();

int PutPlayerToScore(PlayerData player);
int PutScoreToFile(Score score);

int Sort(int mode, int type);

int compare(int mode, int x, int y);
// Compare Ascending / Descending

int TypeToSort(int type, Score score);
// which item to compare (0 for score, 1 for moves, 2 for towers, 3 for disks), and give that item to x to compare.

#endif