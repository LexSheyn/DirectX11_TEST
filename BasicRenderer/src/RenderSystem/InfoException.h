#ifndef INFOEXCEPTION_H
#define INFOEXCEPTION_H

#include "../Exception/Exception.h"

namespace dx11
{
	class InfoException : public Exception
	{
	public:

	// Constructor:

		InfoException();
		InfoException( int32 line, const char* file, std::vector<std::string> infoMessages );

	// Functions:

		void Except( int32 line, const char* file, std::vector<std::string> infoMessages );

	// Accessors:

		const char* what() const noexcept override;

		const char* GetType() const noexcept override;

		std::string GetErrorInfo() const noexcept;

	private:

	// Variables:

		std::string m_Info;
	};
}

#endif // INFOEXCEPTION_H