#include "tower.h"

// Function to initialize tower
void initializeTower(Tower *tower) {
    tower->top = -1; // Initialize the tower as empty
}

// Cases
int TowerIsEmpty(Tower tower) {
    return tower.top <= -1;
}

// Function to push a disk onto a tower
void push(Tower *tower, int disk, int MAX_DISKS) {
    if (tower->top < MAX_DISKS - 1) {   // make sure top isn't on the uppermost slot
        tower->top++;                     // increment top
        tower->disks[tower->top] = disk;  // add the disk to the new top position
    }
}

// Function to "pop" a disk from a tower
int pop(Tower *tower) {
    if (tower->top >= 0) {    // ensures the tower is not empty
        int disk = tower->disks[tower->top];  // store top disk
        tower->top--;                         // decrement top position
        return disk;                          // return the removed disk (tower.disks[top]; top--;)
    }
    return -1; // return -1 if tower is empty
}
