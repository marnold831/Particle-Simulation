#pragma once
#include "Renderer.h"
#include <vector>
#include <random>

namespace NCL {
	namespace CSC3223 {
		namespace Generation {
			class SnowGeneration {
			public:
				SnowGeneration();
				SnowGeneration(int numParticles, float minHeight, float maxHeight);
				~SnowGeneration();
				void generateSnow(Renderer& renderer, float width, float height);

			private:
				int numParticles;
				float minHeight;
				float maxHeight;
				typedef std::mt19937 MyRNG;

			};
		}
		
	}
}