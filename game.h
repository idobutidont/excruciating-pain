#ifndef game_h
#define game_h

#include "player.h"

// Main Module
int inGame(PlayerData *player);
/* Return 1 if the player won, -1 otherwise */

// Cases
int HandIsEmpty(int hand);

int HandIsBigerThanTower(int hand, Tower tower);

int HasWon(Tower tower[]);

int HasRanOutOfMoves(int moves, int max_moves);
// end Cases

// Print Modules
void printTower(Tower towers[], int biggest_disk, char* disk, const char* empty_disk);

void printCursor(int current_pos, int lenArray, char accessories);

void printHand(int current_pos, int hand, int lenArray, int biggest_disk);

void printUI(int moves, int max_moves, const char* message);
// End Print Modules

// Player Input
int EventDetection (Tower *tower, int *hand, int *current_pos, int *moves, char *message);


//Placeholder module
void initializePlayer(PlayerData *player);

#endif