#pragma once

#include "utils.h"

static float frameTime = 0;
static int currFPS = 0;

float getTimeSec();
float getTimeMS();
float getFrameTime();

int getFPS();
void printFPS();
void updateFrameTime();


