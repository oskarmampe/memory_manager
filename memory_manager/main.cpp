#include "SingleStack.h"
#include "DoubleStack.h"
#include "Pool.h"
#include "SmartPointer.h"
#include "MemoryManager.h"
#include <iostream>

int main()
{
	// ------------------------------------------------------------
	// -------------------- MEMORY MANAGER TEST -------------------
	// ------------------------------------------------------------

	{
		MemoryManager mem = {};
		
		{
			std::cout << std::endl << "------------------ MEMORY MANAGER STACK TEST ------------------" << std::endl;

			// Memory stack test
			mem.createStack(8);
			mem.putIntoStack(1);
			mem.putIntoStack('a');
			mem.putIntoStack(3);

			// An example of retrieving from stack.
			// Mixing get and take gives odd results.
			// This is because 'get' doesn't free the memory once a value is retrieved.
			// In this case however, the results are expected. If the char was taken first, and then an int, the results would be inconsistent. 
			// This book-keeping could be implemented in the memory manager, but it would make it much more complicated.
			// Therefore, for simplicity, this book-keeping task is on the programmer using the API.
			char x = mem.takeFromStack<char>();// a
			int y = mem.takeFromStack<int>();// 1
			int z = mem.takeFromStack<int>(); // Null


			std::cout << std::endl << "MEMORY VAL x: " << x << std::endl;
			std::cout << std::endl << "MEMORY VAL y: " << y << std::endl;
			std::cout << std::endl << "MEMORY VAL z: " << z << std::endl;

			mem.putIntoStack(1);// Error not enough space.

			// Testing resetting a stack.
			mem.resetStack(8);

			// 8 bytes exactly as int = 4 char = 1.
			mem.putIntoStack(1);
			mem.putIntoStack('a');
			mem.putIntoStack('b');
			mem.putIntoStack('c');
			mem.putIntoStack('d');

			char ra = mem.takeFromStack<char>();
			char rb = mem.takeFromStack<char>();
			char rc = mem.takeFromStack<char>();
			char rd = mem.takeFromStack<char>();
			int rx = mem.takeFromStack<int>();


			std::cout << std::endl << "MEMORY VAL rx: " << rx << std::endl;
			std::cout << std::endl << "MEMORY VAL ra: " << ra << std::endl;
			std::cout << std::endl << "MEMORY VAL rb: " << rb << std::endl;
			std::cout << std::endl << "MEMORY VAL rc: " << rc << std::endl;
			std::cout << std::endl << "MEMORY VAL rd: " << rd << std::endl;
		}

		{
			std::cout << std::endl << "------------------ MEMORY MANAGER DOUBLESTACK TEST ------------------" << std::endl;

			//Memory double stack test
			mem.createDoubleStack(8);
			mem.putIntoDoubleStack(2, DoubleStack::TOP_STACK);
			mem.putIntoDoubleStack(5, DoubleStack::BOTTOM_STACK);

			// An example of retrieving from double stack.
			// This is similar to a single stack.
			// One exception is that a ENUM is needed from DoubleStack to say which stack is being used.
			// Otherwise, the use is the same.
			int dx = mem.getFromDoubleStack<int>(DoubleStack::BOTTOM_STACK);
			int dy = mem.takeFromDoubleStack<int>(DoubleStack::TOP_STACK);

			std::cout << std::endl << "MEMORY VAL dx: " << dx << std::endl;
			std::cout << std::endl << "MEMORY VAL dy: " << dy << std::endl;

			mem.putIntoDoubleStack('a', DoubleStack::BOTTOM_STACK);
			mem.putIntoDoubleStack('x', DoubleStack::TOP_STACK);
			mem.putIntoDoubleStack('y', DoubleStack::TOP_STACK);

			char da = mem.getFromDoubleStack<char>(DoubleStack::BOTTOM_STACK); // Getting without freeing.
			char db = mem.takeFromDoubleStack<char>(DoubleStack::TOP_STACK); // Take and free.
			char dc = mem.getFromDoubleStack<char>(DoubleStack::TOP_STACK); // Getting without freeing.

			std::cout << std::endl << "MEMORY VAL da: " << da << std::endl;
			std::cout << std::endl << "MEMORY VAL db: " << db << std::endl;
			std::cout << std::endl << "MEMORY VAL dc: " << dc << std::endl;

			mem.resetDoubleStack(8);// Reset stack

			mem.putIntoDoubleStack(452, DoubleStack::TOP_STACK);
			mem.putIntoDoubleStack(1235, DoubleStack::BOTTOM_STACK);

			int dh = mem.getFromDoubleStack<int>(DoubleStack::BOTTOM_STACK);
			int dj = mem.getFromDoubleStack<int>(DoubleStack::TOP_STACK);

			std::cout << std::endl << "MEMORY VAL dh: " << dh << std::endl;
			std::cout << std::endl << "MEMORY VAL dj: " << dj << std::endl;
		}

		{
			std::cout << std::endl << "------------------ MEMORY MANAGER POOL TEST ------------------" << std::endl;

			//Memory pool test
			mem.createPool(sizeof(int), 2);

			//How to put an object in
			mem.putIntoPool<int>(3);
			mem.putIntoPool<int>(76);
			mem.putIntoPool<int>(123);

			// Pool acts as an array. Memory is being allocated and then a pointer is put into a vector.
			// Therefore, to retrieve an element simply input an index. All elements are appended to the end of the vector.
			// Take 'frees' the node and returns the data in it, whilst get just returns the data.
			int pa = mem.takeFromPool<int>(0);
			int pv = mem.getFromPool<int>(0);

			mem.putIntoPool<int>(123);

			int px = mem.getFromPool<int>(0);
			int py = mem.getFromPool<int>(1);

			std::cout << std::endl << "MEMORY VAL pa: " << pa << std::endl;
			std::cout << std::endl << "MEMORY VAL px: " << px << std::endl;
			std::cout << std::endl << "MEMORY VAL py: " << py << std::endl;

			mem.resetPool(sizeof(int), 2);

			mem.putIntoPool<int>(3);
			mem.putIntoPool<int>(76);

			int pg = mem.getFromPool<int>(0);
			int ph = mem.getFromPool<int>(1);

			std::cout << std::endl << "MEMORY VAL pg: " << pg << std::endl;
			std::cout << std::endl << "MEMORY VAL ph: " << ph << std::endl;
		}

	}


	// ------------------------------------------------------------
	// ------------------------ STACK TEST ------------------------
	// ------------------------------------------------------------

	// DON'T USE SMART POINTERS FOR INDIVIDUAL POINTERS USE IT FOR ALLOCATORS
	// This is because smart pointer free memory for the heap.
	// Which is not desired as it should be up to allocators to do that.
	
	std::cout << std::endl << "------------------ STACK ALLOCATOR TEST ------------------" << std::endl;

	// Create a new scope to test if SmartPointer correctly cleans up once references drop to 0.
	{

		// Create a smart pointer to the stack
		SmartPointer<SingleStack> stack(new SingleStack(12));

		// Test whether you can allocate to stack 
		{

			SingleStack::Marker smarker = stack->getMarker();
			int* test = (int*)stack->alloc(sizeof(int));

			*test = 1;

			std::cout << "FIRST STACK TEST: " << *test << std::endl;
		}

		// Test whether you can allocate different types to stack.
		// Also check if the marker goes up correctly.

		{
			SingleStack::Marker smarker = stack->getMarker();
			double* test = (double*)stack->alloc(sizeof(double));

			*test = 1.5;

			std::cout << "SECOND STACK TEST: " << *test << std::endl;
		}


		// Test whether you can free the entire stack.
		{
			stack->clear();

			SingleStack::Marker smarker = stack->getMarker();
			double* test = (double*)stack->alloc(sizeof(double));

			*test = 1.5;

			std::cout << "THIRD STACK TEST: " << *test << std::endl;

			stack->freeToMarker(smarker);
		}

		// Test whether you can free and then allocate something new

		{
			SingleStack::Marker marker = stack->getMarker();

			int* test1 = (int*)stack->alloc(sizeof(int));

			*test1 = 3;

			double* test2 = (double*)stack->alloc(sizeof(double));

			*test2 = 543.0;

			std::cout << "FOURTH STACK TEST: " << *test1 << std::endl;
			std::cout << "FOURTH STACK TEST: " << *test2 << std::endl;

			stack->freeToMarker(marker);
			double* test = (double*)stack->alloc(sizeof(double));

			*test = 234.123;

			std::cout << "FOURTH STACK TEST: " << *test << std::endl;
		}

	}//  End of scope to check if smart pointer correctly destructs.
	

	SmartPointer<SingleStack> stack(new SingleStack(sizeof(int)));
	int* test = (int*)stack->alloc(sizeof(int));

	*test = 1;

	std::cout << "LAST STACK TEST: " << *test << std::endl;


	// -------------------------------------------------------------------
	// ------------------------ DOUBLE STACK TEST ------------------------
	// -------------------------------------------------------------------

	std::cout << std::endl << "------------------ DOUBLESTACK ALLOCATOR TEST ------------------" << std::endl;

		// Create a new scope to test if SmartPointer correctly cleans up once references drop to 0.
	{

		// Create a smart pointer to the stack
		SmartPointer<DoubleStack> dstack(new DoubleStack(12));

		// Test whether you can allocate to top stack 
		{

			DoubleStack::Marker smarker = dstack->getMarker(DoubleStack::TOP_STACK);
			int* test = (int*)dstack->alloc(sizeof(int), DoubleStack::TOP_STACK);

			*test = 1;

			std::cout << "FIRST DOUBLESTACK TEST: " << *test << std::endl;

			dstack->freeToMarker(smarker, DoubleStack::TOP_STACK);
		}

		// Test whether you can allocate to bottom stack 
		{

			DoubleStack::Marker smarker = dstack->getMarker(DoubleStack::BOTTOM_STACK);
			int* test = (int*)dstack->alloc(sizeof(int), DoubleStack::BOTTOM_STACK);

			*test = 1;

			std::cout << "SECOND DOUBLESTACK TEST: " << *test << std::endl;
			dstack->freeToMarker(smarker, DoubleStack::BOTTOM_STACK);
		}


		// Test whether you can allocate different types to stack.
		// Also check if the marker goes up correctly.

		{
			DoubleStack::Marker smarker = dstack->getMarker(DoubleStack::TOP_STACK);
			double* test = (double*)dstack->alloc(sizeof(double), DoubleStack::TOP_STACK);
			int* test1 = (int*)dstack->alloc(sizeof(int), DoubleStack::TOP_STACK);

			*test = 1.5;
			*test1 = 1.5;

			std::cout << "THIRD DOUBLESTACK TEST: " << *test << std::endl;
			std::cout << "THIRD DOUBLESTACK TEST: " << *test1 << std::endl;
		}

		// Test whether you can allocate to both stacks
		{

			DoubleStack::Marker tmarker = dstack->getMarker(DoubleStack::TOP_STACK);
			DoubleStack::Marker bmarker = dstack->getMarker(DoubleStack::TOP_STACK);

			int* test = (int*)dstack->alloc(sizeof(int), DoubleStack::BOTTOM_STACK);
			int* test1 = (int*)dstack->alloc(sizeof(int), DoubleStack::TOP_STACK);

			*test = 1;

			std::cout << "FOURTH DOUBLESTACK TEST: " << *test << std::endl;
			std::cout << "FOURTH DOUBLESTACK TEST: " << *test1 << std::endl;

			dstack->freeToMarker(bmarker, DoubleStack::BOTTOM_STACK);
			dstack->freeToMarker(tmarker, DoubleStack::TOP_STACK);
		}


		// Test whether you can free the entire stack.
		{
			dstack->clear();

			SingleStack::Marker smarker = dstack->getMarker(DoubleStack::TOP_STACK);
			double* test = (double*)dstack->alloc(sizeof(double), DoubleStack::TOP_STACK);

			*test = 1.5;

			std::cout << "THIRD DOUBLESTACK TEST: " << *test << std::endl;

			dstack->freeToMarker(smarker, DoubleStack::TOP_STACK);
		}

		// Test whether you can free and then allocate something new

		{
			DoubleStack::Marker marker = dstack->getMarker(DoubleStack::TOP_STACK);

			int* test1 = (int*)dstack->alloc(sizeof(int), DoubleStack::TOP_STACK);

			*test1 = 3;

			double* test2 = (double*)dstack->alloc(sizeof(double), DoubleStack::TOP_STACK);

			*test2 = 543.0;

			std::cout << "FOURTH DOUBLESTACK TEST: " << *test1 << std::endl;
			std::cout << "FOURTH DOUBLESTACK TEST: " << *test2 << std::endl;

			dstack->freeToMarker(marker);
			double* test = (double*)dstack->alloc(sizeof(double), DoubleStack::TOP_STACK);

			*test = 234.123;

			std::cout << "FOURTH DOUBLESTACK TEST: " << *test << std::endl;
		}

	}//  End of scope to check if smart pointer correctly destructs.


	SmartPointer<DoubleStack> dstack(new DoubleStack(sizeof(int)));
	int* test = (int*)dstack->alloc(sizeof(int), DoubleStack::TOP_STACK);

	*test = 1;

	std::cout << "LAST DOUBLESTACK TEST: " << *test << std::endl;


	// -----------------------------------------------------------
	// ------------------------ POOL TEST ------------------------
	// -----------------------------------------------------------
		// INITIALIZATION
		// ALLOCATION
		// CLEAR
		// FREE
		// OVERASSIGNING
		// CLEANUP/SCOPE TEST
	{
		SmartPointer<Pool> pool(new Pool(sizeof(int), 3));

		Pool::Node* dtest1 = pool->alloc();
		int* data = (int*)(dtest1->data);
		*(data) = 1;


		Pool::Node* dtest2 = pool->alloc();
		int* data2 = (int*)(dtest2->data);
		*(data2) = 2;

		Pool::Node* dtest3 = pool->alloc();
		int* data3 = (int*)(dtest3->data);
		*(data3) = 3;

		std::cout << std::endl << "POOL TEST: " << *(data) << *(data2) << *(data3);

		pool->free(dtest1);

		SmartPointer<Pool> bvcx = pool;

		std::cout << std::endl << "pointer count: " << pool.getCount() << std::endl;


		std::cout << std::endl << "POOL TEST: " << *(data) << *(data2) << *(data3);

		pool->clear();

		std::cout << std::endl << "POOL TEST: " << *(data) << *(data2) << *(data3);
	}

	{
		SmartPointer<Pool> pool(new Pool(sizeof(int), 2));

		Pool::Node* dtest1 = pool->alloc();
		int* data = (int*)(dtest1->data);
		*(data) = 1;


		Pool::Node* dtest2 = pool->alloc();
		int* data2 = (int*)(dtest2->data);
		*(data2) = 2;

		// Uncommenting this line breaks the program, as expected.
		// Pool::Node* dtest4 = pool->alloc();

		std::cout << std::endl << "POOL TEST: " << *(data) << *(data2);

		pool->free(dtest1);

		Pool::Node* dtest3 = pool->alloc();
		int* data3 = (int*)(dtest3->data);
		*(data3) = 36;

		SmartPointer<Pool> bvcx = pool;

		std::cout << std::endl << "pointer count: " << pool.getCount() << std::endl;


		std::cout << std::endl << "POOL TEST: " << *(data) << *(data2);

		pool->clear();

		std::cout << std::endl << "POOL TEST: " << *(data) << *(data2);
	}
	return 0;
}