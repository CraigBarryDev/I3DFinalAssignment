#ifndef UPDATE_H
#define UPDATE_H

void resetGame(int* lives, int* score, int* nCorpses);
void resetFrog();
void killFrog(int* lives, int* score, int* nCorpses);
void explosion();

void killOutOfBoundsFrog(int* lives, int* score, int* nCorpses);

void moveX(model* m, float width, float* speed, int minSpeed, int maxSpeed, int nLanes, float planeSize, float* zPos);
void moveLogs();
void moveCars();

void handleCarCollisions(int* lives, int* score, int* nCorpses);
void handleLogCollisions(int* lives, int* score, int* nCorpses);
void handleWaterCollision(int* lives, int* score, int* nCorpses);

void updateWater();
void updateParticles();

void updateFrogScore(int* score);

void handleFrogRibbit();

#endif