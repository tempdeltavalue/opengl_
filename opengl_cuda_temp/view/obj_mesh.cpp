#include "obj_mesh.h"
#include <algorithm>

std::vector<float> normalizeValues(const std::vector<float>& values)
{
	// Find the minimum and maximum values in the vector
	float minValue = *std::min_element(values.begin(), values.end());
	float maxValue = *std::max_element(values.begin(), values.end());

	// Calculate the range
	float range = maxValue - minValue;

	// Create a new vector to store the normalized values
	std::vector<float> normalizedValues;

	// Iterate over each element in the original vector and normalize it
	for (const float& value : values)
	{
		// Normalize the value to the range of 0 to 1
		float normalizedValue = (value - minValue) / range;
		normalizedValues.push_back(normalizedValue);
	}

	return normalizedValues;
}

ObjMesh::ObjMesh(MeshCreateInfo* createInfo) {

	std::vector<float> vertices =
		util::load_model_from_file(createInfo->filepath, createInfo->preTransform);

	// Needed for apple
	//vertices = normalizeValues(vertices);

	//for (float& number : vertices) {
	//	number *= 10;
	//}

	vertexCount = int(vertices.size()) / 8;
	glCreateBuffers(1, &VBO);
	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));
	glNamedBufferStorage(
		VBO, vertices.size() * sizeof(float), vertices.data(), GL_DYNAMIC_STORAGE_BIT);

	//pos: 0, texcoord: 1, normal: 2

	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	glEnableVertexArrayAttrib(VAO, 2);

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);
	glVertexArrayAttribBinding(VAO, 2, 0);
}

ObjMesh::~ObjMesh() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}