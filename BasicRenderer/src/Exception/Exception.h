#ifndef EXCEPTION_H
#define EXCEPTION_H

namespace dx11
{
	class Exception : public std::exception
	{
	public:

	// Constructors and Destructor:

		Exception();
		Exception( int32 line, const char* file ) noexcept;

		~Exception();

	// Accessors:

	//	inline  const char* What()            const noexcept { return this->what(); }

		        const char* what()            const noexcept override;

		virtual const char* GetType()         const noexcept;
									          
		 const       int32& GetLine()         const noexcept;
		 
		 const std::string& GetFile()         const noexcept;
		 
		       std::string  GetOriginString() const noexcept;

	protected:

		mutable std::string WhatBuffer;

	private:

	// Private Overriden Accessors:

	//	const char* what() const noexcept override;

	// Variables:

		     int32  m_Line;

		std::string m_File;
	};
}

#endif // EXCEPTION_H