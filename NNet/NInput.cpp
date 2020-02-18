#include <cstdlib>
#include <new>
#include <limits>

#include "NInput.h"
#include "NOutput.h"
#include "NObject.h"



/////////////////////////////////////////////////////////
NInput::NInput(NObject* _pObject)
	: pObject(_pObject)
	, A(0)
	, Ve(NAN)
	, VeAvgErr(FLT_MAX)
	, linkedOutputPtrs(0)
	, activeLinkedOutputPtrs(0)
	, activeLinkedOutputPtr(NULL)
	, Vb(0)
	, AvgErr(0)
{
}

/////////////////////////////////////////////////////////
NInput::~NInput()
{
}

/////////////////////////////////////////////////////////
inline void NInput::Link(NOutput* pOutput)
{
	pOutput->Link(this);
}

/////////////////////////////////////////////////////////
inline bool NInput::IsLinked(NOutput * pOutput)
{
	return pOutput->IsLinked(this);
}

/////////////////////////////////////////////////////////
//float NInput::GetVeOrA()
//{
//	if (activeLinkedOutputPtrs.size() == 0)
//		return A;
//	
//	NOutput* outputPtr = activeLinkedOutputPtrs[0];
//	float MinAvgErr = outputPtr->AvgErr;
//	float Ve = outputPtr->Ve;
//
//	for (int i = 1; i < activeLinkedOutputPtrs.size(); i++)
//	{
//		outputPtr = activeLinkedOutputPtrs[i];
//
//		if (outputPtr->AvgErr < MinAvgErr)
//		{
//			MinAvgErr = outputPtr->AvgErr;
//			Ve = outputPtr->Ve;
//		}
//	}
//
//	return Ve;
//}

/////////////////////////////////////////////////////////
inline float NInput::GetVeOrA()
{
	return Ve == NAN ? A : Ve;
}

/////////////////////////////////////////////////////////
void NInput::DeltaVeOrA(float da)
{
	Vb = Ve == NAN ? A + da : Ve + da;
	A = A + da / 1000;

	Ve = NAN;
	VeAvgErr = FLT_MAX;
}



