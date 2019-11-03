#pragma once
#include <cstdint>
#include <stdlib.h>
#include <iostream>


#include "SmartPointer.h"

class DoubleStack
{
public:
	enum POSITION
	{
		BOTTOM_STACK,
		TOP_STACK
	};

	typedef uint32_t U32;
	typedef unsigned char* Marker;

	explicit DoubleStack(U32);

	unsigned char* alloc(U32, POSITION);

	Marker getMarker(POSITION);

	void freeToMarker(Marker, POSITION);

	void clear();



private:
	unsigned char* base_pointer;
	U32 stack_size;
	Marker top_marker;
	Marker bottom_marker;
};