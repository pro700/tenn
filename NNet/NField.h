#pragma once

#include <cassert>
#include <vector>
#include <algorithm>    // std::shuffle
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock


class NField
{
	friend class NObject;

protected:
	std::vector<float> y;

public:
	NField(int _nYCount);
	~NField();

public:
	float& operator[](int index)
	{
		return y[index];
	}

public:
	static std::vector<int> GenerateRandomIndexes(size_t Size);
};

