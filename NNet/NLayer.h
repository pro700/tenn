#pragma once

#include <stdlib.h>
#include <new>
#include <vector>
#include <iostream>
#include <random>

class NField;
class NInput;
class NOutput;
class NObject;
class NBlock;

/////////////////////////////////////////////////////////
class NLayer
{
protected:
	NBlock* pBlock;
	std::vector<NObject> objects;

public:
	NLayer(NField* pField, NBlock* _pBlock, int countOfObjects);
	~NLayer();

public:
	void Link(std::vector<NLayer>& dstLayers, int beg, int end, int countOfLinksPerObject);
	void LinkR(std::reverse_iterator<std::vector<NLayer>::iterator> rbeg, std::reverse_iterator<std::vector<NLayer>::iterator> rend, int countOfLinksPerObject);
	void Link(std::vector<NInput>& inputs);
	void Link2(std::vector<NLayer>& dstLayers, int iDstLyrBeg, int iDstLyrEnd);
	void Eval();
	void GetVe(std::vector<float>& Ve);
	void SetVb(std::vector<float>& Vb);
	void Back();

	void Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks);
};

