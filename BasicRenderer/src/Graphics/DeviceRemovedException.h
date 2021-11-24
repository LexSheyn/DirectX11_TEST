#ifndef DEVICEREMOVEDEXCEPTION_H
#define DEVICEREMOVEDEXCEPTION_H

#include "HrException.h"

namespace dx11
{
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;

	public:

	// Constructors and Destructor:

		DeviceRemovedException();
		DeviceRemovedException( int32 line, const char* file, HRESULT hResult );

	// Functions:

		void Except( int32 line, const char* file, HRESULT hResult );

	// Accessors:

		const char* GetType() const noexcept override;

	private:

	// Variables:

		HRESULT m_hResult;
	};
}

#endif // DEVICEREMOVEDEXCEPTION_H