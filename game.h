#ifndef game_h
#define game_h

// WM = WRONG MOVE
// Invalid Player Moves
#define WM_DISK_AT_HAND                -50
#define WM_TOWER_IS_EMPTY              -51
#define WM_HAND_IS_EMPTY               -52
#define WM_HAND_IS_BIGGER_THAN_TOWER   -53

// Valid Player Moves
#define DISK_PUT_DOWN   111
#define DISK_PICK_UP    112
#define CURSOR_MOVE     113

#define WON 101
#define LOST -101
#define EXIT -100

#include "score.h"

// Main Module
int processGame(PlayerData *player, Score Highscore);
/* Return 1 if the player won, -1 otherwise */

// Cases
int HandIsEmpty(int hand);
int HandIsBiggerThanTower(int hand, Tower tower);
int HasWon(PlayerData *player);
int HasLost(PlayerData *player);
int HasExit(int input_result);
int HasDiskStacked(Tower tower[], int start_pos);
int HasRanOutOfMoves(int moves, int max_moves);
int HandAtRightEdge(int hand);
int HandAtLeftEdge(int hand);
int MoveIsValid(int move);
int HasPutDownDisk(int input_result);
// end Cases

// Print Modules
void printTower(Tower towers[]);
void printCursor(int hand_position);
void printHand(int hand_position, int hand);
void printUI(int moves, int max_moves, int score, int input_result, Score Highscore);
void printWrongMove(int input_result);
void printEndScreen(int WinOrLose, Score playerScore);
// End Print Modules

// Gameplay Modules
int MoveCursor(int LeftOrRight, int *hand_position);
int PickUpDisk(Tower *tower, int *hand);
int PutDownDisk(Tower *tower, int *hand);
// End Gameplay Modules

// String Conversion Handling Modules
void DiskToString(char* stringDisk,int current_disk, int biggest_disk);
void TowerToString(char* stringTower,int biggest_disk, char accessories);
// End String Conversion

// Game Calculation Modules
void IncrementMove(int *moves);
int CalculateMinMove(int disk, int tower);
int CalculateScoreWeight(PlayerData *player);
void CalculateScore(PlayerData *player, int scoreWeight);
// End Game Calculation

// Player Input
int PlayerEvent(PlayerData *player);

// Player modules
int initializePlayer(PlayerData *player);
int initializePlayerMenu(PlayerData *player);

// Diff select module
int DiffSelect(PlayerData *player);

// Username input
void InputInitial(char* initial);

// Escape menu
int EscapeMenu();

// Custom Disk Tower Menu
void InputCustom(int *disk, int *tower);

#endif