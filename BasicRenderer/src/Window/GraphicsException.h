#ifndef GRAPHICSEXCEPTION_H
#define GRAPHICSEXCEPTION_H

#include "../RenderSystem/HrException.h"

namespace dx11
{
	class GraphicsException : public HrException
	{
	public:

	// Constructors and Destcutor:

		GraphicsException();
		GraphicsException( int32 line, const char* file, HRESULT hResult );

	// Functions:

		void Except( int32 line, const char* file, HRESULT hResult );

	// Accessors:

		inline const char* GetType() const noexcept override { return "Graphics Exception"; }
	};
}

#endif // GRAPHICSEXCEPTION_H