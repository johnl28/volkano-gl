#pragma once
#include <random>

namespace glcore {


	class Random
	{
	public:
		const Random& operator=(const Random&) = delete;
		Random(const Random&) = delete;

		
		static Random& Get()
		{
			static Random instance;
			return instance;
		}

		static float Float(float min, float max)
		{
			return Random::Get().Impl_Float(min, max);
		}

	private:
		Random() 
		{
			std::random_device randomDevice;
			gen = std::mt19937(randomDevice());
		}

		float Impl_Float(float min, float max)
		{

			std::uniform_real_distribution<float> dis(min, max);

			return dis(gen);
		}

		std::mt19937 gen;
	};

}
