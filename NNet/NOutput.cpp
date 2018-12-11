#include <stdlib.h>
#include <new>

#include "NObject.h"
#include "NOutput.h"
#include "NInput.h"


/////////////////////////////////////////////////////////
NOutput::NOutput(NObject* _pObject)
	: pObject(_pObject)
	, B(0)
	, linkedInputPtrs(0)
	, activeLinkedInputPtr(NULL)
{
}

/////////////////////////////////////////////////////////
NOutput::~NOutput()
{
}

/////////////////////////////////////////////////////////
void NOutput::Link(NInput* pInput)
{
	//assert(!IsLinked(pInput));

	this->linkedInputPtrs.push_back(pInput);
	pInput->linkedOutputPtrs.push_back(this);

	if (activeLinkedInputPtr == NULL && pInput->activeLinkedOutputPtr == NULL)
	{
		activeLinkedInputPtr = pInput;
		pInput->activeLinkedOutputPtr = this;
	}
}

/////////////////////////////////////////////////////////
bool NOutput::IsLinked(NInput* pInput)
{
	for (int n = 0; n < linkedInputPtrs.size(); n++)
	{
		if (linkedInputPtrs[n] == pInput)
			return true;
	}
	return false;
}
