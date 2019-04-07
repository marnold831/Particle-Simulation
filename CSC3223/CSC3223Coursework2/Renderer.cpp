#include "Renderer.h"

#include "../../Common/TextureWriter.h"
#include "../../Common/Maths.h"
#include "../../Common/Matrix3.h"
using namespace NCL;
using namespace Rendering;
using namespace CSC3223;
using namespace TFeedback;


Renderer::Renderer(Window& w) : OGLRenderer(w)
{
	defaultShader = new OGLShader("rasterisationVert.glsl", "rasterisationFrag.glsl");
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

Renderer::~Renderer()
{
	delete defaultShader;
}

int Renderer::SetShaderAttributes(OGLShader* activeShader) {

	int projLocation = glGetUniformLocation(activeShader->GetProgramID(), "projMatrix");
	int viewLocation = glGetUniformLocation(activeShader->GetProgramID(), "viewMatrix");
	int modelLocation = glGetUniformLocation(activeShader->GetProgramID(), "modelMatrix");

	glUniformMatrix4fv(projLocation, 1, false, (float*)&projMatrix);
	glUniformMatrix4fv(viewLocation, 1, false, (float*)&viewMatrix);

	return modelLocation;

}
void Renderer::SetMatrixTransform(RenderObject* object, int modelLocation) {
	Matrix4 mat = object->GetTransform();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glUniformMatrix4fv(modelLocation, 1, false, (float*)&mat);

	BindTextureToShader(object->GetBaseTexture(), "mainTex", 0);
}

void Renderer::RenderFrame() {
	OGLShader* activeShader = nullptr;
	

	int modelLocation = 0;

	for (RenderObject* object : renderObjects) {
		OGLShader* objectShader = (OGLShader*)object->GetShader();
		OGLShader* objectShader2 = (OGLShader*)object->GetRenderShader();
		if (!object->GetMesh()) {
			continue;
		}
		if (objectShader == nullptr) {
			objectShader = defaultShader;
		}
		if (object->GetIsTransform()) {
			if (objectShader != activeShader) {//if not null
				static int frame_count = 0;

				activeShader = objectShader;
				tFeedback->SetTransformFeedbackVaryings(activeShader->GetProgramID(), object->GetVaryingsSize(), object->GetVaryings());
				BindShader(activeShader); //sets glUseProgram to that of the shader id
				glEnable(GL_RASTERIZER_DISCARD);
				modelLocation = SetShaderAttributes(activeShader);
				SetMatrixTransform(object, modelLocation);
				
				BindMesh(object->GetMesh());
				tFeedback->InitTransformFeedback(object->GetBuffer(), object);
				tFeedback->EnableTransformFeedback(object);
				DrawBoundMesh();
				tFeedback->DisableTransformFeedback();
				glDisable(GL_RASTERIZER_DISCARD);
				
				BindMesh(object->GetMesh());
				activeShader = objectShader2;
				BindShader(activeShader);
				
				modelLocation = SetShaderAttributes(activeShader);
				SetMatrixTransform(object, modelLocation);
				BindMesh(object->GetMesh());
				
				tFeedback->ReadTransformFeedback(object);
				tFeedback->EnableTransformFeedback(object);
				DrawBoundMesh();
				tFeedback->DisableTransformFeedback();
				
				tFeedback->UpdateFrameCount();
			}
		}
		else {
			if (objectShader != activeShader) {//if not null
				activeShader = objectShader;
				BindShader(activeShader); //sets glUseProgram to that of the shader id
				modelLocation = SetShaderAttributes(activeShader);
			}
			SetMatrixTransform(object, modelLocation);
			BindMesh(object->GetMesh());
			DrawBoundMesh(); //call glDrawElements if the indexCount > 0 else calls glDrawArrays
		}
	}
}
/*Set Depth Buffer on/off */
void Renderer::EnableDepthBuffer(bool state) {
	if (state)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}


/*Alpha toggle on/off plus setting type of alpha blending*/
void Renderer::EnableAlphaBlending(bool state) {
	if (state)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);
}

void Renderer::SetBlendAdditive() {
	glBlendFunc(GL_ONE, GL_ONE);
}

void Renderer::SetBlendToLinear() {
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::SetBlendToInvert() {
	glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
}

void Renderer::OnWindowResize(int w, int h) {
	OGLRenderer::OnWindowResize(w, h);
	projMatrix = Matrix4::Orthographic(-1.0f, 1.0f, (float)currentWidth, 0.0f, 0.0f, (float)currentHeight);
}

void Renderer::EnableBilinearFiltering(OGLTexture& t) {
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::EnableMipMapFiltering(OGLTexture& t) {
	GLuint id = t.GetObjectID();
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
}