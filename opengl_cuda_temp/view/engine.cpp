#pragma once

#include "engine.h"

Engine::Engine(int width, int height) {

	program = util::load_shader("shaders/vertex.txt", "shaders/fragment.txt");
	glUseProgram(program);

	// texture 
	glUniform1i(glGetUniformLocation(program, "basicTexture"), 0);

	float aspectRatio = float(height) / float(width);


	// setup frame buffer 
	glClearColor(0.5f, 0.2f, 0.3f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glm::mat4 projectionTransform = glm::perspective(45.f, aspectRatio, 0.1f, 10.f);
	glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, false, glm::value_ptr(projectionTransform));

	createModels();
	createMaterials();
}

void Engine::render(Scene* scene) {

	glm::mat4 view_transform{ glm::lookAt(scene->player->position,
		scene->player->position + scene->player->forwards,
		scene->player->up) };
	glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_FALSE, glm::value_ptr(view_transform));


	// transform
	float angle = glm::radians(static_cast<float>(10 * glfwGetTime()));
	glm::mat4 modelTransfrom = glm::mat4(1);
	modelTransfrom = glm::translate(modelTransfrom, scene->cube->position);
	modelTransfrom = modelTransfrom * glm::eulerAngleXYZ(scene->cube->eulers.x, scene->cube->eulers.y, scene->cube->eulers.z);

	glUniformMatrix4fv(glGetUniformLocation(program, "model"), 1, false, glm::value_ptr(modelTransfrom));

	// draw
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);
	skinTexture->use();
	glBindVertexArray(cubeModel->VAO);
	glDrawArrays(GL_TRIANGLES, 0, cubeModel->vertexCount);
}

void Engine::createModels() {
	MeshCreateInfo cubeInfo;
	cubeInfo.filepath = "C:/Users/mykha/Desktop/CudaLessons/opengl_cuda_temp/opengl_cuda_temp/objs/Cube obj.obj";
	cubeInfo.preTransform = glm::mat4(1);
	cubeModel = new ObjMesh(&cubeInfo);
}

void Engine::createMaterials() {
	MaterialCreateInfo materialInfo;
	materialInfo.filename = "C:/Users/mykha/Desktop/CudaLessons/opengl_cuda_temp/textures/skin.jpg";
	skinTexture = new Material(&materialInfo);
}

Engine::~Engine() {
	delete skinTexture;
	delete cubeModel;
	glDeleteProgram(program);
}