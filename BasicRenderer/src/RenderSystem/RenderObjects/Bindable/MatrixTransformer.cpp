#include "../../../PrecompiledHeaders/stdafx.h"
#include "MatrixTransformer.h"

namespace dx11
{
// Constructors and Destructor:

	MatrixTransformer::MatrixTransformer(RenderSystem& renderSystem, const Drawable& _parent)
		: parent ( _parent )
	{
		if ( !m_pVertexConstantBuffer )
		{
			m_pVertexConstantBuffer = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>( renderSystem );
		}
	}


// Functions:

	void MatrixTransformer::Bind(RenderSystem& renderSystem) noexcept
	{
		m_pVertexConstantBuffer->Update( renderSystem,
			                           DirectX::XMMatrixTranspose( parent.GetTransformXM() 
										                         * renderSystem.GetProjection() ) );

		m_pVertexConstantBuffer->Bind( renderSystem );
	}

	std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> MatrixTransformer::m_pVertexConstantBuffer;

}