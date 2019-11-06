#pragma once
#include <cstdint>
#include <stdlib.h>

template <class T>
class Pool
{
public:
	typedef uint32_t U32;

	explicit Pool(U32 no_of_elements)
	{
		base_pointer = new T[no_of_elements];
		size = no_of_elements;
		initialise_linked_list();
	}


	T* alloc()
	{
		//return the next free pointer
		T* result = head->data;
		head = head->next;

		return result;

	}

	void free(T* pointer)
	{
		// Create a node and add it to the linked list.
		Node* temp = new Node{ pointer, head };
		head = temp;
	}

	void clear()
	{
		initialise_linked_list();
	}

private:
	T* base_pointer;

	struct Node
	{
		T* data;
		Node* next;
	};

	Node* head;

	void initialise_linked_list()
	{

		Node* curr = new Node;
		for (U32 i = 0; i < size; ++i)
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

	U32 size;
};