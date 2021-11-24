#include "../PrecompiledHeaders/stdafx.h"
#include "WindowException.h"

namespace dx11
{
// Constructors and Destructor:

	WindowException::WindowException()
		: m_hResult( 0 )
	{
	}

	WindowException::WindowException( int32 line, const char* file, HRESULT hResult ) noexcept
		: Exception( line, file ),
		  m_hResult( hResult )
	{
	}

	WindowException::~WindowException()
	{
	}


// Functions:

	void WindowException::Except(int32 line, const char* file, HRESULT hResult)
	{
		WindowException window_exception( line, file, hResult );
		
		throw window_exception;
	}

	std::string WindowException::TranslateErrorCode(HRESULT hResult) noexcept
	{
		char* pMessageBuffer = nullptr;

		DWORD nMessageLength = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			                                  nullptr,
			                                  hResult,
			                                  MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
			                                  reinterpret_cast<LPSTR>(&pMessageBuffer),
			                                  0,
			                                  nullptr);

		if ( nMessageLength == 0 )
		{
			return "Unindentified error code";
		}

		std::string error_string = pMessageBuffer;

		LocalFree( pMessageBuffer );

		return error_string;
	}


// Accessors:

	const char* WindowException::what() const noexcept
	{
		std::stringstream out_str_stream;

		out_str_stream << this->GetType()
		               << "\n" << "[Error Code]: "  << this->GetErrorCode()
		               << "\n" << "[Description]: " << this->GetErrorString()
		               << "\n" << Exception::GetOriginString();

		Exception::WhatBuffer = out_str_stream.str();

		return Exception::WhatBuffer.c_str();
	}

	const char* WindowException::GetType() const noexcept
	{
		return "Window Exception";
	}

	const HRESULT& WindowException::GetErrorCode() const noexcept
	{
		return m_hResult;
	}

	std::string WindowException::GetErrorString() const noexcept
	{
		return this->TranslateErrorCode( m_hResult );
	}

}