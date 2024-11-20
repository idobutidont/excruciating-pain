#ifndef tower_h
#define tower_h

typedef struct {
    int disks[16];
    int top;
} Tower;

void initializeTower(Tower *tower);

void push(Tower *tower, int disk, int MAX_DISKS);

int pop(Tower *tower);

int TowerIsEmpty (int top);

#endif