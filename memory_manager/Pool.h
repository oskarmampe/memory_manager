#pragma once
#include <cstdint>
#include <stdlib.h>

class Pool
{
public:
	typedef uint32_t U32;

	explicit Pool(U32, U32);
	virtual ~Pool();
	unsigned char* alloc();
	void free(unsigned char*);

	void clear();

private:

	struct Node
	{
		unsigned char* data;
		Node* next;
	};

	unsigned char* base_pointer;
	U32 size;
	U32 byte_size;
	Node* head;

	void initialise_linked_list();	
};