#include "../../../PrecompiledHeaders/stdafx.h"
#include "Bindable.h"

namespace dx11
{
// Accessors:


	ID3D11DeviceContext* Bindable::GetContext(RenderSystem& renderSystem) noexcept
	{
		return renderSystem.m_pContext.Get();
	}

	ID3D11Device* Bindable::GetDevice(RenderSystem& renderSystem) noexcept
	{
		return renderSystem.m_pDevice.Get();
	}

//	DxgiInfoManager& Bindable::GetInfoManager(Graphics& gfx) noexcept(!IS_DEBUG)
//	{
//	#ifndef NDEBUG
//
//		return gfx.infoManager;
//
//	#else
//
//		throw std::logic_error("YouFuckedUp! (tried to access gfx.infoManager in Release config)");
//
//	#endif
//	}

}