#include "framework/model.h"
#include "framework/terrain.h"
#include "framework/texture.h"
#include "framework/geom/sphere.h"
#include "framework/geom/cylinder.h"
#include "framework/geom/cube.h"
#include "framework/geom/projectileCurve.h"
#include "framework/geom/skybox.h"
#include "framework/keys.h"
#include "framework/mouse.h"
#include "framework/particles.h"
#include "framework/objLoader.h"

#include "display.h"
#include "frog.h"
#include "input.h"
#include "init.h"
#include "rendering.h"
#include "update.h"

#ifndef MAIN_H
#define MAIN_H

//Textures
texture terrainTexture;
texture logTexture;
texture waterTexture;
texture underwaterTexture;
texture roadTexture;
texture skyboxTexture;
texture particleTexture;

//Procedurally Generated Objs
skybox* skyboxCoords;
cylinder* cylinderCoords;
cube* cubeCoords;
cube* frogCoords;

//Terrains
terrain* terr;
terrain* water;
terrain* underwaterTerr;
terrain* road;

//Models
model* frogModel;
model* logModel;
model* skyboxModel;

//Car models
model** carModels;
vec4* carColors;
AABB carCollider;
int nCarModels;

//Frog instance
frog* frogInst;

//Positions
vec3 logPositions[N_LOGS];
vec3 carPositions[N_CARS];
//Speeds
float logSpeeds[N_LOGS];
float carSpeeds[N_CARS];

//Explosion particles
texturedParticle particles[N_PARTICLES];

//Frog corpses
frogCorpse corpses[N_CORPSES];

#endif