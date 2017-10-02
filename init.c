#include "init.h"
#include "main.h"

extern void resetFrog();

void loadTextures() {
	//Loads texture files
	terrainTexture = loadTexture("grass.png");
	logTexture = loadTexture("log.jpg");
	waterTexture = loadTexture("water.jpg");
	underwaterTexture = loadTexture("ocean_floor.jpg");
	roadTexture = loadTexture("road_texture.png");
	skyboxTexture = loadTexture("skybox.png");
	particleTexture = loadTexture("particle.png");
}

void initTerrains() {
	//Initialize terrain model
	terr = generate_terrain_from_heightmap(TERR_ATTRIBS, "heightmap.png");
	terr->texture = terrainTexture;

	//Initialize water model
	water = generate_terrain(WATER_ATTRIBS);
	water->pos = new_vec3(WATER_POS);
	water->texture = waterTexture;

	//Initialize underwater floor model
	underwaterTerr = generate_terrain(UNDERWATER_TERR_ATTRIBS);
	underwaterTerr->pos = new_vec3(UNDERWATER_TERR_POS);
	underwaterTerr->texture = underwaterTexture;

	//Initialize road model
	road = generate_terrain(ROAD_ATTRIBS);
	road->pos = new_vec3(ROAD_POS);
	road->texture = roadTexture;
}

void initProceduralObjs() {
	//Generate object coordiantes
	cylinderCoords = generate_cylinder(LOG_ATTRIBS);
	cubeCoords = generate_cube();
	frogCoords = generate_cube();
	skyboxCoords = generate_skybox();
}

void initSkybox() {
	//Create skybox model
	skyboxModel = new_model_wIndices(skyboxCoords->vertices, NULL,
		skyboxCoords->texCoords,skyboxCoords->indices);
	//Set skybox texture
	skyboxModel->texture = skyboxTexture;
	//Set skybox scale
	skyboxModel->scale = new_vec3(SKYBOX_SCALE);
}

void initLogs() {
	//Initialize log model
	logModel = new_model_wIndices(cylinderCoords->vertices, cylinderCoords->normals,
								 cylinderCoords->texCoords, cylinderCoords->indices);
	logModel->rot = new_vec3(LOG_ROTATION);
	logModel->scale = new_vec3(LOG_HEIGHT, LOG_LENGTH, LOG_WIDTH);
	logModel->texture = logTexture;
	//Initialize log positions
	for(int i = 0; i < N_LOGS; i++) {
		float randXPos = randBetweenf(0, TERR_SIZE_X) - TERR_SIZE_X / 2.0f;
		logPositions[i] = new_vec3(randXPos, -0.25f, -4.9f + (float)i * 0.5f);
		logSpeeds[i] = randBetweenf(MIN_LOG_SPEED, MAX_LOG_SPEED);
	}
}

void initCarColors() {
	int i = 0;
	carColors[i++] = new_vec4(BRAKELIGHT_COLOR); //BLightR
	carColors[i++] = new_vec4(RIM_COLOR); //TireRL1
	carColors[i++] = new_vec4(EXHAUST_COLOR); //Exhaust
	carColors[i++] = new_vec4(BUMPER_COLOR); //MirrorR
	carColors[i++] = new_vec4(PERSON_COLOR); //Driver_Sport
	carColors[i++] = new_vec4(CAR_COLOR); //Body
	carColors[i++] = new_vec4(TIRE_COLOR); //TireRL
	carColors[i++] = new_vec4(WINDOW_COLOR); //WindF
	carColors[i++] = new_vec4(BUMPER_COLOR); //BumperF
	carColors[i++] = new_vec4(SEAT_COLOR); //SeatR
	carColors[i++] = new_vec4(RIM_COLOR); //TireFR1
	carColors[i++] = new_vec4(WINDOW_COLOR); //WindFL
	carColors[i++] = new_vec4(ROTOR_COLOR); //RotorRR
	carColors[i++] = new_vec4(WINDOW_COLOR); //WindRR
	carColors[i++] = new_vec4(0.0f, 0.0f, 0.0f, 0.0f); //Base
	carColors[i++] = new_vec4(FENDER_COLOR); //FenderR
	carColors[i++] = new_vec4(HEADLIGHT_COLOR); //HLightLG
	carColors[i++] = new_vec4(SEAT_COLOR); //SeatL
	carColors[i++] = new_vec4(TRUNK_COLOR); //Trunk
	carColors[i++] = new_vec4(DOOR_COLOR); //DoorR
	carColors[i++] = new_vec4(DOOR_COLOR); //DoorL
	carColors[i++] = new_vec4(WINDOW_COLOR); //WindFR
	carColors[i++] = new_vec4(BRAKE_COLOR); //BrakeRR
	carColors[i++] = new_vec4(SKIRT_COLOR); //SkirtL
	carColors[i++] = new_vec4(WINDOW_COLOR); //WindR
	carColors[i++] = new_vec4(ROTOR_COLOR); //RotorFL
	carColors[i++] = new_vec4(TIRE_COLOR); //TireRR
	carColors[i++] = new_vec4(BUMPER_COLOR); //BumperR
	carColors[i++] = new_vec4(HOOD_COLOR); //Hood_Carbon
	carColors[i++] = new_vec4(HOOD_COLOR); //Hood
	carColors[i++] = new_vec4(SKIRT_COLOR); //SkirtR
	carColors[i++] = new_vec4(WINDOW_COLOR); //WindRL
	carColors[i++] = new_vec4(RIM_COLOR); //TireFL1
	carColors[i++] = new_vec4(ROTOR_COLOR); //RotorRL
	carColors[i++] = new_vec4(FENDER_COLOR); //FenderL
	carColors[i++] = new_vec4(ROLLCAGE_COLOR); //Rollcag1
	carColors[i++] = new_vec4(SEAT_COLOR); //Seat_Sport
	carColors[i++] = new_vec4(BRAKE_COLOR); //BrakeFR
	carColors[i++] = new_vec4(BRAKE_COLOR); //BrakeRL
	carColors[i++] = new_vec4(BRAKE_COLOR); //BrakeFL
	carColors[i++] = new_vec4(BRAKELIGHT_COLOR); //BlightLG
	carColors[i++] = new_vec4(BRAKELIGHT_COLOR); //BlightL
	carColors[i++] = new_vec4(ROTOR_COLOR); //RotorFR
	carColors[i++] = new_vec4(LICENSE_PL_COLOR); //LicenseR
	carColors[i++] = new_vec4(LICENSE_PL_COLOR); //LicenseF
	carColors[i++] = new_vec4(HEADLIGHT_COLOR); //HLightL
	carColors[i++] = new_vec4(SPOILER_COLOR); //Spoiler
	carColors[i++] = new_vec4(ROLLCAGE_COLOR); //Rollcag2
	carColors[i++] = new_vec4(BUMPER_COLOR); //MirrorL
	carColors[i++] = new_vec4(0.2f, 0.2f, 0.2f, 1.0f); //Engine
	carColors[i++] = new_vec4(BRAKELIGHT_COLOR); //BlightRG
	carColors[i++] = new_vec4(RIM_COLOR); //TireRR1
	carColors[i++] = new_vec4(HEADLIGHT_COLOR); //HLightR
	carColors[i++] = new_vec4(TIRE_COLOR); //TireFL
	carColors[i++] = new_vec4(TIRE_COLOR); //TireFR
	carColors[i++] = new_vec4(HEADLIGHT_COLOR); //HLightRG
}

void initCars() {
	//Initialize car models
	carModels = loadOBJs("nissan-gtr.obj", &nCarModels);

	//Initialize car instace rot/scales
	for(int i = 0; i < nCarModels; i++) {
		carModels[i]->rot = new_vec3(0.0f, 90.0f, 0.0f);
		carModels[i]->scale = new_vec3(CAR_SCALE, CAR_SCALE, CAR_SCALE);
	}

	//Initialize car positions
	for(int i = 0; i < N_CARS; i++) {
		float randXPos = randBetweenf(0, TERR_SIZE_X) - TERR_SIZE_X / 2.0f;
		carPositions[i] = new_vec3(randXPos, 0.2f, 0.9f + (float)i * 0.455f);
		carSpeeds[i] = randBetweenf(MIN_CAR_SPEED, MAX_CAR_SPEED);
	}

	//Initialize car collider
	carCollider = getOBJCollider("nissan-gtr.obj", CAR_SCALE);
	//Swap X and Y as car is rotated 90 degrees
	swapf(&carCollider.size.x, &carCollider.size.z);
	swapf(&carCollider.pos.x, &carCollider.pos.z);

	//Initialize car colors
	carColors = (vec4*)malloc(sizeof(vec4) * nCarModels);
	initCarColors();
}

void initFrog() {
	//Set initial frog values
	for(int i = 2; i < frogCoords->vertices->size; i += 3) {
		frogCoords->vertices->data[i] -= 0.5f;
	}
	frogModel = new_model_wIndices(frogCoords->vertices, frogCoords->normals, NULL, frogCoords->indices);
	frogModel->renderTransformations = false;
	frogModel->scale = new_vec3(FROG_SCALE);
	frogInst = create_frog(frogModel);
	frogInst->nProjCurveVertices = FROG_PROJ_VERTICES;
	//Set frog to initial position/orientations
	resetFrog();
}

void initParticles() {
	//Iterate through the list of particles
	for(int i = 0; i < N_PARTICLES; i++) {
		//Initialize particles
		particles[i] = create_tex_particle(particleTexture, new_vec3(0.0f, 0.0f, 0.0f), 
			new_vec3(0.0f, 0.0f, 0.0f),	new_vec3(1.0f, 1.0f, 1.0f), new_vec3(0.1f, 0.1f, 0.1f), 
			0.0f, 0.0f, 1.0f, 0.0f);

	}
}

void initCorpses() {
	//Initialize all corpse objects to null
	for(int i = 0; i < N_CORPSES; i++) {
		corpses[i] = create_frog_corpse(NULL);
	}
}
