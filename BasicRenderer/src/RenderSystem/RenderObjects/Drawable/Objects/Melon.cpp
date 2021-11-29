#include "../../../../PrecompiledHeaders/stdafx.h"
#include "Melon.h"

namespace dx11
{
// Constructors and Destructor:

	Melon::Melon(RenderSystem& renderSystem,
		          std::mt19937& randomizer, 
		          std::uniform_real_distribution<float32>& adist, 
		          std::uniform_real_distribution<float32>& ddist, 
		          std::uniform_real_distribution<float32>& odist, 
		          std::uniform_real_distribution<float32>& rdist, 
		          std::uniform_int_distribution<int32>& longdist, 
		          std::uniform_int_distribution<int32>& latdist  )
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
			auto pVertexShader = std::make_unique<VertexShader>( renderSystem, L"../Resources/CompiledShaders/ColorIndexVertexShader.cso" );
			auto pVertexShaderBytecode = pVertexShader->GetBytecode();

			AddStaticBind( std::move( pVertexShader ) );

			AddStaticBind( std::make_unique<PixelShader>( renderSystem, L"../Resources/CompiledShaders/ColorIndexPixelShader.cso" ) );

			struct PixelShaderConstants
			{
				struct
				{
					float32 r;
					float32 g;
					float32 b;
					float32 a;
				} face_colors[8];
			};

			const PixelShaderConstants constant_buffer2
			{
				{
					{ 1.0f, 1.0f, 1.0f },
					{ 1.0f, 0.0f, 0.0f },
					{ 0.0f, 1.0f, 0.0f },
					{ 1.0f, 1.0f, 0.0f },
					{ 0.0f, 0.0f, 1.0f },
					{ 1.0f, 0.0f, 1.0f },
					{ 0.0f, 1.0f, 1.0f },
					{ 0.0f, 0.0f, 0.0f }
				}
			};

			AddStaticBind( std::make_unique<PixelConstantBuffer<PixelShaderConstants>>( renderSystem, constant_buffer2 ) );

			const std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc =
			{
				{ "Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			AddStaticBind( std::make_unique<InputLayout>( renderSystem, input_element_desc, pVertexShaderBytecode ) );

			AddStaticBind( std::make_unique<Topology>( renderSystem, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST ) );
		}

		struct Vertex
		{
			DirectX::XMFLOAT3 position;
		};

		auto model = Sphere::MakeTesselated<Vertex>( latdist( randomizer ), longdist( randomizer ) );

	// Deform vertices of model by linear transformation:

		model.Transform( DirectX::XMMatrixScaling( 1.0f, 1.0f, 1.2f ) );

		AddBind( std::make_unique<VertexBuffer>( renderSystem, model.vertices ) );

		AddIndexBuffer( std::make_unique<IndexBuffer>( renderSystem, model.indices ) );

		AddBind( std::make_unique<MatrixTransformer>( renderSystem, *this ) );
	}


// Functions:

	void Melon::Update(const float& dt) noexcept
	{
		roll  += droll  * dt;
		pitch += dpitch * dt;
		yaw   += dyaw   * dt;
		theta += dtheta * dt;
		phi   += dphi   * dt;
		chi   += dchi   * dt;
	}


// Accessors:

	DirectX::XMMATRIX Melon::GetTransformXM() const noexcept
	{
		return DirectX::XMMatrixRotationRollPitchYaw( pitch, yaw, roll )
			 * DirectX::XMMatrixTranslation( radius, 0.0f, 0.0f )
		     * DirectX::XMMatrixRotationRollPitchYaw( theta, phi, chi )
			 * DirectX::XMMatrixTranslation( 0.0f, 0.0f, 20.0f );
	}

}