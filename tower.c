#include "tower.h"

// Function to initialize tower
void initializeTower(Tower *tower) {
    tower->top = -1; // Initialize the tower as empty
}

// Cases
int TowerIsEmpty(int top) {
    return top <= -1;
}

// Function to push a disk onto a tower
void push(Tower *tower, int disk, int MAX_DISKS) {
    if (tower->top < MAX_DISKS - 1) {           // make sure the top isn't on the most upper slot
        tower->disks[++(tower->top)] = disk;    // tower.top++; tower.disks[tower.top] = disk;
    }
}

// Function to "pop" a disk from a tower
int pop(Tower *tower) {
    if (tower->top >= 0) {                      
        return tower->disks[(tower->top)--];    // return tower.disks[top]; top--;
    }
    return -1; // Return -1 if tower is empty
}