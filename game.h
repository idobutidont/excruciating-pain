#ifndef game_h
#define game_h

#define WRONG_MOVE -2

#define WON 1
#define LOSE -1

#include "player.h"

// Main Module
int inGame(PlayerData *player);
/* Return 1 if the player won, -1 otherwise */

// Cases
int HandIsEmpty(int hand);

int HandIsBiggerThanTower(int hand, Tower tower);

int HasWon(PlayerData *player);

int HasLose(PlayerData *player);

int HasDiskStacked(Tower tower[], int MAX_DISKS, int MAX_TOWERS);

int HasRanOutOfMoves(int moves, int max_moves);

int HandAtRightEdge(int hand, int MAX_TOWERS);

int HandAtLeftEdge(int hand);
// end Cases

// Print Modules
void printTower(char *stringDisk, const char *stringTower, Tower towers[], int biggest_disk, int MAX_DISKS, int MAX_TOWERS);

void PutDiskTowerToString(int height, Tower towers[], int tower, char *stringDisk, int biggest_disk, char stringDiskTower[4096], const char *stringTower);

void printCursor(const char* stringCursor, int hand_position, int lenArray);

void printHand(char* stringHand, int hand_position, int hand, int lenArray, int biggest_disk);

void printSpaces(int lenArray, int hand_position);

void printUI(int moves, int max_moves, char* message);
// End Print Modules

// Gameplay Modules
int MoveCursor(int LeftOrRight, int *hand_position, int MAX_TOWERS);

int PickUpDisk(Tower *tower, int *hand, char* message);

int PutDownDisk(Tower *tower, int *hand, int *moves, char* message);

void IncrementMove(int *moves);
// End Gameplay Modules

// Player Input
int PlayerEvent(PlayerData *player, char* message);


//Placeholder module
void initializePlayer(PlayerData *player);

#endif