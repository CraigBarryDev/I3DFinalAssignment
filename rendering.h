#include "framework/utils.h"
#include "framework/model.h"

#ifndef RENDERING_H
#define RENDERING_H

static bool renderWireframes = false;
static bool enableLighting = false;

void renderBitmapString(float x,float y, char* text);

void setColor(float red, float green, float blue);
void setLighting();

void toggleWireframeRendering();
void toggleLighting();

#endif