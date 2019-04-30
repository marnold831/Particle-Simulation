#include "RenderObject.h"
#include "../../Common/MeshGeometry.h"

using namespace NCL;
using namespace CSC3223;

RenderObject::RenderObject(MeshGeometry* mesh, Matrix4 m) {
	this->mesh = mesh;
	this->texture = nullptr;
	this->shader = nullptr;
	this->renderShader = nullptr;
	this->transform = m;
	this->isTransform = false;
}

RenderObject::RenderObject(MeshGeometry* inMesh, bool isTransform, Matrix4 m)
	: mesh(inMesh), texture(nullptr), shader(nullptr), renderShader(nullptr), isTransform(isTransform), transform(m)
{
	this->mesh = inMesh;
	this->texture = nullptr;
	this->shader = nullptr;
	this->renderShader = nullptr;
	this->transform = m;
	this->isTransform = isTransform;

	vector<Vector3> vec = mesh->GetPositionData();
	vector<Vector3> vec2 = mesh->GetNormalData();
	Vector3* data = vec.data();
	Vector3* data2 = vec2.data();
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec) * mesh->GetVertexCount(), data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec) * mesh->GetVertexCount(), data, GL_DYNAMIC_DRAW);

	
}

RenderObject::~RenderObject()
{
}