#pragma once
#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "TransformFeedback.h"
#include "RenderObject.h"

#include "../../Common/Vector2.h"

namespace NCL {

	namespace CSC3223 {
		using namespace TFeedback;
		class Renderer : public OGLRenderer
		{
		public:
			Renderer(Window& w);
			~Renderer();

			void AddRenderObject(RenderObject* ro) {
				renderObjects.emplace_back(ro);
			}

			void DeleteAllRenderObjects() {
				for (const RenderObject* object : renderObjects) {
					delete object;
				}
				renderObjects.clear();
			}

			void SetProjectionMatrix(const Matrix4&m) {
				projMatrix = m;
			}

			void SetViewMatrix(const Matrix4&m) {
				viewMatrix = m;
			}
			/*Depth Functions*/
			void EnableDepthBuffer(bool state);


			/*Blend Functions*/
			void EnableAlphaBlending(bool state);
			void SetBlendAdditive();
			void SetBlendToLinear();
			void SetBlendToInvert();

			void EnableBilinearFiltering(OGLTexture& t);
			void EnableMipMapFiltering(OGLTexture& t);

			int SetShaderAttributes(OGLShader* activeShader);
			void SetMatrixTransform(RenderObject* object, int modelLocation);
		protected:
			
			void OnWindowResize(int w, int h)	override;
			void RenderFrame()	override;
			OGLShader*		defaultShader;
			Matrix4		projMatrix;
			Matrix4		viewMatrix;
			TransformFeedback* tFeedback = new TransformFeedback;
			vector<RenderObject*> renderObjects;
		};
	}
}

