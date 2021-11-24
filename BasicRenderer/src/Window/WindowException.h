#ifndef WINDOWEXCEPTION_H
#define WINDOWEXCEPTION_H

#include "../Exception/Exception.h"

namespace dx11
{
	class WindowException : public Exception
	{
	public:

	// Constructors and Destructor:

		WindowException();
		WindowException( int32 line, const char* file, HRESULT hResult ) noexcept;

		~WindowException();

	// Functions:

		void Except( int32 line, const char* file, HRESULT hResult );

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