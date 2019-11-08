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
	top_marker = base_pointer;
	size_free = stackSize_bytes;
	stack_size = stackSize_bytes;
}


SingleStack::~SingleStack()
{
	delete[] base_pointer;
	base_pointer = nullptr;
}

SingleStack::Marker SingleStack::alloc(U32 size_bytes)
{
	//
	if (top_marker == NULL)
	{
		top_marker = base_pointer;
	} 
	else
	{
		top_marker += size_bytes;
	}
	size_free -= size_bytes;
	return top_marker - size_bytes;
		
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
	size_free = top_marker - base_pointer;
}

void SingleStack::clear()
{
	//
	top_marker = base_pointer;
	size_free = stack_size;
}

SingleStack::U32 SingleStack::getFreeSize()
{
	return size_free;
}
