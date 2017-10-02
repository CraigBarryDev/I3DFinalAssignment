#ifndef INIT_H
#define INIT_H

//Uncomment to disable game resetting (for debugging/testing)
//#define GAME_RESET

//Number of logs and cars
#define N_LOGS 9
#define N_CARS 8

//Starting viewing angle on the frog (X axis)
#define STARTING_CAMERA_ANGLE -25.0f, 0.0f

//Starting game stats
#define INITIAL_LIVES 5
#define INITIAL_SCORE 0

//Skybox attributes
#define SKYBOX_COLOR 1.0f, 1.0f, 1.0f
#define SKYBOX_SCALE 50.0f, -50.0f, 50.0f

//Log attributes
#define MIN_LOG_SPEED 1.0f
#define MAX_LOG_SPEED 1.5f
#define LOG_LENGTH 2.0f
#define LOG_WIDTH 0.5f
#define LOG_HEIGHT 0.5f
#define LOG_VERTICES 30
#define LOG_RADIUS 0.5f
#define LOG_ROTATION 0.0f, 0.0f, 90.0f
#define LOG_ATTRIBS LOG_VERTICES, LOG_VERTICES, LOG_RADIUS
#define LOG_COLOR 0.25f, 0.125f, 0.075f

//Car attributes
#define MIN_CAR_SPEED 1.0f
#define MAX_CAR_SPEED 3.7f
#define CAR_SCALE 0.3f
#define CAR_COLOR 0.6f, 0.0f, 0.0f, 1.0f
#define TIRE_COLOR 0.09f, 0.09f, 0.09f, 1.0f
#define RIM_COLOR TIRE_COLOR
#define WINDOW_COLOR 0.07f, 0.07f, 0.07f, 0.9f
#define BUMPER_COLOR 0.35f, 0.0f, 0.0f, 1.0f
#define ROTOR_COLOR 0.0f, 0.0f, 0.0f, 1.0f
#define FENDER_COLOR BUMPER_COLOR
#define HEADLIGHT_COLOR 0.2f, 0.2f, 0.2f, 0.3f
#define TRUNK_COLOR BUMPER_COLOR
#define DOOR_COLOR BUMPER_COLOR
#define BRAKE_COLOR 0.0f, 0.0f, 0.8f, 1.0f
#define SKIRT_COLOR 0.5f, 0.0f, 0.0f, 1.0f
#define HOOD_COLOR 0.05f, 0.05f, 0.05f, 1.0f
#define BRAKELIGHT_COLOR 0.95f, 0.5f, 0.0f, 1.0f
#define LICENSE_PL_COLOR 0.0f, 0.0f, 0.0f, 1.0f
#define SPOILER_COLOR 0.05f, 0.05f, 0.05f, 1.0f
#define EXHAUST_COLOR 0.4f, 0.4f, 0.4f, 1.0f
#define SEAT_COLOR 0.0f, 0.0f, 0.0f, 1.0f
#define ROLLCAGE_COLOR 0.3f, 0.3f, 0.3f, 1.0f
#define PERSON_COLOR 0.7f, 0.0f, 0.0f, 1.0f

//Size of terrain
#define TERR_SIZE_X 20.0f
#define TERR_SIZE_Z 15.0f
#define TERR_VERTICES 30
#define TERR_MAX_HEIGHT 1.0f
#define TERR_MIN_HEIGHT -1.0f
#define TERR_ATTRIBS TERR_SIZE_X, TERR_SIZE_Z, TERR_VERTICES, TERR_VERTICES, TERR_MIN_HEIGHT, TERR_MAX_HEIGHT
#define TERR_COLOR 0.0f, 0.4f, 0.0f

//Water attributes
#define WATER_SIZE_X TERR_SIZE_X
#define WATER_SIZE_Z 6.0f
#define WATER_VERT 40
#define WATER_ATTRIBS WATER_SIZE_X, WATER_SIZE_Z, WATER_VERT, WATER_VERT
#define WATER_POS 0.0f, -0.25f, -2.55f
#define WATER_COLOR 0.5f, 0.5f, 0.5f, 0.5f

//Road attributes
#define ROAD_SIZE_X TERR_SIZE_X
#define ROAD_SIZE_Z 4.0f
#define ROAD_NSQUARES_X 2
#define ROAD_NSQUARES_Z 2
#define ROAD_ATTRIBS ROAD_SIZE_X, ROAD_SIZE_Z, ROAD_NSQUARES_X, ROAD_NSQUARES_Z
#define ROAD_COLOR 1.0f, 1.0f, 1.0f
#define ROAD_POS 0.0f, 0.02f, 2.55f

//Underwater terrain attributes
#define UNDERWATER_TERR_SIZE_X TERR_SIZE_X
#define UNDERWATER_TERR_SIZE_Z 5.0f
#define UNDERWATER_TERR_VERT 40
#define UNDERWATER_TERR_ATTRIBS UNDERWATER_TERR_SIZE_X, UNDERWATER_TERR_SIZE_Z, UNDERWATER_TERR_VERT, UNDERWATER_TERR_VERT
#define UNDERWATER_TERR_POS 0.0f, -0.90f, -3.25f
#define UNDERWATER_TERR_COLOR 1.0f, 1.0f, 0.0f

//Frog attributes
#define FROG_STARTING_POS 0.0f, 0.0f, 4.8f
#define FROG_STARTING_ROT 0.0f, 90.0f, 0.0f
#define FROG_SCALE 0.1f, 0.1f, 0.1f
#define FROG_INITIAL_JUMP_SPEED 3.5f
#define FROG_PROJ_VERTICES 15
//Max velocity of the frog's jump
#define FROG_MAX_JUMP_SPEED 5.0f
//How fast moving actions occur
#define FROG_ROT_SPEED 35.0f
#define FROG_ROT_ANGLE_SPEED 150.0f
#define FROG_ANGLE_SPEED 3.0f

//The y position which the frog will automatically die
#define KILLZONE_Y -10.0f

//Color of HUD text
#define HUD_COLOR 0.0f, 1.0f, 0.0f

//Particle attributes
#define N_PARTICLES 100
#define PARTICLE_SCALE_START 0.4f, 0.4f, 0.4f
#define PARTICLE_SCALE_END 0.1f, 0.1f, 0.1f

//Corpse attributes
#define N_CORPSES INITIAL_LIVES

void loadTextures();
void initTerrains();
void initProceduralObjs();
void initSkybox();
void initLogs();
void initCars();
void initFrog();
void initParticles();
void initCorpses();

#endif