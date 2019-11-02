#include "SingleStack.h"
#include "SmartPointer.h"
#include <iostream>

int main()
{
	SingleStack stack(2);

	int* test = (int*) stack.alloc(2);

	*test = 1;
	*(test + 1) = 2;
	*(test + 2) = 3;

	std::cout << *test << *(test + 1) << *(test + 2);
	return 0;
}