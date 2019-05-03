/*	Author: Michael John Arnold
	Description: This class is responsible for the handling of transform feedback. This class contains the relevant methods
	for transform feedback setup and for during rendering. 
*/

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
		BindVertexAttribute(0, object->GetBuffer()[1], 0, 3, sizeof(Vector3), 0);
		
	}
	else {
		BindVertexAttribute(0, object->GetBuffer()[0], 0, 3, sizeof(Vector3), 0);
	
	}
}
void TransformFeedback::InitTransformFeedback(GLuint* outputVBO, RenderObject* object) {
	
	if ((frameCount & 1) != 0 ){
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, object->GetBuffer()[0]);
	
		
		BindVertexAttribute(0, object->GetBuffer()[1], 0, 3, sizeof(Vector3), 0);
	
	}
	else {
		glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, object->GetBuffer()[1]);
	
	
		BindVertexAttribute(0, object->GetBuffer()[0], 0, 3, sizeof(Vector3), 0);
		
	}
	
}
void TransformFeedback::SetTransformFeedbackVaryings(GLuint program) {

	 const GLchar * varyingss[] =
	{
		"transformPos"
	};

	glTransformFeedbackVaryings(program, 1,  varyingss, GL_INTERLEAVED_ATTRIBS);
	glLinkProgram(program);

	int logLength = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

	if (logLength) {
		char* tempData = new char[logLength];
		glGetProgramInfoLog(program, logLength, NULL, tempData);
		std::cout << "---- Error -----" << std::endl;
		std::cout << "Current Program: " << program << std::endl;
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