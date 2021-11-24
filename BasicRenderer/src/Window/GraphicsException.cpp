#include "../PrecompiledHeaders/stdafx.h"
#include "GraphicsException.h"

namespace dx11
{
// Constructors and Destructor:

	GraphicsException::GraphicsException()
	{
	}

	GraphicsException::GraphicsException(int32 line, const char* file, HRESULT hResult)
		: HrException( line, file, hResult )
	{
	}


// Functions:

	void GraphicsException::Except( int32 line, const char* file, HRESULT hResult )
	{
		GraphicsException graphics_exception( line, file, hResult );

		throw graphics_exception;
	}
}