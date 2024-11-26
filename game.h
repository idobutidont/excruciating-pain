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
void printTower(char* stringDisk, const char* stringTower, Tower towers[], int biggest_disk);

void printCursor(const char* stringCursor, int hand_position, int lenArray);

void printHand(char* stringHand, int hand_position, int hand, int lenArray, int biggest_disk);

void printSpaces(int lenArray, int hand_position);

void printUI(int moves, int max_moves, const char* message);
// End Print Modules

// Player Input
int EventDetection (Tower *tower, int *hand, int *hand_position, int *moves, char *message);


//Placeholder module
void initializePlayer(PlayerData *player);

#endif