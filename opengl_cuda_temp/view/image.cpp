#include "image.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../external_helpers/stb_image.h"

image util::load_from_file(const char* filepath) {
	image result;

	result.pixels = stbi_load(filepath, &(result.width), &(result.height), &(result.channels), STBI_rgb_alpha);

	return result;
}

void util::free_img_memory(image oldImage) {
	stbi_image_free(oldImage.pixels);
}
