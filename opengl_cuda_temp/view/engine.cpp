#pragma once

#include "engine.h"

Engine::Engine(int width, int height) {

	program = util::load_shader("shaders/vertex.txt", "shaders/fragment.txt");
	glUseProgram(program);

	// texture 
	glUniform1i(glGetUniformLocation(program, "basicTexture"), 0);

	float aspectRatio = float(height) / float(width);


	// setup frame buffer 
	glClearColor(0.0f, 0.0f, 0.0f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glm::mat4 projectionTransform = glm::perspective(45.f, aspectRatio, 0.1f, 10.f);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, glm::value_ptr(projectionTransform));

	std::stringstream location;
	for (int i = 0; i < 8; i++) {
		location.str("");
		location << "lights[" << i << "].color";
		lights.colorLoc[i] = glGetUniformLocation(program, location.str().c_str());

		location.str("");
		location << "lights[" << i << "].position";
		lights.positionLoc[i] = glGetUniformLocation(program, location.str().c_str());

		location.str("");
		location << "lights[" << i << "].strength";
		lights.strengthLoc[i] = glGetUniformLocation(program, location.str().c_str());
	}

	lightFunctions.full = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "calculatePointLightFull");
	lightFunctions.rough = glGetSubroutineIndex(program, GL_FRAGMENT_SHADER, "calculatePointLightRough");

	cameraPosLoc = glGetUniformLocation(program, "cameraPosition");

	createModels();
	createMaterials();
}

void Engine::render(Scene* scene) {

	glUseProgram(program);


	glm::mat4 view_transform{ glm::lookAt(scene->player->position,
		scene->player->position + scene->player->forwards,
		scene->player->up) };
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view_transform));


	// transform



	glUniform3fv(cameraPosLoc, 1, glm::value_ptr(scene->player->position));

	int i{ 0 };
	for (Light* light : scene->lights) {
		glUniform3fv(lights.colorLoc[i], 1, glm::value_ptr(light->color));
		glUniform3fv(lights.positionLoc[i], 1, glm::value_ptr(light->position));
		glUniform1f(lights.strengthLoc[i], light->strength);
		++i;
	}


	// draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	skinTexture->use();
	glBindVertexArray(cubeModel->VAO);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE,
		glm::value_ptr(scene->cube->modelTransform)
	);

	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &lightFunctions.rough);
	glDrawArrays(GL_TRIANGLES, 0, cubeModel->vertexCount);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, GL_FALSE,
		glm::value_ptr(scene->cube2->modelTransform)
	);

	glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &lightFunctions.full);
	glDrawArrays(GL_TRIANGLES, 0, cubeModel->vertexCount);
}

void Engine::createModels() {
	MeshCreateInfo cubeInfo;
	cubeInfo.filepath = "objs/Cube.obj";  //"objs/apple.obj";
	cubeInfo.preTransform = glm::mat4(1);

	cubeModel = new ObjMesh(&cubeInfo);
}

void Engine::createMaterials() {
	MaterialCreateInfo materialInfo;
	materialInfo.filename = "C:/Users/tempdelta/Desktop/opengl_/textures/skin.jpg"; // absolute path ?
	skinTexture = new Material(&materialInfo);
}

Engine::~Engine() {
	delete skinTexture;
	delete cubeModel;
	glDeleteProgram(program);
}