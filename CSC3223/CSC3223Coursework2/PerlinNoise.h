#pragma once
#include <cmath>
namespace NCL {
	namespace CSC3223 {
		namespace Generation {
			class PerlinNoise {

			public:
				//std::vector<int> p;
				PerlinNoise();
				PerlinNoise(unsigned int seed);
				double Noise(double x, double y, double z);

			protected:
				double fade(double t);
				double lerp(double t, double a, double b);
				double grad(int hash, double x, double y, double z);

			};
		}
	}
}
