#ifndef game_h
#define game_h

// WM = WRONG MOVE
// Invalid Player Moves
#define WM_DISK_AT_HAND                -5
#define WM_TOWER_IS_EMPTY              -6
#define WM_HAND_IS_EMPTY               -7
#define WM_HAND_IS_BIGGER_THAN_TOWER   -8

// Valid Player Moves
#define DISK_PUT_DOWN   1
#define DISK_PICK_UP    2
#define CURSOR_MOVE     3

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
int HasDiskStacked(Tower tower[], int start_pos);
int HasRanOutOfMoves(int moves, int max_moves);
int HandAtRightEdge(int hand);
int HandAtLeftEdge(int hand);
int MoveIsValid(int move);
int PlayerPutDownDisk(int input);
// end Cases

// Print Modules
void printTower(Tower towers[]);
void printCursor(int hand_position);
void printHand(int hand_position, int hand);
void printUI(int moves, int max_moves, int input);
void printWrongMove(int input);
// End Print Modules

// Gameplay Modules
int MoveCursor(int LeftOrRight, int *hand_position);
int PickUpDisk(Tower *tower, int *hand);
int PutDownDisk(Tower *tower, int *hand);
void IncrementMove(int *moves);
// End Gameplay Modules

// Player Input
int PlayerEvent(PlayerData *player);

//Placeholder module
void initializePlayer(PlayerData *player);

// Diff select module
void DiffSelect(PlayerData *player);

// Username input
void InputUsername(PlayerData *player);

#endif