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
    int handPosition;
    int max_towers;
    int max_disks;
} PlayerData;

int save(PlayerData player);

int load(PlayerData *player);

//void initializePlayer(PlayerData *player);

#endif