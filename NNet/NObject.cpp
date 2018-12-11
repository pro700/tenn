
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
	: pField(_pField)
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
void NObject::Eval()
{
	for (int i = 0; i < inputs.size(); i++)
	{
		NInput& input = inputs[i];

		float ve = 0;

		if (input.activeLinkedOutputPtr != NULL)
			ve += pField->y[i] * input.activeLinkedOutputPtr->Ve;
		else
			ve += pField->y[i] * input.A;

		output.Ve = output.B + ve;
	}

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


