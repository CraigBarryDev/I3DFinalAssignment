#include "texture.h"

texture loadTexture(const char* filename) {
	//Create texture from image
	texture tex = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
	//Bind texture
	glBindTexture(GL_TEXTURE_2D, tex);
	//Allows textures to tesselate (re-use textures multiple times across a single model)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	//Return the texture
	return tex;
}