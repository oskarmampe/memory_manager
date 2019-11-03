#include "SingleStack.h"
#include "DoubleStack.h"
#include "SmartPointer.h"
#include <iostream>

int main()
{
	SingleStack stack(12);
	DoubleStack dstack(20);

	int* test = (int*) stack.alloc(8);

	*test = 1;
	*(test + 1) = 2;
	*(test + 2) = 3;

	std::cout << *test << *(test + 1) << *(test + 2);

	stack.freeToMarker(0);


	std::cout << *test << *(test + 1) << *(test + 2);

	return 0;
}