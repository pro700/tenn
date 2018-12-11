#include <stdlib.h>
#include <new>

#include "NField.h"

NField::NField(int _nYCount) 
	: y(_nYCount, 0)
{
}

NField::~NField()
{
}

std::vector<int> NField::GenerateRandomIndexes(size_t Size)
{
	std::vector<int> indexes(Size);

	for (int i = 0; i < indexes.size(); i++)
		indexes[i] = i;

	random_shuffle(indexes.begin(), indexes.end());

	return indexes;
}


