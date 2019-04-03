#pragma once
#include "../../Common/Matrix4.h"
#include "../../Common/TextureBase.h"
#include "../../Common/ShaderBase.h"
#include "glad\glad.h"
#include <vector>
namespace NCL {
	using namespace NCL::Rendering;
	class MeshGeometry;
	namespace CSC3223 {
		using namespace Maths;

		class RenderObject
		{
		public:
			RenderObject(MeshGeometry* mesh, Matrix4 m = Matrix4());
			RenderObject(MeshGeometry* mesh, const char* varyings, int varyingsSize, bool isTransform, Matrix4 m = Matrix4());
			~RenderObject();

			MeshGeometry*		GetMesh() const {
				return mesh;
			}

			void  SetTransform(Matrix4 mat) {
				transform = mat;
			}

			Matrix4 GetTransform() const {
				return transform;
			}

			void SetBaseTexture(TextureBase* t) {
				texture = t;
			}

			TextureBase* GetBaseTexture() const {
				return texture;
			}


			void SetShader(ShaderBase* s) {
				shader = s;
			}

			ShaderBase* GetShader() const {
				return shader;
			}
			void setRenderShader(ShaderBase* s) {
				renderShader = s;
			}
			ShaderBase* GetRenderShader() const {
				return renderShader;
			}
			GLuint* GetBuffer() {
				return buffer;
			}
			void SetVaryings(const char* varyings, int size) {
				this->varyings = varyings;
				varyingsSize = size;
			}
			const char* GetVaryings() const {
				return varyings;
			}
			int GetVaryingsSize()const {
				return varyingsSize;
			}
			void SetIsTransform(bool transform) {
				isTransform = transform;
			}
			bool GetIsTransform() {
				return isTransform;
			}
		protected:
			MeshGeometry*	mesh;
			TextureBase*	texture;
			ShaderBase*		shader;
			ShaderBase*		renderShader;
			Matrix4			transform;
			GLuint			buffer[2];
			const char*		varyings;
			int				varyingsSize;
			bool			isTransform;
		};
	}
}

