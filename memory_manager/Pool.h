#pragma once
#include <cstdint>
#include <stdlib.h>

/*
	Pool class representing a pool allocator.
	This allocator is only used to reserve memory.
	It does little to no book-keeping.
*/

class Pool
{
public:
	// A node struct to keep track of the data and the pointer to next allocated memory.
	struct Node
	{
		unsigned char* data;
		Node* next;
	};

	// Typedef for clarity
	typedef uint32_t U32; 

	// Constructor/Destructor
	explicit Pool(U32, U32);
	virtual ~Pool();

	// Allocate memory by getting a free pointer from a linked list
	Node* alloc();

	// Free the pointer by putting the node back into the linked list.
	void free(Node*);

	// Reset the linked list.
	void clear();

private:
	unsigned char* base_pointer; // Bottom of the linked list
	U32 size; // Total size in bytes which is the number of elements * type size in bytes.
	U32 byte_size; // Byte size of the type that is being allocated
	Node* head; // The head of the linked list

	void initialise_linked_list(); // Create the linked list.	
};