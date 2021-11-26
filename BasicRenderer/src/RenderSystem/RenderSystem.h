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
		void DrawTestTriangle( float32 angle, float32 x, float32 y )
		{
			// TEST:
			DirectX::XMVECTOR vector = DirectX::XMVectorSet( 3.0f, 3.0f, 0.0f, 0.0f );

			auto result = DirectX::XMVector3Transform( vector, DirectX::XMMatrixScaling( 1.5f, 0.0f, 0.0f ) );

			auto vx = DirectX::XMVectorGetX( result );

		// Create a vertex buffer (1 2d triangle at the center of the screen):

			struct Vertex
			{
				struct
				{
					float32 x;
					float32 y;
					float32 z;
				} position;	
			};

			Vertex vertices[] =
			{
				{ -1.0f, -1.0f, -1.0f },
				{  1.0f, -1.0f, -1.0f },
				{ -1.0f,  1.0f, -1.0f },
				{  1.0f,  1.0f, -1.0f },
				{ -1.0f, -1.0f,  1.0f },
				{  1.0f, -1.0f,  1.0f },
				{ -1.0f,  1.0f,  1.0f },
				{  1.0f,  1.0f,  1.0f }
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
				0, 2, 1,    2, 3, 1,

				1, 3, 5,    3, 7, 5,

				2, 6, 3,    3, 6, 7,

				4, 5, 7,    4, 7, 6,

				0, 4, 2,    2, 4, 6,

				0, 1, 4,    1, 5, 4
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

		// Create constant buffer for transfirmation natrix:
			
			struct ConstantBuffer
			{
				DirectX::XMMATRIX transform;
			};

			const ConstantBuffer constant_buffer =
			{
				{
					DirectX::XMMatrixTranspose( DirectX::XMMatrixRotationX( angle / 2.0f ) 
					                          * DirectX::XMMatrixRotationY( angle ) 
						                      * DirectX::XMMatrixRotationZ( angle / 2.0f ) 
						                      * DirectX::XMMatrixScaling( 9.0f / 21.0f, 1.0f, 1.0f )
				//	                          * DirectX::XMMatrixTranslation( x, y, 5.0f ) 
					                          * DirectX::XMMatrixTranslation( x, y, y + 5.0f ) 
						                      * DirectX::XMMatrixPerspectiveLH( 1.0f, 1.0f, 0.5f, 10.f ) )
				}
			};

			Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;

			D3D11_BUFFER_DESC constant_buffer_desc = {};

			constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constant_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
			constant_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			constant_buffer_desc.MiscFlags = 0u;
			constant_buffer_desc.ByteWidth = sizeof( constant_buffer );
			constant_buffer_desc.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA const_buf_subresource_data = {};

			const_buf_subresource_data.pSysMem = &constant_buffer;

			m_pDevice->CreateBuffer( &constant_buffer_desc, &const_buf_subresource_data, &pConstantBuffer );

		// Bind ConstantBuffer to vertex shader:

			m_pContext->VSSetConstantBuffers( 0u, 1u, pConstantBuffer.GetAddressOf() );

			struct ConstantBuffer2
			{
				struct
				{
					float32 r;
					float32 g;
					float32 b;
					float32 a;
				} face_colors[6];
			};

			const ConstantBuffer2 constant_buffer2 =
			{
				{
					{ 1.0f, 0.0f, 0.0f, 1.0f },
					{ 1.0f, 0.0f, 1.0f, 1.0f },
					{ 1.0f, 1.0f, 0.0f, 1.0f },
					{ 0.0f, 1.0f, 0.0f, 1.0f },
					{ 0.0f, 1.0f, 1.0f, 1.0f },
					{ 0.0f, 0.0f, 1.0f, 1.0f },
				}
			};

			Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer2;

			D3D11_BUFFER_DESC constant_buffer_desc2 = {};

			constant_buffer_desc2.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constant_buffer_desc2.Usage = D3D11_USAGE_DEFAULT;
			constant_buffer_desc2.CPUAccessFlags = 0u;
			constant_buffer_desc2.MiscFlags = 0u;
			constant_buffer_desc2.ByteWidth = sizeof( constant_buffer2 );
			constant_buffer_desc2.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA const_buf_subresource_data2 = {};

			const_buf_subresource_data2.pSysMem = &constant_buffer2;

			m_pDevice->CreateBuffer( &constant_buffer_desc2, &const_buf_subresource_data2, &pConstantBuffer2 );

			m_pContext->PSSetConstantBuffers( 0u, 1u, pConstantBuffer2.GetAddressOf() );

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
				{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			m_pDevice->CreateInputLayout( input_element_desc, 
				                          static_cast<uint32>( std::size( input_element_desc ) ), 
				                          pBlob->GetBufferPointer(),
				                          pBlob->GetBufferSize(),
				                          &pInputLayout );

		// Bind Input (Vertex) layout:

			m_pContext->IASetInputLayout( pInputLayout.Get() );

		// Bind Render Target View:

		//	m_pContext->OMSetRenderTargets( 1u, m_pRenderTargetView.GetAddressOf(), nullptr );

		// Set primitive topology to triangle list (groups 3 vertices):

			m_pContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

		// Configure Viewport:

			D3D11_VIEWPORT viewport;

			viewport.Width    = 1050.0f;
			viewport.Height   = 450.0f;
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

		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	};
}

#endif // RENDERSYSTEM_H