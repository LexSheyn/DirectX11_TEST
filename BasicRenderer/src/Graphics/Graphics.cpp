#include "../PrecompiledHeaders/stdafx.h"
#include "Graphics.h"

namespace dx11
{
// Constructors and Destructors:

	Graphics::Graphics(HWND hWnd)
	{
	// Create spaw chain descriptor:

		DXGI_SWAP_CHAIN_DESC swap_chain_descriotor = { 0 };

		swap_chain_descriotor.BufferDesc.Width = 0u;
		swap_chain_descriotor.BufferDesc.Height = 0u;
		swap_chain_descriotor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swap_chain_descriotor.BufferDesc.RefreshRate.Numerator = 0u;
		swap_chain_descriotor.BufferDesc.RefreshRate.Denominator = 0u;
		swap_chain_descriotor.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_descriotor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_descriotor.SampleDesc.Count = 1u;
		swap_chain_descriotor.SampleDesc.Quality = 0u;
		swap_chain_descriotor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_descriotor.BufferCount = 1u;
		swap_chain_descriotor.OutputWindow = hWnd;
		swap_chain_descriotor.Windowed = TRUE;
		swap_chain_descriotor.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_descriotor.Flags = 0u;

	// Create device and front/back buffers, and swap chain and rendering context:

		D3D11CreateDeviceAndSwapChain(nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			0u,
			nullptr,
			0u,
			D3D11_SDK_VERSION,
			&swap_chain_descriotor,
			&m_pSwapChain,
			&m_pDevice,
			nullptr,
			&m_pContext);
	}

	Graphics::~Graphics()
	{
		if (m_pDevice != nullptr)
		{
			m_pDevice->Release();
		}

		if (m_pSwapChain != nullptr)
		{
			m_pSwapChain->Release();
		}
		
		if (m_pContext != nullptr)
		{
			m_pContext->Release();
		}		
	}

}