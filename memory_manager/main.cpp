#include "SingleStack.h"
#include "DoubleStack.h"
#include "Pool.h"
#include "SmartPointer.h"
#include <iostream>

int main()
{
	int* x = new int{ 0 };
	
	SmartPointer<DoubleStack> dstack(new DoubleStack(24));
	SmartPointer<Pool<int>> pool(new Pool<int>(5));

	// ------------------------------------------------------------
	// ------------------------ STACK TEST ------------------------
	// ------------------------------------------------------------
	{
		SmartPointer<SingleStack> stack(new SingleStack(20));
		{
			// DON'T USE SMART POINTERS FOR INDIVIDUAL POINTERS USE IT FOR ALLOCATORS
			// 
			SingleStack::Marker smarker = stack->getMarker();
			int* test = (int*)stack->alloc(sizeof(int));

			*test = 1;

			std::cout << "FIRST INT VAL" << *test << std::endl;

			stack->freeToMarker(smarker);
		}

		{
			SingleStack::Marker smarker = stack->getMarker();
			double* test = (double*)stack->alloc(sizeof(double));

			*test = 1.5;

			std::cout << "FIRST DOUBLE VAL" << *test << std::endl;

			stack->freeToMarker(smarker);
		}
	}
	

	SmartPointer<SingleStack> stack(new SingleStack(20));
	int* test = (int*)stack->alloc(sizeof(int));

	*test = 1;

	std::cout << "SECOND INT VAL" << *test << std::endl;

	//*(test + 1) = 2;
	//*(test + 2) = 3;

	//std::cout << *test << *(test + 1) << *(test + 2);

	//stack->freeToMarker(0);

	SmartPointer<SingleStack> vbfd = stack;

	//std::cout << std::endl << "pointer count: " << stack.getCount() << std::endl;


	//std::cout << *test << *(test + 1) << *(test + 2);

	stack->clear();

	//std::cout << *test << *(test + 1) << *(test + 2);


	//int* tests = (int*)stack->alloc(8);

	//*tests = 1;
	//*(tests + 1) = 2;
	//*(tests + 2) = 3;

	//std::cout << *tests << *(tests + 1) << *(tests + 2);

	//stack->freeToMarker(0);

	//SmartPointer<SingleStack> lkj = stack;

	//std::cout << std::endl << "pointer count: " << stack.getCount() << std::endl;

	//std::cout << *tests << *(tests + 1) << *(tests + 2);

	//stack->clear();
/*
	std::cout << *tests << *(tests + 1) << *(tests + 2);*/


	// -------------------------------------------------------------------
	// ------------------------ DOUBLE STACK TEST ------------------------
	// -------------------------------------------------------------------



	//{
	//	//int* dtest =;
	//	DoubleStack::Marker dstack_marker = dstack->getMarker(DoubleStack::TOP_STACK);
	//	SmartPointer<int> point_test((int*)dstack->alloc(sizeof(int), DoubleStack::TOP_STACK));

	//	

	//	

	//	*point_test = 1;

	//	dstack->freeToMarker(dstack_marker, DoubleStack::TOP_STACK);
	//}
	


	//*(dtest - 1) = 2;
	//*(dtest - 2) = 3;

	//std::cout << *dtest << *(dtest - 1) << *(dtest - 2);

	//dstack->freeToMarker(0, DoubleStack::TOP_STACK);

	//SmartPointer<DoubleStack> vcx = dstack;

	//std::cout << std::endl << "pointer count: " << dstack.getCount() << std::endl;


	//std::cout << *dtest << *(dtest - 1) << *(dtest - 2);

	//dstack->clear();

	//std::cout << *dtest << *(dtest - 1) << *(dtest - 2);


	//int* dtestz = (int*)dstack->alloc(12, DoubleStack::TOP_STACK);

	//*dtestz = 1;
	//*(dtestz - 1) = 2;
	//*(dtestz - 2) = 3;

	//std::cout << *dtestz << *(dtestz - 1) << *(dtestz - 2);

	//dstack->freeToMarker(0, DoubleStack::TOP_STACK);

	//SmartPointer<DoubleStack> mnb = dstack;

	//std::cout << std::endl << "pointer count: " << dstack.getCount() << std::endl;


	//std::cout << *dtestz << *(dtestz - 1) << *(dtestz - 2);

	//dstack->clear();

	//std::cout << *dtestz << *(dtestz - 1) << *(dtestz - 2);



	int* dtestb = (int*)dstack->alloc(12, DoubleStack::BOTTOM_STACK);

	*dtestb = 1;
	*(dtestb + 1) = 2;
	*(dtestb + 2) = 3;

	std::cout << *dtestb << *(dtestb + 1) << *(dtestb + 2);

	dstack->freeToMarker(0, DoubleStack::BOTTOM_STACK);

	SmartPointer<DoubleStack> bvc = dstack;

	std::cout << std::endl << "pointer count: " << dstack.getCount() << std::endl;

	std::cout << *dtestb << *(dtestb + 1) << *(dtestb + 2);

	dstack->clear();

	std::cout << *dtestb << *(dtestb + 1) << *(dtestb + 2);

	// -----------------------------------------------------------
	// ------------------------ POOL TEST ------------------------
	// -----------------------------------------------------------
	int* dtest1 = (int*)pool->alloc();
	*dtest1 = 1;

	int* dtest2 = (int*)pool->alloc();
	*dtest2 = 2;

	int* dtest3 = (int*)pool->alloc();
	*dtest3 = 3;

	std::cout << *dtest1 << *dtest2 << *dtest3;

	pool->free(dtest1);

	SmartPointer<Pool<int>> bvcx = pool;

	std::cout << std::endl << "pointer count: " << pool.getCount() << std::endl;


	std::cout << *dtest1 << *dtest2 << *dtest3;

	pool->clear();

	std::cout << *dtest1 << *dtest2 << *dtest3;
	return 0;
}