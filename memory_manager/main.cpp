#include "SingleStack.h"
#include "DoubleStack.h"
#include "SmartPointer.h"
#include <iostream>

int main()
{
	DoubleStack dstack(20);
	int *x = new int{ 0 };
	SmartPointer<SingleStack> pointer(new SingleStack(20));

	int* test = (int*) pointer->alloc(8);

	*test = 1;
	*(test + 1) = 2;
	*(test + 2) = 3;

	std::cout << *test << *(test + 1) << *(test + 2);

	pointer->freeToMarker(0);


	std::cout << *test << *(test + 1) << *(test + 2);

	pointer->clear();

	std::cout << *test << *(test + 1) << *(test + 2);

	return 0;
}