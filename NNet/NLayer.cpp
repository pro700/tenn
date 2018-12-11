#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <vector>        // std::vector
#include <random>       // std::default_random_engine

#include "NLayer.h"
#include "NObject.h"

/////////////////////////////////////////////////////////
NLayer::NLayer(NField* pField, int countOfObjects)
	: objects(countOfObjects, NObject(pField))
{
}

/////////////////////////////////////////////////////////
NLayer::~NLayer()
{
}

/////////////////////////////////////////////////////////
void NLayer::Link(std::vector<NLayer>& dstLayers, int beg, int end, int countOfLinksPerObject)
{
	int countOfDestObjects = 0;
	for (int i = beg; i <= end; i++)
		countOfDestObjects += dstLayers[i].objects.size();

	int min = 1;
	int max = std::max(1, countOfDestObjects / countOfLinksPerObject);

	for (int n = 0; n < objects.size(); n++)
	{
		NObject& object = objects[n];
		int step = min + (rand() % static_cast<int>(max - min + 1));
		int m = step - 1;

		for (int i = beg; i <= end; i++)
		{
			NLayer& dstLayer = dstLayers[i];

			for (; m < dstLayer.objects.size(); m += step)
			{
				object.Link(dstLayer.objects[m]);

				if(object.GetCountOfLinks() >= countOfLinksPerObject)
					goto exit;
			}

			m = dstLayer.objects.size() - m;
		}
	exit:;
	}
}

/////////////////////////////////////////////////////////
void NLayer::Eval()
{
	for (int n = 0; n < objects.size(); n++)
	{
		objects[n].Eval();
	}
}

void NLayer::Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks)
{
	for (int n = 0; n < objects.size(); n++)
	{
		objects[n].Count(countOfInputs, countOfLinks, countOfActiveLinks);
	}

}
