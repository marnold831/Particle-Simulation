#include "RenderObject.h"
#include "../../Common/MeshGeometry.h"

using namespace NCL;
using namespace CSC3223;

RenderObject::RenderObject(MeshGeometry* mesh, Matrix4 m) 
	: mesh(mesh), texture(nullptr), shader(nullptr), varyings(nullptr), varyingsSize(0), isTransform(false),transform(m) {}

RenderObject::RenderObject(MeshGeometry* inMesh, const char* varyings, int varyingsSize, bool isTransform, Matrix4 m)
	: mesh(inMesh), texture(nullptr), shader(nullptr), varyings(varyings), varyingsSize(varyingsSize), isTransform(isTransform), transform(m)
{
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * 1000, nullptr, GL_DYNAMIC_DRAW);

	//glGenTransformFeedbacks(2, buffer);
}

RenderObject::~RenderObject()
{
}