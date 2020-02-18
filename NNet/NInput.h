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

	float Ve;
	float VeAvgErr;

	std::vector<NOutput*> linkedOutputPtrs;
	std::vector<NOutput*> activeLinkedOutputPtrs;
	NOutput* activeLinkedOutputPtr;

	float Vb;
	float AvgErr;

public:
	NInput(NObject* _pObject);
	~NInput();

protected:
	void Link(NOutput* pOutput);
	bool IsLinked(NOutput* pOutput);
	float GetVeOrA();
	float GetVb() { return Vb; }
	void SetVb(float vb) { Vb = vb; }
	void DeltaVeOrA(float da);
};

