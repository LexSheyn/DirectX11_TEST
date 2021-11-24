#ifndef HREXCEPTION_H
#define HREXCEPTION_H

#include "../Exception/Exception.h"

// Exception setup.
#define SET_GFX_EXCEPTION_HRESULT( hResult ) HrException hr_exception( __LINE__, __FILE__, hResult );

// Exception throw.
#define GET_GFX_EXCEPTION_HRESULT throw hr_exception;

#define GFX_EXCEPT_HRESULT_FAILED( hResultCall ) if( FAILED( h_result = (hResultCall) ) ) SET_GFX_EXCEPTION_HRESULT( h_result ) GET_GFX_EXCEPTION_HRESULT

namespace dx11
{
	class HrException : public Exception
	{
	public:

	// Constructors and Destructor:

		HrException();
		HrException( int32 line, const char* file, HRESULT hResult ) noexcept;

	// Functions:

		void Except( int32 line, const char* file, HRESULT hResult );

	// Accessors:

		const    char* what()                const noexcept override;

		const    char* GetType()             const noexcept override;

		const HRESULT& GetErrorCode()        const noexcept;

		   std::string GetErrorString()      const noexcept;

		   std::string GetErrorDescription() const noexcept;

	private:

	// Variables:

		HRESULT m_hResult;
	};
}

#endif // HREXCEPTION_H