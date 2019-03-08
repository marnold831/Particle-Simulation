#include "TerrainGeneration.h"

using namespace NCL;
using namespace CSC3223;
using namespace Generation;

TerrainGeneration::TerrainGeneration() {}
TerrainGeneration::~TerrainGeneration() {}


double** TerrainGeneration::generateHeights(double xScale, double zScale, int width, int depth, double xVariance, double zVariance) {

	double x = 0.0;
	double z = 0.0;

	PerlinNoise pn = PerlinNoise();
	double** heights = new double*[depth];
	for (int i = 0; i < depth; i++) {
		heights[i] = new double[width];
	}

	for (int j = 0; j < depth; j++) {
		for (int k = 0; k < width; k++) {
			heights[j][k] = pn.Noise(x * xVariance, 0, z *  zVariance);
			x += xScale;
		}
		x = 0.0;
		z += zScale;
	}
	return heights;
}
void TerrainGeneration::generatePlane(Renderer& renderer, double depth, double width, double xVariance, double zVariance) {

	double xScale = (double)(1 / width);
	double zScale = (1 / depth);

	double x = 0.0;
	double z = 0.0;

	double** heights = generateHeights(xScale, zScale, (int)width, (int)depth, xVariance, zVariance);
	for (int j = 0; j < depth-1; j++) {

		std::vector<Vector3> verts;
		std::vector<Vector4> colours;
		std::vector<Vector2> texCoords;

		for (int k = 0; k < width; k++) {

			verts.push_back(Vector3(x, heights[j][k], z));
			colours.push_back(Vector4(0.66, 0.66, 0.66, 1));

			verts.push_back(Vector3(x, heights[j+1][k], z + zScale));
			colours.push_back(Vector4(0.66, 0.66, 0.66, 1));
	
			texCoords.push_back(Vector2(0, 0));
			texCoords.push_back(Vector2(0, 1));
			texCoords.push_back(Vector2(1, 0));
			texCoords.push_back(Vector2(1, 1));

			x += xScale;
		}
		x = 0.0;
		z += zScale;
		RenderPlane(renderer, verts, colours, texCoords);
	}
}

void TerrainGeneration::RenderPlane(Renderer& renderer, vector<Vector3> verts, vector<Vector4> colours, vector<Vector2> texCoords) {

	OGLMesh* terrainMESH = new OGLMesh();
	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("terrain.PNG");

	terrainMESH->SetVertexPositions(verts);
	terrainMESH->SetVertexColours(colours);
	terrainMESH->SetVertexTextureCoords(texCoords);
	terrainMESH->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	terrainMESH->UploadToGPU();

	Matrix4 scale = Matrix4::Scale(Vector3(100, 8, 100));
	RenderObject* terrainOBJ = new RenderObject(terrainMESH, scale);
	terrainOBJ->SetBaseTexture(newTex);
	renderer.EnableBilinearFiltering(*(OGLTexture*)newTex);
	renderer.EnableMipMapFiltering(*(OGLTexture*)newTex);
	renderer.AddRenderObject(terrainOBJ);
}