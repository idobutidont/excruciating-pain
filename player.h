#ifndef player_h
#define player_h

#include "tower.h"

#define SAVE_FILE "save.dat"

typedef struct {
    char username[16];
    int moves;
    int max_moves;
    int difficulty;
    Tower tower[6];
    int hand;
    int handPosition;
    int max_towers;
    int max_disks;
    int startTower;
    int score;
} PlayerData;

int save(PlayerData *player);
int load(PlayerData *player);

#endif