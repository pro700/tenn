#include <stdlib.h>
#include <new>

#include "NInput.h"
#include "NOutput.h"
#include "NObject.h"



/////////////////////////////////////////////////////////
NInput::NInput(NObject* _pObject)
	: pObject(_pObject)
	, A(0)
	, linkedOutputPtrs(0)
	, activeLinkedOutputPtr(NULL)

{
}

/////////////////////////////////////////////////////////
NInput::~NInput()
{
}

/////////////////////////////////////////////////////////
void NInput::Link(NOutput* pOutput)
{
	pOutput->Link(this);
}

bool NInput::IsLinked(NOutput * pOutput)
{
	return pOutput->IsLinked(this);
}



