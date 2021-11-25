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
				struct
				{
					float32 x;
					float32 y;
				} position;
				
				struct
				{
					uint8 r;
					uint8 g;
					uint8 b;
					uint8 a;
				} color;				
			};

			Vertex vertices[] =
			{
				{  0.0f,  0.5f, 255, 000, 000, 255 },
				{  0.5f, -0.5f, 000, 255, 000, 255 },
				{ -0.5f, -0.5f, 000, 000, 255, 255 },
				{ -0.3f,  0.3f, 000, 255, 000, 255 },
				{  0.3f,  0.3f, 000, 000, 255, 255 },
				{  0.0f, -0.8f, 255, 000, 000, 255 }
			};

			Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;

			D3D11_BUFFER_DESC vertex_buffer_desc = {};

			vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			vertex_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			vertex_buffer_desc.CPUAccessFlags = 0u;
			vertex_buffer_desc.MiscFlags = 0u;
			vertex_buffer_desc.ByteWidth = sizeof( vertices );
			vertex_buffer_desc.StructureByteStride = sizeof( Vertex );

			D3D11_SUBRESOURCE_DATA subresource_data = {};

			subresource_data.pSysMem = vertices;

			HRESULT h_result = (m_pDevice->CreateBuffer(&vertex_buffer_desc, &subresource_data, &pVertexBuffer));

			if ( FAILED( h_result ) )
			{
				m_HrException.Except( __LINE__, __FILE__, h_result );
			}

		// Bind Vertex buffer to pipelines:

			const uint32 stride = sizeof( Vertex );
			const uint32 offset = 0u;

			m_pContext->IASetVertexBuffers( 0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset );

		// Create Index buffer:

			const uint16 indices[] =
			{
				0, 1, 2,
				0, 2, 3,
				0, 4, 1,
				2, 1, 5
			};

			Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;

			D3D11_BUFFER_DESC index_buffer_desc = {};

			index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			index_buffer_desc.CPUAccessFlags = 0u;
			index_buffer_desc.MiscFlags = 0u;
			index_buffer_desc.ByteWidth = sizeof( vertices );
			index_buffer_desc.StructureByteStride = sizeof( Vertex );

			D3D11_SUBRESOURCE_DATA index_subresource_data = {};

			index_subresource_data.pSysMem = indices;

			m_pDevice->CreateBuffer( &index_buffer_desc, &index_subresource_data, &pIndexBuffer);

		// Bind Index buffer to pipelines:

			m_pContext->IASetIndexBuffer( pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u );

		// Create Pixel Shader:

			Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

			Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
			D3DReadFileToBlob( L"../Resources/CompiledShaders/PixelShader.cso", &pBlob );
			m_pDevice->CreatePixelShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);

		// Bind Pixel Shader:

			m_pContext->PSSetShader( pPixelShader.Get(), nullptr, 0u );

		// Create Vertex Shader:

			Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
			D3DReadFileToBlob( L"../Resources/CompiledShaders/VertexShader.cso", &pBlob );
			m_pDevice->CreateVertexShader( pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader );

		// Bind Vertex Shader:

			m_pContext->VSSetShader( pVertexShader.Get(), nullptr, 0u );		

		// Input (Vertex) layout (2d position only):

			Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

			const D3D11_INPUT_ELEMENT_DESC input_element_desc[] =
			{
				{ "Position", 0, DXGI_FORMAT_R32G32_FLOAT , 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "Color"   , 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 8u, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			m_pDevice->CreateInputLayout( input_element_desc, 
				                          static_cast<uint32>( std::size( input_element_desc ) ), 
				                          pBlob->GetBufferPointer(),
				                          pBlob->GetBufferSize(),
				                          &pInputLayout );

		// Bind Input (Vertex) layout:

			m_pContext->IASetInputLayout( pInputLayout.Get() );

		// Bind Render Target View:

			m_pContext->OMSetRenderTargets( 1u, m_pRenderTargetView.GetAddressOf(), nullptr );

		// Set primitive topology to triangle list (groups 3 vertices):

			m_pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		// Configure Viewport:

			D3D11_VIEWPORT viewport;

			viewport.Width    = 525.0f;
			viewport.Height   = 225.0f;
			viewport.MinDepth = 0.0f;
			viewport.MaxDepth = 1.0f;
			viewport.TopLeftX = 0.0f;
			viewport.TopLeftY = 0.0f;

			m_pContext->RSSetViewports( 1u, &viewport );

		// InfoException should be used, but class InfoManager required:

			m_pContext->DrawIndexed( static_cast<uint32>(std::size( indices )), 0u, 0u );
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