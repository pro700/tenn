#pragma once

#include <cassert>
#include <vector>

#include "NInput.h"
#include "NOutput.h"

class NField;

/////////////////////////////////////////////////////////
class NObject
{
protected:
	NField* pField;
	std::vector<NInput> inputs;
	NOutput output;

public:
	NObject(NField* _pFields);
	~NObject();

protected:
	NInput* GetMostFreeInput();
	NInput* GetRandomInput();

public:
	void Link(NObject& dstObject);
	void Eval();

	void Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks);

	int GetCountOfLinks() { return output.linkedInputPtrs.size(); }

};

