#include "SnowGeneration.h"


using namespace NCL;
using namespace CSC3223;
using namespace Generation;

SnowGeneration::SnowGeneration() : numParticles(10), minHeight(20.0), maxHeight(100.0) {}
SnowGeneration::SnowGeneration(int numParticles, float minHeight, float maxHeight): numParticles(numParticles), minHeight(minHeight), maxHeight(maxHeight) {}
SnowGeneration::~SnowGeneration() {}

void SnowGeneration::generateSnow(Renderer& renderer, float width, float depth) {

	OGLMesh* particles = new OGLMesh();
	std::vector<Vector3> verts;
	std:vector<Vector4> colour;
	std::random_device seed;
	MyRNG rng(seed());

	std::uniform_real_distribution<float> float_distHeight(minHeight, maxHeight);
	std::uniform_real_distribution<float> float_distX(0.0, width);
	std::uniform_real_distribution<float> float_distZ(0.0, depth);
	for (int i = 0; i < numParticles; i++) {
		float x = float_distX(rng);
		float y = float_distHeight(rng);
		float z = float_distZ(rng);
	
		verts.push_back(Vector3(x, y, z));
		
	}

	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, 0));
	particles->SetVertexPositions(verts);
	particles->SetVertexColours(colour);
	
	particles->SetPrimitiveType(GeometryPrimitive::Points);
	particles->UploadToGPU();
	

	OGLShader* particlesShader = new OGLShader("PhysicsVert.glsl", "PhysicsFrag.glsl", "PhysicsGeom.glsl");
	OGLShader* transformShader = new OGLShader("TransformVert.glsl", "TransformFrag.glsl");
	
	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("snowball.PNG");
	
	RenderObject* particlesOBJ = new RenderObject(particles, true, modelMat);

	particlesOBJ->SetBaseTexture(newTex);
	particlesOBJ->SetShader(transformShader);
	particlesOBJ->setRenderShader(particlesShader);

	renderer.AddRenderObject(particlesOBJ);

	
}