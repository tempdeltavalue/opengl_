#pragma once

#include "../config.h"
#include "../model/scene.h"
#include "../view/engine.h"

struct AppCreateInfo {
	int width, height;
};

enum class returnCode {
	CONTINUE, QUIT
};

class App {
public:
	App(AppCreateInfo* createInfo);
	returnCode mainLoop();
	~App();

private:
	GLFWwindow* makeWindow();
	returnCode processInput();
	void calculateFrameRate();

	GLFWwindow* window;
	int width, height;
	Scene* scene;
	Engine* renderer;

	double lastTime, currentTime;
	int numFrames;
	float frameTime;
};
