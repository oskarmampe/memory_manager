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

SingleStack::Marker SingleStack::alloc(U32 size_bytes)
{
	//
	if (top_marker == NULL)
	{
		top_marker = base_pointer + size_bytes;
	} 
	else
	{
		top_marker += size_bytes;
	}
	return top_marker;
		
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
	delete[] base_pointer;
}

