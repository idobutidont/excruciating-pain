#ifndef tower_h
#define tower_h

typedef struct {
    int disks[16];
    int top;
} Tower;

void initializeTower(Tower *tower);
void initializeDisks(Tower *tower, int MAX_DISKS);

void push(Tower *tower, int disk);

int pop(Tower *tower);

int TowerIsEmpty (Tower tower);

#endif