#pragma once
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/Maths.h"
#include "PerlinNoise.h"
#include "Renderer.h"
#include <vector>

namespace NCL {
	namespace CSC3223 {
		namespace Generation {
			class TerrainGeneration {
			public:
				TerrainGeneration();
				~TerrainGeneration();
				void generatePlane(Renderer& renderer, double depth, double width, double xVariance, double zVariance);

			private:
				double* generate1DHeights(double scale, int distance, double xVariance, double zVariance);
				double** generateHeights(double xScale, double zScale, int width, int depth, double xVariance, double zVariance);
				void RenderPlane(Renderer& renderer, vector<Vector3> verts, vector<Vector4> colours, vector<Vector2> texCoords);
			};
		}
	}
}