#include "config.h"
#include "control/app.h"

int main() {

	int width = 640;
	int height = 480;


	AppCreateInfo appInfo;
	appInfo.width = width;
	appInfo.height = height;
	App* app = new App(&appInfo);
	returnCode nextAction = returnCode::CONTINUE;


	while (nextAction == returnCode::CONTINUE) {
		nextAction = app->mainLoop();
	}

	delete app;

	return 0;
}