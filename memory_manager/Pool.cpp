#include "Pool.h"


Pool::Pool(U32 size_byte, U32 no_of_elements)
{
    size = no_of_elements*byte_size;
	base_pointer = new unsigned char[size];
    byte_size = size_byte;
	initialise_linked_list();
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
	Node* temp = new Node{ pointer, head };
	head = temp;
}

void Pool::clear()
{
	initialise_linked_list();
}

void Pool::initialise_linked_list()
{

	Node* curr = new Node;
	for (U32 i = 0; i < size; i += byte_size)
	{

		Node* temp = new Node;
		temp->data = base_pointer + i;
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