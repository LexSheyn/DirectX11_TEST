#include "../PrecompiledHeaders/stdafx.h"
#include "HrException.h"

namespace dx11
{
// Constructors and Destructor:

	HrException::HrException()
		: m_hResult( 0 )
	{
	}

	HrException::HrException(int32 line, const char* file, HRESULT hResult) noexcept
		: Exception( line, file ),
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
		std::ostringstream out_str_stream;

		out_str_stream << this->GetType()
			           << "\n" << "[Error code]: 0x" << std::hex << std::uppercase << this->GetErrorCode()
			           << std::dec << " (" << static_cast<uint64>(this->GetErrorCode()) << ")"
			           << "\n" << "[Error string]: " << this->GetErrorString()
			           << "\n" << "[Description]: " << this->GetErrorDescription()
			           << "\n" << Exception::GetOriginString();

		WhatBuffer = out_str_stream.str();

		return WhatBuffer.c_str();
	}

	const char* HrException::GetType() const noexcept
	{
		return "Render System Exception";
	}

	const HRESULT& HrException::GetErrorCode() const noexcept
	{
		return m_hResult;
	}

	std::string HrException::GetErrorString() const noexcept
	{
		return DXGetErrorStringA( m_hResult );
	}

	std::string HrException::GetErrorDescription() const noexcept
	{
		char buffer[512];

		DXGetErrorDescriptionA( m_hResult, buffer, sizeof( buffer ) );

		return buffer;
	}

}