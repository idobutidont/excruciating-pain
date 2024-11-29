/***************************************************************
* FILENAME: tower.c
* DESCRIPTION: 
* AUTHOR: 
* DATE: 
****************************************************************/

#include "tower.h"

// Function to initialize tower
void initializeTower(Tower *tower) {
    tower->top = -1; // Initialize the tower as empty
}

// Cases
int TowerIsEmpty(Tower tower) {
    return tower.top <= -1;
}

int TowerIsFull(Tower tower, int MAX_DISKS) {
    return tower.top >= MAX_DISKS - 1;
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
