#ifndef player_h
#define player_h

#include "tower.h"

typedef struct {
    char username[64];
    int moves;
    int max_moves;
    int difficulty;
    Tower tower[6];
    int hand;
    int currentPosition;
    int max_towers;
    int max_disks;
} PlayerData;

void save(PlayerData player);

void load(PlayerData *player);

#endif