#include "../PrecompiledHeaders/stdafx.h"
#include "RenderSystem.h"

namespace dx11
{
// Constructors and Destructors:

	RenderSystem::RenderSystem(HWND hWnd)
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

	// HRESULT for checking results of d3d functions:

		HRESULT h_result = 0;

	// Create device and front/back buffers, and swap chain and rendering context:

		if ( FAILED (D3D11CreateDeviceAndSwapChain(nullptr,
			                                       D3D_DRIVER_TYPE_HARDWARE,
			                                       nullptr,
			                                       0u,//D3D11_CREATE_DEVICE_DEBUG,
			                                       nullptr,
			                                       0u,
			                                       D3D11_SDK_VERSION,
			                                       &swap_chain_descriotor,
			                                       &m_pSwapChain,
			                                       &m_pDevice,
			                                       nullptr,
			                                       &m_pContext) ) )
		{
			m_HrException.Except( __LINE__, __FILE__, h_result );
		}

	// Gain access to texture subresource in swap chain (back buffer):

		Microsoft::WRL::ComPtr<ID3D11Resource> pBackBuffer;

		m_pSwapChain->GetBuffer( 0u, __uuidof( ID3D11Texture2D ), &pBackBuffer );

		m_pDevice->CreateRenderTargetView(pBackBuffer.Get(), nullptr, &m_pRenderTargetView);


		pBackBuffer->Release();
	}


// Functions:

	void RenderSystem::EndFrame()
	{
		HRESULT h_result = 0;

		if( FAILED( m_pSwapChain->Present( 1u, 0u ) ) )
		{
			if ( h_result == DXGI_ERROR_DEVICE_REMOVED )
			{
				m_DeviceRemovedException.Except( __LINE__, __FILE__ , m_pDevice->GetDeviceRemovedReason() );
			}
			else
			{
				m_HrException.Except( __LINE__, __FILE__, GetLastError());
			}			
		}
	}

	void RenderSystem::ClearBuffer(float32 red, float32 green, float32 blue) noexcept
	{
		const float color[] = { red, green, blue, 1.0f };

		m_pContext->ClearRenderTargetView( m_pRenderTargetView.Get(), color );
	}

}