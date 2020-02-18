#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>

#include "NField.h"
#include "NObject.h"
#include "NLayer.h"
#include "NBlock.h"

int main()
{

	std::srand(unsigned(std::time(0)));

	int n = 0;
	

	NField field(100);

	NBlock block(&field, 300, 300, 300);

	std::clock_t start = std::clock();
	double duration0 = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	start = std::clock();
  	block.Link();
	double duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	start = std::clock();
	block.Eval();
	double duration1 = (std::clock() - start) / (double)CLOCKS_PER_SEC;

	int countOfInputs = 0;
	int countOfLinks = 0;
	int countOfActiveLinks = 0;

	block.Count(countOfInputs, countOfLinks, countOfActiveLinks);

	std::cout << "Hello World!" << std::endl;
	std::cout << "duration0=" << duration0 << std::endl;
	std::cout << "duration=" << duration << std::endl;
	std::cout << "duration1=" << duration1 << std::endl;
	std::cout << "countOfInputs=" << countOfInputs << std::endl;
	std::cout << "countOfLinks=" << countOfLinks << std::endl;
	std::cout << "countOfActiveLinks=" << countOfActiveLinks << std::endl;
	std::cin >> n;

	
	return 0;
}