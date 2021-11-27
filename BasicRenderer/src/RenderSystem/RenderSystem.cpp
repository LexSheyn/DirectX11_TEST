#include "../PrecompiledHeaders/stdafx.h"
#include "RenderSystem.h"

namespace dx11
{
// Constructors and Destructors:

	RenderSystem::RenderSystem(HWND hWnd)
	{
	// Projection Matrix initialization:

		m_ProjectionMatrix = {};

	// Create spaw chain descriptor:

		DXGI_SWAP_CHAIN_DESC swap_chain_descriotor = { 0 };

		swap_chain_descriotor.BufferDesc.Width  = 0u;
		swap_chain_descriotor.BufferDesc.Height = 0u;
		swap_chain_descriotor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swap_chain_descriotor.BufferDesc.RefreshRate.Numerator   = 0u;
		swap_chain_descriotor.BufferDesc.RefreshRate.Denominator = 0u;
		swap_chain_descriotor.BufferDesc.Scaling          = DXGI_MODE_SCALING_UNSPECIFIED;
		swap_chain_descriotor.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swap_chain_descriotor.SampleDesc.Count   = 1u;
		swap_chain_descriotor.SampleDesc.Quality = 0u;
		swap_chain_descriotor.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swap_chain_descriotor.BufferCount  = 1u;
		swap_chain_descriotor.OutputWindow = hWnd;
		swap_chain_descriotor.Windowed     = TRUE;
		swap_chain_descriotor.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
		swap_chain_descriotor.Flags        = 0u;

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

	//	pBackBuffer->Release();

	// Create depth stencil state:

		D3D11_DEPTH_STENCIL_DESC depth_stencil_desc = {};

		depth_stencil_desc.DepthEnable    = TRUE;
		depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		depth_stencil_desc.DepthFunc      = D3D11_COMPARISON_LESS;

		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDepthStencilState;

		m_pDevice->CreateDepthStencilState( &depth_stencil_desc, &pDepthStencilState );

	// Bind depth state:

		m_pContext->OMSetDepthStencilState( pDepthStencilState.Get(), 1u );

	// Create depth stencil texture:

		Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencilTexture;

		D3D11_TEXTURE2D_DESC depth_stencil_tex_desc = {};

		depth_stencil_tex_desc.Width     = 1050u;
		depth_stencil_tex_desc.Height    = 450u;
		depth_stencil_tex_desc.MipLevels = 1u;
		depth_stencil_tex_desc.ArraySize = 1u;
		depth_stencil_tex_desc.Format    = DXGI_FORMAT_D32_FLOAT;
		depth_stencil_tex_desc.SampleDesc.Count   = 1u;
		depth_stencil_tex_desc.SampleDesc.Quality = 0u;
		depth_stencil_tex_desc.Usage     = D3D11_USAGE_DEFAULT;
		depth_stencil_tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

		m_pDevice->CreateTexture2D( &depth_stencil_tex_desc, nullptr, &pDepthStencilTexture );

	// Create view of depth stencil texture:

		D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc = {};

		depth_stencil_view_desc.Format             = DXGI_FORMAT_D32_FLOAT;
		depth_stencil_view_desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2D;
		depth_stencil_view_desc.Texture2D.MipSlice = 0u;

		m_pDevice->CreateDepthStencilView( pDepthStencilTexture.Get(), &depth_stencil_view_desc, &m_pDepthStencilView );

	// Bind depth stencil view to OM:

		m_pContext->OMSetRenderTargets( 1u, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get() );

	// Configure viewport:

		D3D11_VIEWPORT viewport = {};

		viewport.Width    = 1050.0f; 
		viewport.Height   = 450.0f; 
		viewport.MinDepth = 0.0f; 
		viewport.MaxDepth = 1.0f; 
		viewport.TopLeftX = 0.0f; 
		viewport.TopLeftY = 0.0f;

		m_pContext->RSSetViewports( 1u, &viewport );
	}


// Functions:

	void RenderSystem::EndFrame()
	{
		HRESULT h_result = m_pSwapChain->Present(1u, 0u);

		if( FAILED( h_result ) )
		{
			if ( h_result == DXGI_ERROR_DEVICE_REMOVED )
			{
				m_DeviceRemovedException.Except( __LINE__, __FILE__ , m_pDevice->GetDeviceRemovedReason() );
			}
			else
			{
				m_HrException.Except( __LINE__, __FILE__, h_result);
			}			
		}
	}

	void RenderSystem::ClearBuffer(float32 red, float32 green, float32 blue) noexcept
	{
		const float color[] = { red, green, blue, 1.0f };

		m_pContext->ClearRenderTargetView( m_pRenderTargetView.Get(), color );
		m_pContext->ClearDepthStencilView( m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u );
	}

	void RenderSystem::DrawIndexed(uint32 count) noexcept
	{
		m_pContext->DrawIndexed( count, 0u, 0u );
	}


// Accessors:

	const DirectX::XMMATRIX& RenderSystem::GetProjection() const noexcept
	{
		return m_ProjectionMatrix;
	}


// Modifiers:

	void RenderSystem::SetProjection(DirectX::FXMMATRIX projection) noexcept
	{
		m_ProjectionMatrix = projection;
	}

}