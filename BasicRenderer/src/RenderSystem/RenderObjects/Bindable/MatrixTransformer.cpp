#include "../../../PrecompiledHeaders/stdafx.h"
#include "MatrixTransformer.h"

namespace dx11
{
// Constructors and Destructor:

	MatrixTransformer::MatrixTransformer(RenderSystem& renderSystem, const Drawable& _parent)
		: m_VertexConstantBuffer( renderSystem ),
		  parent ( _parent )
	{
	}


// Functions:

	void MatrixTransformer::Bind(RenderSystem& renderSystem) noexcept
	{
		m_VertexConstantBuffer.Update( renderSystem,
			                           DirectX::XMMatrixTranspose( parent.GetTransformXM() 
										                         * renderSystem.GetProjection() ) );

		m_VertexConstantBuffer.Bind( renderSystem );
	}

}