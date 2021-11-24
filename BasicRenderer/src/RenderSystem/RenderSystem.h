#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "HrException.h"
#include "DeviceRemovedException.h"

namespace dx11
{
	class RenderSystem
	{
	public:

	// Constructors and Destructor:

		RenderSystem( HWND hWnd );
		RenderSystem( const RenderSystem& ) = delete;

		~RenderSystem() = default;

	// Operatprs:

		RenderSystem& operator=(const RenderSystem&) = delete;

	// Functions:

		void EndFrame();

		void ClearBuffer( float32 red, float32 green, float32 blue ) noexcept;

		// TEST
		void DrawTestTriangle()
		{
		// Create a vertex buffer (1 2d triangle at the center of the screen):

			struct Vertex
			{
				float32 x;
				float32 y;
			};

			const Vertex vertices[] =
			{
				{  0.0f,  0.5f },
				{  0.5f, -0.5f },
				{ -0.5f, -0.5f }
			};

			Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;

			D3D11_BUFFER_DESC vertex_buffer_desc = { 0 };

			vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			vertex_buffer_desc.CPUAccessFlags = 0u;
			vertex_buffer_desc.MiscFlags = 0u;
			vertex_buffer_desc.ByteWidth = sizeof( vertices );
			vertex_buffer_desc.StructureByteStride = sizeof( Vertex );

			D3D11_SUBRESOURCE_DATA subresource_data = { 0 };

			subresource_data.pSysMem = vertices;

			HRESULT h_result = (m_pDevice->CreateBuffer(&vertex_buffer_desc, &subresource_data, &pVertexBuffer));

			if ( FAILED( h_result ) )
			{
				m_HrException.Except( __LINE__, __FILE__, h_result );
			}

		// Bind Vertex buffer to pipelines:

			const uint32 stride = sizeof( Vertex );
			const uint32 offset = 0u;

			m_pContext->IASetVertexBuffers( 0u, 1u, &pVertexBuffer, &stride, &offset );

		// InfoException should be used, but class InfoManager required:

			m_pContext->Draw( 3u, 0u );
		}

	private:

	// Exceptions:

		HrException m_HrException;
		DeviceRemovedException m_DeviceRemovedException;

	// Variables:

		Microsoft::WRL::ComPtr<ID3D11Device>           m_pDevice;

		Microsoft::WRL::ComPtr<IDXGISwapChain>         m_pSwapChain;

		Microsoft::WRL::ComPtr<ID3D11DeviceContext>    m_pContext;

		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	};
}

#endif // RENDERSYSTEM_H