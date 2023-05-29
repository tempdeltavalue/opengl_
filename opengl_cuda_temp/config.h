#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector> 

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <string>
#include <sstream>

#include "view/shader.h"

struct image {
	unsigned char* pixels;
	int width, height, channels;
};