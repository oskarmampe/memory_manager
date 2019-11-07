#pragma once
#include <cstdint>
#include <stdlib.h>
#include <iostream>


#include "SmartPointer.h"

class SingleStack
{
public:
	typedef uint32_t U32;
	typedef unsigned char* Marker;

	explicit SingleStack(U32);

	virtual ~SingleStack();

	Marker alloc(U32);

	Marker getMarker();

	void freeToMarker(Marker);

	void clear();

private:
	Marker base_pointer;
	Marker top_marker;
	U32 size_allocated;
};