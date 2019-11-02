#pragma once

#include "SingleStack.h"

///
///
/// <- TOP
///
///
/// <- MARKER
///
///
/// <- BOTTOM
///
///
/// WHILE TOP != MARKER
/// FREE MEMORY


SingleStack::SingleStack(U32 stackSize_bytes)
{
	//
	base_pointer = new unsigned char[stackSize_bytes];
	top_marker = 0;
}

unsigned char* SingleStack::alloc(U32 size_bytes)
{
	//
	Marker temp_marker = top_marker;
	std::cout << temp_marker;
	top_marker += size_bytes;
	std::cout << temp_marker;
	return base_pointer + temp_marker;
		
}

SingleStack::Marker SingleStack::getMarker()
{
	//
	return top_marker;
}

void SingleStack::freeToMarker(SingleStack::Marker marker)
{
	//
	top_marker = marker;
}

void SingleStack::clear()
{
	//
	top_marker = 0;
	delete[] base_pointer; // cleanup
}

