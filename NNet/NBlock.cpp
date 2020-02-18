#include <vector>
#include <algorithm>    // std::shuffle

#include "NInput.h"
#include "NOutput.h"
#include "NObject.h"
#include "NLayer.h"
#include "NBlock.h"
#include <ctime>


/////////////////////////////////////////////////////////
NBlock::NBlock(NField * pField, int countOfLayers, int countOfObjectsInLayer, int countOfLinksPerObject, float p)
	: layers(countOfLayers, NLayer(pField, this, countOfObjectsInLayer))
	, terminalInputs(countOfObjectsInLayer, NInput(NULL))
	, countOfLinksPerObject(countOfLinksPerObject)
	, p(p)
	, randomObjectsIndexes(countOfObjectsInLayer, 0)
	, randomA(countOfObjectsInLayer, 0)
	, randomB(countOfObjectsInLayer, 0)
	, countOfLinksPerObjectPerLayer(countOfLayers, 0)
{
	linear_rand.seed(unsigned(std::time(0)));

	for (int i = 0; i < randomObjectsIndexes.size(); i++)
		randomObjectsIndexes[i] = i;

	random_shuffle(randomObjectsIndexes.begin(), randomObjectsIndexes.end());
	for (int i = 0; i < countOfLayers; i++)
		countOfLinksPerObjectPerLayer[i] = round(countOfLinksPerObject * p * pow(1 - p, i));
}

/////////////////////////////////////////////////////////
std::vector<int>& NBlock::GetRandomObjectsIndexes(int countOfObjects)
{
	return randomObjectsIndexes;
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

	layers.rbegin()->Link(terminalInputs);
}

/////////////////////////////////////////////////////////
void NBlock::LinkR()
{
	for (auto rcur = layers.rbegin(); rcur < layers.rend() - 1; rcur++) 
	{
		rcur->LinkR(rcur + 1, layers.rend(), countOfLinksPerObject);
	}

	layers.rbegin()->Link(terminalInputs);
}

/////////////////////////////////////////////////////////
void NBlock::Link2()
{
	for (int n = 0; n < layers.size() - 1; n++)
	{
		layers[n].Link2(layers, n + 1, layers.size() - 1);
	}

	layers.rbegin()->Link(terminalInputs);
}

/////////////////////////////////////////////////////////
void NBlock::Eval()
{
	for (auto &layer : layers)
		layer.Eval();
}

/////////////////////////////////////////////////////////
void NBlock::GetVe(std::vector<float>& Ve)
{
	layers.rbegin()->GetVe(Ve);
}

/////////////////////////////////////////////////////////
void NBlock::SetVb(std::vector<float>& Vb)
{
	layers.rbegin()->SetVb(Vb);
}

/////////////////////////////////////////////////////////
void NBlock::Back()
{
	for (auto layerPtr = layers.rbegin(); layerPtr != layers.rend(); layerPtr++)
	{
		layerPtr->Back();
	}
}

/////////////////////////////////////////////////////////
void NBlock::Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks)
{
	for (auto &layer : layers)
		layer.Count(countOfInputs, countOfLinks, countOfActiveLinks);
}
