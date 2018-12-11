#pragma once

#include <cassert>
#include <vector>

class NObject;
class NOutput;

/////////////////////////////////////////////////////////
class NInput
{
	friend class NObject;
	friend class NOutput;

protected:
	NObject* pObject;

	float A;

	std::vector<NOutput*> linkedOutputPtrs;
	NOutput* activeLinkedOutputPtr;

public:
	NInput(NObject* _pObject);
	~NInput();

protected:
	void Link(NOutput* pOutput);
	bool IsLinked(NOutput* pOutput);

};

