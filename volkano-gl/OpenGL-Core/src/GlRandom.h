#pragma once
#include <random>

namespace glcore {


	class Random
	{
	public:
		static float Float(float min, float max)
		{
			static std::random_device rd;  // Seed with a real random value, if available
			static std::mt19937 gen(rd()); // Static to maintain state across calls
			std::uniform_real_distribution<> dis(min, max);

			return dis(gen);
		}
	};

}
