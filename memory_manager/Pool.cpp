#include "Pool.h"

/*
	Implementation of pool allocator.
*/

// Constructor which allocates a chunk of memory and intiailizes all the variables.
Pool::Pool(U32 size_byte, U32 no_of_elements)
{
    size = no_of_elements*size_byte;
	base_pointer = new unsigned char[size];
    byte_size = size_byte;
	head = nullptr;
	initialise_linked_list();
}

// Destructor, which clears the pointer and allocated memory.
Pool::~Pool()
{
	delete[] base_pointer;
	base_pointer = nullptr;
}


// Allocate a pool by returning a free node.
Pool::Node* Pool::alloc()
{
	if (head == nullptr)
	{
		return nullptr;
	}

	//return the next free pointer
	Node* result = head;

	head = result->next;

	return result;

}

// Free the pointer by creating a new node and adding it to the linked list.
void Pool::free(Node* pointer)
{
	// Create a node and add it to the linked list.
	Node* temp = new Node{ pointer->data, head };
	head = temp;
}

// Clear the linked list, by creating a new linked list.
void Pool::clear()
{
	initialise_linked_list();
}

// Initialize a linked list.
void Pool::initialise_linked_list()
{

	Node* curr = new Node{ nullptr, nullptr };

	// Loop through starting at base pointer going up by a byte size.
	for (U32 i = 0; i < size; i += byte_size)
	{

		Node* temp = new Node {base_pointer + i, nullptr}; 
		if (head == nullptr)
		{
			head = temp;
			curr = temp;
		}
		else
		{
			curr->next = temp;
			curr = temp;
		}
	}
}