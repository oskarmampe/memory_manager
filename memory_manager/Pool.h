#pragma once
#include <cstdint>
#include <stdlib.h>

class Pool
{
public:
	typedef uint32_t U32;

	explicit Pool(U32, U32);

	unsigned char* alloc();

	void free(unsigned char*);

	void clear();

private:
	unsigned char* base_pointer;

	struct Node
	{
		unsigned char* data;
		Node* next;
	};

	Node* head;
};