#include "obj_mesh.h"

ObjMesh::ObjMesh(MeshCreateInfo* createInfo) {

	//float l = createInfo->size.x / 2;
	//float w = createInfo->size.y / 2;
	//float h = createInfo->size.z / 2;

	//Make Cube
	//x,y,z,s,t
	std::vector<float> vertices = util::load_model_from_file(createInfo->filepath, createInfo->preTransform);


	vertexCount = int(vertices.size()) / 5;
	glCreateBuffers(1, &VBO);
	glCreateVertexArrays(1, &VAO);
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 8 * sizeof(float));

	glNamedBufferStorage(VBO, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	// pos:0, textcoord:1, normal: 2
	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	glEnableVertexArrayAttrib(VAO, 2);

	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribFormat(VAO, 1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribFormat(VAO, 2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));

	glVertexArrayAttribBinding(VAO, 0, 0);
	glVertexArrayAttribBinding(VAO, 1, 0);
}

ObjMesh::~ObjMesh() {
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}