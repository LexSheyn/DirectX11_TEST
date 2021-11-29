#include "../../../../PrecompiledHeaders/stdafx.h"
#include "Pyramid.h"

namespace dx11
{
// Constructors and Destructor:


	Pyramid::Pyramid(RenderSystem& renderSystem,
		              std::mt19937& randomizer, 
		              std::uniform_real_distribution<float32>& adist, 
		              std::uniform_real_distribution<float32>& ddist, 
		              std::uniform_real_distribution<float32>& odist, 
		              std::uniform_real_distribution<float32>& rdist  )
		: radius( rdist( randomizer ) ),
	      droll( ddist( randomizer ) ),
	      dpitch( ddist( randomizer ) ),
	      dyaw( ddist( randomizer ) ),
	      dphi( odist( randomizer ) ),
	      dtheta( odist( randomizer ) ),
	      dchi( odist( randomizer ) ),
	      chi( adist( randomizer ) ),
	      theta( adist( randomizer ) ),
	      phi( adist( randomizer ) )
	{
		if ( !IsStaticInitialized() )
		{
			struct Vertex
			{
				DirectX::XMFLOAT3 position;
				
				struct
				{
					uint8 r;
					uint8 g;
					uint8 b;
					uint8 a;
				} color;
			};

			auto model = Cone::MakeTesselated<Vertex>( 4 );

		// Set Vertex colors for mesh:
			
			model.vertices[0].color = { 255, 255,   0 };
			model.vertices[1].color = { 255, 255,   0 };
			model.vertices[2].color = { 255, 255,   0 };
			model.vertices[3].color = { 255, 255,   0 };
			model.vertices[4].color = { 255, 255,  80 };
			model.vertices[5].color = { 255,  10,   0 };

		// Deform mesh lineraly:

			model.Transform( DirectX::XMMatrixScaling( 1.0f, 1.0f, 0.7f ) );

			AddStaticBind( std::make_unique<VertexBuffer>( renderSystem, model.vertices ) );

			auto pVertexShader = std::make_unique<VertexShader>( renderSystem, L"../Resources/CompiledShaders/ColorBlendVertexShader.cso" );

			auto pVertexShaderBytecode = pVertexShader->GetBytecode();

			AddStaticBind( std::move( pVertexShader ) );

			AddStaticBind( std::make_unique<PixelShader>( renderSystem, L"../Resources/CompiledShaders/ColorBlendPixelShader.cso" ) );

			AddStaticIndexBuffer( std::make_unique<IndexBuffer>( renderSystem, model.indices ) );

			const std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc =
			{
				{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0 , D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "Color"   , 0, DXGI_FORMAT_R8G8B8A8_UNORM , 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			AddStaticBind( std::make_unique<InputLayout>( renderSystem, input_element_desc, pVertexShaderBytecode ) );

			AddStaticBind( std::make_unique<Topology>( renderSystem, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
		}
		else
		{
			SetIndexFromStatic();
		}

		AddBind( std::make_unique<MatrixTransformer>( renderSystem, *this ) );
	}


// Functions:

	void Pyramid::Update(const float& dt) noexcept
	{
		roll  += droll  * dt;
		pitch += dpitch * dt;
		yaw   += dyaw   * dt;
		theta += dtheta * dt;
		phi   += dphi   * dt;
		chi   += dchi   * dt;
	}


// Accessors:

	DirectX::XMMATRIX Pyramid::GetTransformXM() const noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll)
			 * DirectX::XMMatrixTranslation(radius, 0.0f, 0.0f)
			 * DirectX::XMMatrixRotationRollPitchYaw(theta, phi, chi)
			 * DirectX::XMMatrixTranslation(0.0f, 0.0f, 20.0f);
	}

}