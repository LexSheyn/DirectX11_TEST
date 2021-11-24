#include "../PrecompiledHeaders/stdafx.h"
#include "DeviceRemovedException.h"

namespace dx11
{
// Constructors and Destructor:

    DeviceRemovedException::DeviceRemovedException()
        : m_hResult( 0 )
    {
    }

    DeviceRemovedException::DeviceRemovedException(int32 line, const char* file, HRESULT hResult)
        : HrException( line, file, hResult ),
          m_hResult( hResult )
    {
    }


// Functions:

    void DeviceRemovedException::Except(int32 line, const char* file, HRESULT hResult)
    {
        DeviceRemovedException device_removed_exception( line, file, hResult );

        throw device_removed_exception;
    }


// Accessors:

    const char* DeviceRemovedException::GetType() const noexcept
    {
        return "Device Removed Exception (DXGI_ERROR_DEVICE_REMOVED)";
    }

}