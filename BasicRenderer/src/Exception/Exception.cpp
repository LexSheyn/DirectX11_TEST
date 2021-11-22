#include "../PrecompiledHeaders/stdafx.h"
#include "Exception.h"

namespace dx11
{
// Constructors and Destructor:

	Exception::Exception( int32 line, const char* file ) noexcept
		: m_Line( line ),
		  m_File( file )
	{
	}

	Exception::~Exception()
	{
	}


// Accessors:

	const char* Exception::what() const noexcept
	{
		std::stringstream out_str_stream;

		out_str_stream << this->GetType()
			   << "\n" << this->GetOriginString();

		WhatBuffer = out_str_stream.str();

		return WhatBuffer.c_str();
	}

	const char* Exception::GetType() const noexcept
	{
		return "Base Exception";
	}

	const int32& Exception::GetLine() const noexcept
	{
		return m_Line;
	}

	const std::string& Exception::GetFile() const noexcept
	{
		return m_File;
	}

	std::string Exception::GetOriginString() const noexcept
	{
		std::stringstream out_str_stream;

		out_str_stream << "[File]: " << m_File
			   << "\n" << "[Line]: " << m_Line;

		return out_str_stream.str();
	}	

}