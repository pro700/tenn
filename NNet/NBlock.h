#pragma once

#include <stdlib.h>
#include <new>
#include <vector>
#include <iostream>

class NField;
class NObject;
class NLayer;

class NBlock
{
protected:
	std::vector<NLayer> layers;
	int countOfLinksPerObject;

public:
	NBlock(NField* pField, int countOfLayers, int countOfObjectsInLayer, int _countOfLinksPerObject);
	~NBlock();

public:
	void Link();
	void Eval();
	void Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks);

};

