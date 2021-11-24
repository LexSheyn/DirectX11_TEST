#include "../PrecompiledHeaders/stdafx.h"
#include "GraphicsException.h"

namespace dx11
{
// Constructors and Destructor:

	GraphicsException::GraphicsException()
	{
	}

	GraphicsException::GraphicsException(int32 line, const char* file)
		: Exception( line, file )
	{
	}


// Functions:

	void GraphicsException::Except( int32 line, const char* file )
	{
		GraphicsException graphics_exception( line, file );

		throw graphics_exception;
	}
}