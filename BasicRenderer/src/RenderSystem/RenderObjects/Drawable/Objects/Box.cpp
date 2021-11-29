#include "../../../../PrecompiledHeaders/stdafx.h"
#include "Box.h"

namespace dx11
{
// Constructors and Destructor:

	Box::Box(RenderSystem& renderSystem, 
		     std::mt19937& rng, 
		     std::uniform_real_distribution<float32>& adist, 
		     std::uniform_real_distribution<float32>& ddist, 
		     std::uniform_real_distribution<float32>& odist, 
		     std::uniform_real_distribution<float32>& rdist)
		: radius( rdist( rng) ),
		  droll( ddist( rng) ),
		  dpitch( ddist( rng) ),
		  dyaw( ddist( rng) ),
		  dphi( odist( rng) ),
		  dtheta( odist( rng) ),
		  dchi( odist( rng) ),
		  chi( adist( rng) ),
		  theta( adist( rng) ),
		  phi( adist( rng) )
	{
		if ( !IsStaticInitialized() )
		{
			struct Vertex
			{
				DirectX::XMFLOAT3 position;
			};

			auto model = Sphere::Make<Vertex>();
		//	auto model = Prism::Make<Vertex>();
		//	auto model = Cube::Make<Vertex>();

			model.Transform( DirectX::XMMatrixScaling( 1.0f, 1.0f, 1.0f ) );

			AddStaticBind( std::make_unique<VertexBuffer>( renderSystem, model.vertices ) );

			auto pVertexShader = std::make_unique<VertexShader>(renderSystem, L"../Resources/CompiledShaders/VertexShader.cso");

			auto pVertexShaderByteCode = pVertexShader->GetBytecode();

			AddStaticBind(std::move(pVertexShader));

			AddStaticBind(std::make_unique<PixelShader>(renderSystem, L"../Resources/CompiledShaders/PixelShader.cso"));

			AddStaticIndexBuffer( std::make_unique<IndexBuffer>( renderSystem, model.indices ) );

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
					{ 1.0f, 0.0f, 1.0f, 1.0f },
					{ 1.0f, 0.0f, 0.0f, 1.0f },
					{ 0.0f, 1.0f, 0.0f, 1.0f },
					{ 0.0f, 0.0f, 1.0f, 1.0f },
					{ 1.0f, 1.0f, 0.0f, 1.0f },
					{ 0.0f, 1.0f, 1.0f, 1.0f },
				}
			};

			AddStaticBind(std::make_unique<PixelConstantBuffer<ConstantBuffer2>>(renderSystem, constant_buffer2));

			const std::vector<D3D11_INPUT_ELEMENT_DESC> input_element_desc =
			{
				{ "Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
			};

			AddStaticBind(std::make_unique<InputLayout>(renderSystem, input_element_desc, pVertexShaderByteCode));

			AddStaticBind(std::make_unique<Topology>(renderSystem, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST));
		}
		else
		{
			SetIndexFromStatic();
		}

		AddBind(std::make_unique<MatrixTransformer>( renderSystem, *this) );
	}
	
	void Box::Update(const float32& dt) noexcept
	{
		roll  += droll  * dt;
		pitch += dpitch * dt;
		yaw   += dyaw   * dt;
		theta += dtheta * dt;
		phi   += dphi   * dt;
		chi   += dchi   * dt;
	}
	
	DirectX::XMMATRIX Box::GetTransformXM() const noexcept
	{
	//	return DirectX::XMLoadFloat3x3( &m_TransformationMatrix ) 
	//		 * DirectX::XMMatrixRotationRollPitchYaw( pitch, yaw, roll )
	//		 * DirectX::XMMatrixTranslation( radius, 0.0f, 0.0f )
	//		 * DirectX::XMMatrixRotationRollPitchYaw( theta, phi, chi )
	//		 * DirectX::XMMatrixTranslation( 0.0f, 0.0f, 20.0f );

		return DirectX::XMMatrixRotationRollPitchYaw( pitch, yaw, roll )
			 * DirectX::XMMatrixTranslation( radius, 0.0f, 0.0f )
			 * DirectX::XMMatrixRotationRollPitchYaw( theta, phi, chi )
			 * DirectX::XMMatrixTranslation( 0.0f, 0.0f, 20.0f );
	}
}