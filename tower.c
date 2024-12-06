/***************************************************************
* FILENAME: tower.c
* DESCRIPTION: Basic Tower of Hanoi disk and tower handling, using stack array implementation
* AUTHOR: Idotoho
* DATE: 13 / 11 / 2024
****************************************************************/

#include "tower.h"

// Function to initialize tower
void initializeTower(Tower *tower) {
    tower->top = -1; // Initialize the tower as empty
}

// Fill the tower from the bottom, hence the loop started at the biggest disk first.
void initializeDisks(Tower *tower, int MAX_DISKS) {
    for (int i = 2 * MAX_DISKS - 1; i>= 1; i -= 2)
        push(&*tower, i);
}

// Cases
int TowerIsEmpty(Tower tower) {
    return tower.top <= -1;
}

// Function to push a disk onto a tower
// Precondition Tower is not full
void push(Tower *tower, int disk) {
    tower->disks[++(tower->top)] = disk;    // add the disk to the new top position
}

// Function to "pop" a disk from a tower
// Precondition Tower is not empty
int pop(Tower *tower) {
    return tower->disks[(tower->top)--];    // return the removed disk (tower.disks[top]; top--;)
}
