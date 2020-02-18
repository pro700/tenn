
#include <algorithm>    // std::shuffle
#include <stdlib.h>
#include <new>
#include <vector>
#include <iostream>

#include "NObject.h"
#include "NInput.h"
#include "NOutput.h"
#include "NField.h"

using namespace std;


/////////////////////////////////////////////////////////
NObject::NObject(NField* _pField)
	: isLocked(false)
	, pField(_pField)
	, inputs(_pField->y.size(), NInput(this))
	, output(this)
{
}

/////////////////////////////////////////////////////////
NObject::~NObject()
{
}

/////////////////////////////////////////////////////////
NInput* NObject::GetMostFreeInput()
{
	NInput* pInput = nullptr;
	size_t nMin = INT_MAX;

	std::vector<int> n = NField::GenerateRandomIndexes(inputs.size());

	for (int i = 0; i < n.size(); i++)
	{
		NInput* pInput1 = &inputs[n[i]];
		if (pInput1->linkedOutputPtrs.size() < nMin)
		{
			pInput = pInput1;
			nMin = pInput1->linkedOutputPtrs.size();
		}
	}

	return pInput;
}

/////////////////////////////////////////////////////////
NInput* NObject::GetRandomInput()
{
	return &inputs[rand()%inputs.size()];
}

/////////////////////////////////////////////////////////
void NObject::Link(NObject& dstObject)
{
	NInput* pDstInput = dstObject.GetRandomInput();
	output.Link(pDstInput);
}

/////////////////////////////////////////////////////////
void NObject::Link(NInput& dstInput)
{
	output.Link(&dstInput);
}

/////////////////////////////////////////////////////////
void NObject::Eval()
{
	float ve = output.GetB();

	for (int i = 0; i < inputs.size(); i++)
		ve += pField->y[i] * inputs[i].GetVeOrA();

	output.SetVe(ve);
}

/////////////////////////////////////////////////////////
float NObject::GetVe() 
{
	return output.Ve;
}

/////////////////////////////////////////////////////////
void NObject::SetVb(float Vb)
{
	output.activeLinkedInputPtr->SetVb(Vb);
}

/////////////////////////////////////////////////////////
// Ve = B + Sum{ y[i]*(A[i]/Ve[i]) }
void NObject::Back()
{

	// 1) Calculate Delta A[i]/Ve[i]
	float Vb = output.activeLinkedInputPtr->GetVb();
	float e = output.Ve - Vb;
	float Err = abs(e);
	output.AvgErr = 0.95*output.AvgErr + Err;
	float s2 = 1.0;
	for (int i = 0; i < inputs.size(); i++)
		s2 += pField->y[i] * pField->y[i];

	float K = 1 / s2;
	output.B -= K * e / 1000;
	for (int i = 0; i < inputs.size(); i++)
	{
		float da = -K * e * pField->y[i];
		inputs[i].DeltaVeOrA(da);
	}


	// 2) Choose active input
	NInput* nextActiveInputPtr = NULL;
	float MinAvgErr = FLT_MAX;

	for (int i = 0; i < output.linkedInputPtrs.size(); i++)
	{
		NInput* inputPtr = output.linkedInputPtrs[i];

		// Compare CurrentActive and NonActive inputs
		float Err = abs(output.Ve - inputPtr->GetVb());
		inputPtr->AvgErr = 0.95*inputPtr->AvgErr + Err;

		if (inputPtr->AvgErr < MinAvgErr)
		{
			MinAvgErr = inputPtr->AvgErr;
			nextActiveInputPtr = inputPtr;
		}
	}

	if (nextActiveInputPtr != output.activeLinkedInputPtr)
		output.MakeActive(nextActiveInputPtr); 

}

/////////////////////////////////////////////////////////
void NObject::Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks)
{
	for (int i = 0; i < inputs.size(); i++)
	{
		NInput& input = inputs[i];

		countOfInputs += 1;
		countOfLinks += input.linkedOutputPtrs.size();
		countOfActiveLinks += (input.activeLinkedOutputPtr != NULL ? 1 : 0);
	}
}

/////////////////////////////////////////////////////////
std::vector<int> NObject::GenerateRandomIndexes(size_t Size)
{
	return pField->GenerateRandomIndexes(Size);
}



