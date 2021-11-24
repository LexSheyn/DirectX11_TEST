#include "../PrecompiledHeaders/stdafx.h"
#include "HrException.h"

namespace dx11
{
// Constructor:

	HrException::HrException()
		: m_hResult( 0 )
	{
	}

	HrException::HrException(int32 line, const char* file, HRESULT hResult) noexcept
		: Exception( 0, "" ),
		  m_hResult( hResult )
	{
	}


// Functions:

	void HrException::Except(int32 line, const char* file, HRESULT hResult)
	{
		HrException hr_exception( line, file, hResult );
		
		throw hr_exception;
	}


// Accessors:

	const char* HrException::what() const noexcept
	{
		return nullptr;
	}

	const char* HrException::GetType() const noexcept
	{
		return nullptr;
	}

	HRESULT HrException::GetErrorCode() const noexcept
	{
		return E_NOTIMPL;
	}

	std::string HrException::GetErrorString() const noexcept
	{
		return std::string();
	}

	std::string HrException::GetErrorDescription() const noexcept
	{
		return std::string();
	}

}