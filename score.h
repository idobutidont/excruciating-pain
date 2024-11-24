#ifndef score_h
#define score_h

#include "player.h"
#include <stdio.h>

void printScoreMenu();

int printScores();

int PutPlayerToScore(PlayerData player);
/*
    VERY OPTIMISTIC DEMO

    Username                Scores              Moves / Max             Towers          Disks
    Guweh banget            42562               240/255                 3               7


    Sort:           < Scores >
    Sort Mode:      < Ascending

    > Exit Menu

    Press Enter to confirm....
*/

int Sort(int mode, int type);

int compare(int mode, int x, int y);
// Compare Ascending / Descending

int TypeToSort(int type, PlayerData player);
// which item to compare (0 for score, 1 for moves, 2 for towers, 3 for disks), and give that item to x to compare.

#endif