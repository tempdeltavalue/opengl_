#pragma once 

#include "../config.h"

namespace util {
	image load_from_file(const char* filepath);

	void free_img_memory(image oldImage);
}