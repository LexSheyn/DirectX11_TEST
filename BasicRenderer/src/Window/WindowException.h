#ifndef WINDOWEXCEPTION_H
#define WINDOWEXCEPTION_H

#include "../Exception/Exception.h"

// Exception setup.
#define SET_WINDOW_EXCEPTION( hResult ) WindowException exception( __LINE__, __FILE__, hResult );

// Exception throw.
#define GET_WINDOW_EXCEPTION throw exception;

// Exception with parameters.
#define WINDOW_EXCEPT( hResult ) SET_WINDOW_EXCEPTION( hResult ) GET_WINDOW_EXCEPTION

// Exception with default Win32 last error code.
#define WINDOW_EXCEPT_LAST_ERROR() SET_WINDOW_EXCEPTION( GetLastError() ) GET_WINDOW_EXCEPTION

namespace dx11
{
	class WindowException : public Exception
	{
	public:

	// Constructors and Destructor:

		WindowException( int32 line, const char* file, HRESULT hResult ) noexcept;

		~WindowException();

	// Functions:

		static std::string TranslateErrorCode( HRESULT hResult ) noexcept;

	// Accessors:

		const char*    what()           const noexcept override;
					   
		const char*    GetType()        const noexcept override;
								     
		const HRESULT& GetErrorCode()   const noexcept;

		   std::string GetErrorString() const noexcept;

	private:

	// Variables:

		HRESULT m_hResult;
	};
}

#endif // WINDOWEXCEPTION_H