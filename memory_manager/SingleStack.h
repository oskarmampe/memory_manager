#pragma once
#include <cstdint>
#include <stdlib.h>
#include <iostream>


#include "SmartPointer.h"

class SingleStack
{
public:
	typedef uint32_t U32;
	typedef U32 Marker;

	explicit SingleStack(U32);

	unsigned char* alloc(U32);

	Marker getMarker();

	void freeToMarker(Marker);

	void clear();

private:
	unsigned char* base_pointer;
	Marker top_marker;
};