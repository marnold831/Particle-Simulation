#include "TransformFeedback.h"

using namespace NCL;
using namespace CSC3223;
using namespace TFeedback;

TransformFeedback::TransformFeedback() { frameCount = 0; }
TransformFeedback::~TransformFeedback() {}

void TransformFeedback::EnableTransformFeedback(const RenderObject* object) {
	MeshGeometry* mesh = object->GetMesh();
	GLuint mode = TypeConvertion(mesh->GetPrimitiveType());
	glBeginTransformFeedback(mode);
}
void TransformFeedback::DisableTransformFeedback() {
	glEndTransformFeedback();
}
void TransformFeedback::ReadTransformFeedback(RenderObject* object) {
	MeshGeometry* mesh = object->GetMesh();

	if ((frameCount & 1) != 0) {
		BindVertexAttribute(0, object->GetBuffer()[0], 0, 3, sizeof(Vector3), 0);
	}
	else {
		BindVertexAttribute(0, object->GetBuffer()[1], 0, 3, sizeof(Vector3), 0);
	}
}
void TransformFeedback::InitTransformFeedback(GLuint* outputVBO, RenderObject* object) {
	//glGenBuffers(1, object->GetBuffer());
	if ((frameCount & 1) != 0 ){
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, object->GetBuffer()[0]);
	}
	else {
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, object->GetBuffer()[1]);
	}
	//glBufferData(GL_ARRAY_BUFFER, object->GetMesh()->GetVertexCount() * sizeof(Vector4), NULL, GL_DYNAMIC_DRAW);
}
void TransformFeedback::SetTransformFeedbackVaryings(GLuint program, GLsizei count,  const char* varyings) {
	const char* varyingss[] = { varyings };
	glTransformFeedbackVaryings(program, count,  varyingss, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(program);

	int logLength = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength) {
		char* tempData = new char[logLength];
		glGetProgramInfoLog(program, logLength, NULL, tempData);
		std::cout << "Transform Link Log:\n" << tempData << std::endl;
		delete tempData;
	}
}
void TransformFeedback::BindVertexAttribute(int attribSlot, int buffer, int bindingID, int elementCount, int elementSize, int elementOffSet) {
	glEnableVertexAttribArray(attribSlot);
	glVertexAttribFormat(attribSlot, elementCount, GL_FLOAT, false, 0);
	glVertexAttribBinding(attribSlot, bindingID);
	glBindVertexBuffer(bindingID, buffer, elementOffSet, elementSize);
}