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
	, Ve(0)
{
}

/////////////////////////////////////////////////////////
NOutput::~NOutput()
{
}

/////////////////////////////////////////////////////////
//void NOutput::Link(NInput* pInput)
//{
//	//assert(!IsLinked(pInput));
//
//	this->linkedInputPtrs.push_back(pInput);
//	pInput->linkedOutputPtrs.push_back(this);
//
//	if (activeLinkedInputPtr == NULL && pInput->activeLinkedOutputPtr == NULL)
//	{
//		activeLinkedInputPtr = pInput;
//		pInput->activeLinkedOutputPtr = this;
//	}
//}

/////////////////////////////////////////////////////////
void NOutput::Link(NInput* pInput)
{
	//assert(!IsLinked(pInput));

	this->linkedInputPtrs.push_back(pInput);
	pInput->linkedOutputPtrs.push_back(this);

	if (activeLinkedInputPtr == NULL)
	{
		activeLinkedInputPtr = pInput;
		pInput->activeLinkedOutputPtrs.push_back(this);
	}
}

/////////////////////////////////////////////////////////
void NOutput::SetVe(float Ve) 
{
	this->Ve = Ve;

	if (AvgErr <= activeLinkedInputPtr->VeAvgErr)
	{
		activeLinkedInputPtr->Ve = Ve;
		activeLinkedInputPtr->VeAvgErr = AvgErr;
	}
}

/////////////////////////////////////////////////////////
void NOutput::MakeActive(NInput* pInput)
{
	////assert(!IsLinked(pInput));
	//assert(pInput->activeLinkedOutputPtr == NULL || pInput->activeLinkedOutputPtr == this);

	//if(activeLinkedInputPtr != NULL)
	//	activeLinkedInputPtr->activeLinkedOutputPtr = NULL;

	//activeLinkedInputPtr = pInput;
	//activeLinkedInputPtr->activeLinkedOutputPtr = this;
}

/////////////////////////////////////////////////////////
bool NOutput::IsLinked(NInput* pInput)
{
	for (NInput*& InputPtr : linkedInputPtrs)
	{
		if (InputPtr == pInput)
			return true;
	}
	return false;
}

