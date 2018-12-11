#include <vector>

#include "NInput.h"
#include "NOutput.h"
#include "NObject.h"
#include "NLayer.h"
#include "NBlock.h"


/////////////////////////////////////////////////////////
NBlock::NBlock(NField * pField, int countOfLayers, int countOfObjectsInLayer, int _countOfLinksPerObject)
	: layers(countOfLayers, NLayer(pField, countOfObjectsInLayer))
	, countOfLinksPerObject(_countOfLinksPerObject)
{
}

/////////////////////////////////////////////////////////
NBlock::~NBlock()
{
}

/////////////////////////////////////////////////////////
void NBlock::Link()
{

	for (int n = 0; n < layers.size() - 1; n++)
	{
		layers[n].Link(layers, n + 1, layers.size() - 1, countOfLinksPerObject);
	}

}

/////////////////////////////////////////////////////////
void NBlock::Eval()
{
	for (int n = 0; n < layers.size(); n++)
	{
		layers[n].Eval();
	}
}

/////////////////////////////////////////////////////////
void NBlock::Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks)
{
	for (int n = 0; n < layers.size(); n++)
	{
		layers[n].Count(countOfInputs, countOfLinks, countOfActiveLinks);
	}

}
