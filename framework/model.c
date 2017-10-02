#include "model.h"

model* new_model(vectorf* vertices, vectorf* normals, vectorf* texCoords) {
	model* m = (model*)malloc(sizeof(model));
	m->vertices = vertices;
	m->normals = normals;
	m->texCoords = texCoords;
	m->indices = NULL;
	m->texture = -1;
	m->showTextures = true;
	m->renderTransformations = true;
	m->pos = new_vec3(0.0f, 0.0f, 0.0f);
	m->rot = new_vec3(0.0f, 0.0f, 0.0f);
	m->scale = new_vec3(1.0f, 1.0f, 1.0f);
	return m;
}

model* new_model_wIndices(vectorf* vertices, vectorf* normals, vectorf* texCoords, vectori* indices) {
	model* m = new_model(vertices, normals, texCoords);
	m->indices = indices;
	return m;
}

void render(model* m) {
	glPushMatrix();

	if(m->renderTransformations) {
		glTranslatef(m->pos.x, m->pos.y, m->pos.z);
		glRotatef(m->rot.x, 1.0f, 0.0f, 0.0f);
		glRotatef(m->rot.y, 0.0f, 1.0f, 0.0f);
		glRotatef(m->rot.z, 0.0f, 0.0f, 1.0f);
		glScalef(m->scale.x, m->scale.y, m->scale.z);
	}

	//If the model contains a texture, render with texture
	if (m->showTextures && m->texCoords != NULL && m->texture != -1) {
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m->texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, m->texCoords->data);
	}
	//If the model contains normals, render using normals
	if (m->normals != NULL) {
		glEnableClientState(GL_NORMAL_ARRAY);
		glNormalPointer(GL_FLOAT, 0, m->normals->data);
	}
	//Sets the models vertices to the VAO
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, m->vertices->data);

	//If the model has an index buffer then use it
	if(m->indices != NULL) {
		//Draws the model with an index buffer
		glDrawElements(GL_TRIANGLES, m->indices->size, GL_UNSIGNED_INT, m->indices->data);
	}else {
		//Draws the model
		glDrawArrays(GL_TRIANGLES, 0, m->vertices->size / 3);
	}
	
	//Disable client state
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	//Unbind Texture
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();
}

void destroy_model(model* m) {
	//Clears the model's positional data from memory
	if(m->vertices) 	destroy_vectorf(m->vertices);
	if(m->normals) 		destroy_vectorf(m->normals);
	if(m->texCoords) 	destroy_vectorf(m->texCoords);
	if(m->indices) 		destroy_vectori(m->indices);
	//Clears the model from memory
	free(m);
}
