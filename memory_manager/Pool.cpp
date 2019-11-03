#include "Pool.h"

Pool::Pool(U32 byte_size, U32 no_of_elements)
{
	U32 size = byte_size * no_of_elements;
	base_pointer = new unsigned char[size];

	Node* curr = new Node;

	for (int i = 0; i < size; i += byte_size)
	{

		Node* temp = new Node;
		temp->data = base_pointer+i;
		temp->next = NULL;
		if (head == NULL)
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

unsigned char* Pool::alloc()
{
	//return the next free pointer
	unsigned char* result = head->data;
	head = head->next;

	return result;

}

void Pool::free(unsigned char* pointer)
{
	// Create a node and add it to the linked list.
	delete pointer;
	Node* temp = new Node{ pointer, head };
	head = temp;
}

void Pool::clear()
{
	delete[] base_pointer;
}