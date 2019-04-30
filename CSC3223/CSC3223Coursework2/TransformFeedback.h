#pragma once
#include "glad\glad.h"
#include "RenderObject.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"

namespace NCL {
	namespace CSC3223 {
		namespace TFeedback {
			class TransformFeedback {
			public:
				TransformFeedback();
				~TransformFeedback();

				void EnableTransformFeedback(const RenderObject* object);
				void DisableTransformFeedback();

				void ReadTransformFeedback(RenderObject* object);
				void InitTransformFeedback(GLuint* outputVBO, RenderObject* object);
				void SetTransformFeedbackVaryings(GLuint program);

				void BindVertexAttribute(int attribSlot, int buffer, int bindingID, int elementCount, int elementSize, int elementOffset);
				void UpdateFrameCount() { 
					frameCount++; 
				}
			
				GLuint TypeConvertion(GeometryPrimitive primitive) {
					GLuint mode = 0;
					switch (primitive) {
					case GeometryPrimitive::Triangles:		mode = GL_TRIANGLES;		break;
					case GeometryPrimitive::Points:			mode = GL_POINTS;			break;
					case GeometryPrimitive::Lines:			mode = GL_LINES;			break;
					case GeometryPrimitive::TriangleFan:	mode = GL_TRIANGLE_FAN;		break;
					case GeometryPrimitive::TriangleStrip:	mode = GL_TRIANGLE_STRIP;	break;
					case GeometryPrimitive::Patches:		mode = GL_PATCHES;			break;
					}
					return mode;
				}
				int frameCount;

			};
		}
	}
	
}