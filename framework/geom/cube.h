#include "../utils.h"

#ifndef CUBE_H
#define CUBE_H

#define N_VERTICES 24
#define N_INDICES 36
#define N_NORMALS 24

static float cube_vertices[] = {
	//Top square
	0.5f, 0.5f, 0.5f,	//TOP BACK RIGHT 0
	0.5f, 0.5f, -0.5f,	//TOP FRONT RIGHT 1
	-0.5f, 0.5f, -0.5f,	//TOP FRONT LEFT 2
	-0.5f, 0.5f, 0.5f,	//TOP BACK LEFT 3
	//Bottom square
	0.5f, -0.5f, 0.5f,	//BOTTOM BACK RIGHT 4
	0.5f, -0.5f, -0.5f,	//BOTTOM FRONT RIGHT 5
	-0.5f, -0.5f, -0.5f,//BOTTOM FRONT LEFT 6
	-0.5f, -0.5f, 0.5f,	//BOTTOM BACK LEFT 7
	//Right square
	0.5f, -0.5f, 0.5f,	//RIGHT BACK BOTTOM 8
	0.5f, -0.5f, -0.5f, //RIGHT FRONT BOTTOM 9
	0.5f, 0.5f, -0.5f,	//RIGHT FRONT TOP 10
	0.5f, 0.5f, 0.5f,	//RIGHT BACK TOP 11
	
	//Left square
	-0.5f, -0.5f, 0.5f,	//LEFT BACK BOTTOM 12
	-0.5f, -0.5f, -0.5f,//LEFT FRONT BOTTOM 13
	-0.5f, 0.5f, -0.5f,	//LEFT FRONT TOP 14
	-0.5f, 0.5f, 0.5f,	//LEFT BACK TOP 15
	//Back square
	0.5f, 0.5f, 0.5f,	//BACK TOP RIGHT 16
	-0.5f, 0.5f, 0.5f,	//BACK TOP LEFT 17
	0.5f, -0.5f, 0.5f,	//BACK BOTTOM RIGHT 18
	-0.5f, -0.5f, 0.5f,	//BACK BOTTOM LEFT 19
	//Front square
	0.5f, 0.5f, -0.5f,	//FRONT TOP RIGHT 20 
	-0.5f, 0.5f, -0.5f,	//FRONT TOP LEFT 21
	0.5f, -0.5f, -0.5f, //FRONT BOTTOM RIGHT 22
	-0.5f, -0.5f, -0.5f	//FRONT BOTTOM LEFT 23
};

static int cube_indices[] = {
	//TOP
	0,1,2,
	0,2,3,
	//BOTTOM
	6,5,4,
	7,6,4,
	//RIGHT
	8,9,10,
	11,8,10,
	//LEFT
	14,13,12,
	14,12,15,
	//BACK
	16,17,19,
	16,19,18,
	//FRONT
	23,21,20,
	22,23,20
};

static float cube_normals[] = {
	//Top square
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	//Bottom square
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	0.0f, -1.0f, 0.0f,
	//Right square
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,
	//Left square
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	-1.0f, 0.0f, 0.0f,
	//Back square
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f,
	//Front square
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
	0.0f, 0.0f, -1.0f,
};

typedef struct {
	vectorf* vertices;
	vectorf* normals;
	vectori* indices;
}cube;

cube* generate_cube();
void destroy_cube(cube* c);

#endif
