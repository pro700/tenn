#pragma once

#include <stdlib.h>
#include <new>
#include <vector>
#include <iostream>

class NField;
class NObject;

/////////////////////////////////////////////////////////
class NLayer
{
protected:
	std::vector<NObject> objects;

public:
	NLayer(NField* pField, int countOfObjects);
	~NLayer();

public:
	void Link(std::vector<NLayer>& dstLayers, int beg, int end, int countOfLinksPerObject);
	void Eval();

	void Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks);
};

