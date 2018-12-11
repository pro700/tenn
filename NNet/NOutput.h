#pragma once

#include <cassert>
#include <vector>

class NObject;
class NInput;

/////////////////////////////////////////////////////////
class NOutput
{
	friend class NObject;
	friend class NInput;

protected:
	NObject * pObject;

	float B;

	std::vector<NInput*> linkedInputPtrs;
	NInput* activeLinkedInputPtr;

	float Ve;

public:
	NOutput(NObject* _pObject);
	~NOutput();

protected:
	void Link(NInput* pInput);
	bool IsLinked(NInput* pInput);
};

