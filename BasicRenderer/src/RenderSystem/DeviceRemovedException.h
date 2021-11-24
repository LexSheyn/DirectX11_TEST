#ifndef DEVICEREMOVEDEXCEPTION_H
#define DEVICEREMOVEDEXCEPTION_H

#include "HrException.h"

namespace dx11
{
	class DeviceRemovedException : public HrException
	{
		using HrException::HrException;

	public:

	// Accessors:

		const char* GetType() const noexcept override;

	private:

	// Variables:

		std::string m_Reason;
	};
}

#endif // DEVICEREMOVEDEXCEPTION_H