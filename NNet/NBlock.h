#pragma once

#include <stdlib.h>
#include <new>
#include <vector>
#include <iostream>
#include <random>

class NField;
class NInput;
class NObject;
class NLayer;

class NBlock
{
protected:
	std::vector<NLayer> layers;
	std::vector<NInput> terminalInputs;
	int countOfLinksPerObject;
	float p;

	std::vector<int> randomObjectsIndexes;
	std::vector<int> randomA;
	std::vector<int> randomB;
	std::vector<int> countOfLinksPerObjectPerLayer;

public:
	NBlock(NField* pField, int countOfLayers, int countOfObjectsInLayer, int _countOfLinksPerObject, float p);
	~NBlock();

	std::minstd_rand linear_rand;

public:
	std::vector<int>& GetRandomObjectsIndexes(int countOfObjects);
	int GetCountOfLinksPerObjectPerLayerDistance(int iLayer) { return countOfLinksPerObjectPerLayer[iLayer];  }
	void Link();
	void LinkR();
	void Link2();
	void Eval();
	void GetVe(std::vector<float>& Ve);
	void SetVb(std::vector<float>& Vb);
	void Back();
	void Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks);

};

