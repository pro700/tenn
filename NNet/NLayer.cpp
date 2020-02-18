#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <vector>        // std::vector
#include <random>       // std::default_random_engine

#include "NBlock.h"
#include "NLayer.h"
#include "NObject.h"

/////////////////////////////////////////////////////////
NLayer::NLayer(NField* pField, NBlock* _pBlock, int countOfObjects)
	: objects(countOfObjects, NObject(pField))
	, pBlock(_pBlock)
{
}

/////////////////////////////////////////////////////////
NLayer::~NLayer()
{
}

/*
/////////////////////////////////////////////////////////
void NLayer::Link(std::vector<NLayer>& dstLayers, int beg, int end, int countOfLinksPerObject)
{
	std::vector<NObject*> dstObjectPtrs;
	for (int iLayer = beg; iLayer <= end; iLayer++)
	{
		for (auto &dstObject : dstLayers[iLayer].objects)
			dstObjectPtrs.push_back(&dstObject);
	}

	int allLinksCount = objects.size()*countOfLinksPerObject;
	std::vector<int> allLinksIndexes(allLinksCount);
	for (int k = 0; k < allLinksCount; k++)
		allLinksIndexes[k] = k;
	std::random_shuffle(allLinksIndexes.begin(), allLinksIndexes.end());

	int n = 0;
	for (auto &object : objects)
	{
		for (int iLinkPerObject = 0; iLinkPerObject < countOfLinksPerObject; iLinkPerObject++)
		{
			int m = allLinksIndexes[n++] % dstObjectPtrs.size();
			object.Link(*dstObjectPtrs[m]);
		}
	}
}

/////////////////////////////////////////////////////////
void NLayer::Link1(std::vector<NLayer>& dstLayers, int beg, int end, int countOfLinksPerObject)
{
	for (int n = 0; n < objects.size(); n++)
	{
		NObject& object = objects[n];

		for(int i = 0; i < countOfLinksPerObject; i++)
		{
			int iLayer = beg + rand() % (end - beg + 1);
			NLayer& layer = dstLayers[iLayer];
			int min = 0;
			int max = layer.objects.size() - 1;
			int iObject = min + rand() % (max - min + 1);
			object.Link(layer.objects[iObject]);
		}
	}
}
*/

/////////////////////////////////////////////////////////
void NLayer::Link2(std::vector<NLayer>& dstLayers, int iDstLyrBeg, int iDstLyrEnd)
{
	for (int n = 0; n < objects.size(); n++)
	{
		NObject& object = objects[n];

		for (int iDstLyr = iDstLyrBeg; iDstLyr <= iDstLyrEnd; iDstLyr++)
		{
			NLayer& dstLayer = dstLayers[iDstLyr];

			int countOfObjects = pBlock->GetCountOfLinksPerObjectPerLayerDistance(iDstLyr - iDstLyrBeg);


			if (countOfObjects > 0)
			{
				int maxStep = dstLayer.objects.size() / countOfObjects;
				int step = rand() % maxStep;
				int iObj = rand() % dstLayer.objects.size();

				while (countOfObjects-- > 0)
				{
					NObject& dstObject = dstLayer.objects[iObj];
					object.Link(dstObject);
					iObj += step;
					if (iObj >= dstLayer.objects.size())
						iObj -= dstLayer.objects.size();
				}
			}
			

			// (2) std::vector<int>& indexes = pBlock->GetRandomObjectsIndexes();
			/*
			for (auto pIdx = indexes.begin(); pIdx < indexes.begin() + countOfObjects; pIdx++)
			{
				object.Link(dstLayer.objects[*pIdx]);
			}
			*/

			
			/*
			for (int i = 0; i < countOfObjects; i++)
			{
				int j = rand() % dstLayer.objects.size();
				object.Link(dstLayer.objects[j]);
			}
			*/
			

		}
	}
}


/////////////////////////////////////////////////////////
void NLayer::Link(std::vector<NLayer>& dstLayers, int beg, int end, int countOfLinksPerObject)
{
	int countOfDestObjects = 0;
	for (int i = beg; i <= end; i++)
		countOfDestObjects += dstLayers[i].objects.size();

	int min = 1;
	int max = std::max(1, countOfDestObjects / countOfLinksPerObject);

	for (int iSrcObj = 0; iSrcObj < objects.size(); iSrcObj++)
	{
		NObject& object = objects[iSrcObj];
		int step = min + rand() % (max - min + 1);
		int iDstObj = step - 1;

		for (int iDstLyr = beg; iDstLyr <= end; iDstLyr++)
		{
			NLayer& dstLayer = dstLayers[iDstLyr];

			for (; iDstObj < dstLayer.objects.size(); iDstObj += step)
			{
				object.Link(dstLayer.objects[iDstObj]);

				if(object.GetCountOfLinks() >= countOfLinksPerObject)
					goto exit;
			}

			iDstObj -= dstLayer.objects.size();
		}
	exit:;
	}
}

/////////////////////////////////////////////////////////
void NLayer::LinkR(std::reverse_iterator<std::vector<NLayer>::iterator> rbeg, std::reverse_iterator<std::vector<NLayer>::iterator> rend, int countOfLinksPerObject)
{
 	int countOfDestObjects = 0;
	for (auto rcur = rbeg; rcur < rend; rcur++)
		countOfDestObjects += rcur->objects.size();

	int min = 1;
	int max = std::max(1, countOfDestObjects / countOfLinksPerObject);

	for (auto &dstObject : objects)
	{
		int linksPerObject = 0;
		int step = min + rand() % (max - min + 1);
		int iSrcObj = step - 1;

		for (auto rCurSrcLyr = rbeg; rCurSrcLyr < rend; rCurSrcLyr++)
		{
			for (; iSrcObj < rCurSrcLyr->objects.size(); iSrcObj += step)
			{
				rCurSrcLyr->objects[iSrcObj].Link(dstObject);

				if (++linksPerObject >= countOfLinksPerObject)
					goto exit;
			}

			iSrcObj -= rCurSrcLyr->objects.size();
		}

	exit:;
	}
}

/////////////////////////////////////////////////////////
void NLayer::Link(std::vector<NInput>& inputs)
{
	for (int n = 0; n < objects.size() - 1; n++)
	{
		objects[n].Link(inputs[n]);
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

/////////////////////////////////////////////////////////
void NLayer::GetVe(std::vector<float>& Ve)
{
	Ve.resize(objects.size());

	for (int n = 0; n < objects.size(); n++)
	{
		Ve[n] = objects[n].GetVe();
	}
}

/////////////////////////////////////////////////////////
void NLayer::SetVb(std::vector<float>& Vb)
{
	for (int n = 0; n < objects.size(); n++)
	{
		objects[n].SetVb(Vb[n]);
	}
}

/////////////////////////////////////////////////////////
void NLayer::Back()
{
	for (auto& object : objects)
		object.Back();
}


/////////////////////////////////////////////////////////
void NLayer::Count(int& countOfInputs, int& countOfLinks, int& countOfActiveLinks)
{
	for (int n = 0; n < objects.size(); n++)
	{
		objects[n].Count(countOfInputs, countOfLinks, countOfActiveLinks);
	}

}
