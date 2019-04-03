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
	this->varyings = nullptr;
	this->varyingsSize = 0;
	this->isTransform = false;
}

RenderObject::RenderObject(MeshGeometry* inMesh, const char* varyings, int varyingsSize, bool isTransform, Matrix4 m)
	: mesh(inMesh), texture(nullptr), shader(nullptr), renderShader(nullptr),  varyings(varyings), varyingsSize(varyingsSize), isTransform(isTransform), transform(m)
{
	this->mesh = inMesh;
	this->texture = nullptr;
	this->shader = nullptr;
	this->renderShader = nullptr;
	this->transform = m;
	this->varyings = varyings;
	this->varyingsSize = varyingsSize;
	this->isTransform = isTransform;

	vector<Vector3> vec = mesh->GetPositionData();
	Vector3* data = vec.data();
	glGenBuffers(2, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vector<Vector3>) * mesh->GetVertexCount(), data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vector<Vector3>) * mesh->GetVertexCount(), data, GL_DYNAMIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vector<Vector3>) * mesh->GetVertexCount(), data, GL_DYNAMIC_DRAW);
	//glNamedBufferData(buffer[0], sizeof(Vector3) * mesh->GetVertexCount(), data, GL_DYNAMIC_DRAW);
	//glNamedBufferData(buffer[0], sizeof(Vector3) * mesh->GetVertexCount(), data, GL_DYNAMIC_DRAW);

	//glGenTransformFeedbacks(2, buffer);
}

RenderObject::~RenderObject()
{
}