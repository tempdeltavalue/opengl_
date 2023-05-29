#pragma once

#include "../config.h"
#include "obj_loader.h"

namespace util {
	std::vector<float> load_model_from_file(const char* filepath, glm::mat4 preTransform);
}