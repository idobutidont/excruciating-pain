#ifndef player_h
#define player_h

#include "tower.h"

#define SAVE_FILE "save.dat"

typedef struct {
    char initial[3];
    int moves;
    int max_moves;
    Tower tower[6];
    int hand;
    int handPosition;
    int max_towers;
    int max_disks;
    int startTower;
    int score;
    int difficultyFactor;
} PlayerData;

int savePlayer(PlayerData *player);
int loadPlayer(PlayerData *player);

#endif