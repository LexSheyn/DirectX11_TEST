#include "../PrecompiledHeaders/stdafx.h"
#include "InfoException.h"

namespace dx11
{
// Constructor:

	InfoException::InfoException()
	{
	}

	InfoException::InfoException(int32 line, const char* file, std::vector<std::string> infoMessages)
		: Exception( line, file )
	{
	// Join all info messages with newlines into a single string:

		for ( const auto& message : infoMessages )
		{
			m_Info += message;
			m_Info.push_back( '\n' );
		}

	// Remove final newline if exitst:

		if ( !m_Info.empty() )
		{
			m_Info.pop_back();
		}
	}


// Functions:

	void InfoException::Except(int32 line, const char* file, std::vector<std::string> infoMessages)
	{
		InfoException info_exception( line, file, infoMessages );

		throw info_exception;
	}


// Accessors:

	const char* InfoException::what() const noexcept
	{
		std::ostringstream out_str_stream;

		out_str_stream << this->GetType()
			           << "\n" << "\n[Error info]:\n" << this->GetErrorInfo() << "\n" << "\n";

		out_str_stream << Exception::GetOriginString();

		WhatBuffer = out_str_stream.str();

		return WhatBuffer.c_str();
	}

	const char* InfoException::GetType() const noexcept
	{
		return "Info Exception";
	}

	std::string InfoException::GetErrorInfo() const noexcept
	{
		return m_Info;
	}
}