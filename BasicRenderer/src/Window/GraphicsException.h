#ifndef GRAPHICSEXCEPTION_H
#define GRAPHICSEXCEPTION_H

#include "../Exception/Exception.h"

namespace dx11
{
	class GraphicsException : public Exception
	{
	public:

	// Constructors and Destcutor:

		GraphicsException();
		GraphicsException( int32 line, const char* file );

	// Functions:

		void Except( int32 line, const char* file );

	// Accessors:

		inline const char* GetType() const noexcept override { return "Graphics Exception"; }
	};
}

#endif // GRAPHICSEXCEPTION_H