#include "../PrecompiledHeaders/stdafx.h"
#include "DeviceRemovedException.h"

namespace dx11
{
// Accessors:

    const char* DeviceRemovedException::GetType() const noexcept
    {
        return "Device Removed Exception (DXGI_ERROR_DEVICE_REMOVED)";
    }

}