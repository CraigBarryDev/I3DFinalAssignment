#include "../utils.h"

#ifndef SKYBOX_H
#define SKYBOX_H

#define ONE_THIRD 1.0f/3.0f
#define TWO_THIRD 2.0f/3.0f - 0.01f

#define N_VERTICES 24
#define N_INDICES 36
#define N_TEXCOORDS 24

static float skybox_vertices[] = {
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

static float skybox_texCoords[] = {
	//Top square
	0.50f, 0.0f, 		//TOP BACK RIGHT 0
	0.50f, ONE_THIRD, 	//TOP FRONT RIGHT 1
	0.25f, ONE_THIRD,	//TOP FRONT LEFT 2
	0.25f, 0.0f,		//TOP BACK LEFT 3
	//Bottom square
	0.50f, 1.00f,		//BOTTOM BACK RIGHT 4
	0.50f, TWO_THIRD,	//BOTTOM FRONT RIGHT 5
	0.25f, TWO_THIRD,	//BOTTOM FRONT LEFT 6
	0.25f, 1.00f,		//BOTTOM BACK LEFT 7
	//Right square
	0.75f, TWO_THIRD,	//RIGHT BACK BOTTOM 8
	0.5f, TWO_THIRD,	//RIGHT FRONT BOTTOM 9
	0.5f, ONE_THIRD, 	//RIGHT FRONT TOP 10
	0.75f, ONE_THIRD, 	//RIGHT BACK TOP 11
	//Left square
	0.0f, TWO_THIRD, 	//LEFT BACK BOTTOM 12
	0.25f, TWO_THIRD, 	//LEFT FRONT BOTTOM 13
	0.25f, ONE_THIRD, 	//LEFT FRONT TOP 14
	0.0f, ONE_THIRD, 	//LEFT BACK TOP 15
	//Back square
	0.75f, ONE_THIRD, 	//BACK TOP RIGHT 16
	1.0f, ONE_THIRD,	//BACK TOP LEFT 17
	0.75f, TWO_THIRD,	//BACK BOTTOM RIGHT 18
	1.0f, TWO_THIRD,	//BACK BOTTOM LEFT 19
	//Front square
	0.5f, ONE_THIRD, 	//FRONT TOP RIGHT 20 
	0.25f, ONE_THIRD, 	//FRONT TOP LEFT 21
	0.5f, TWO_THIRD, 	//FRONT BOTTOM RIGHT 22
	0.25f, TWO_THIRD, 	//FRONT BOTTOM LEFT 23
};

static int skybox_indices[] = {
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

typedef struct {
	vectorf* vertices;
	vectorf* texCoords;
	vectori* indices;
}skybox;

skybox* generate_skybox();
void destroy_skybox(skybox* c);

#endif