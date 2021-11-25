#ifndef HREXCEPTION_H
#define HREXCEPTION_H

#include "../Exception/Exception.h"

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
		std::string info;
	};
}

#endif // HREXCEPTION_H