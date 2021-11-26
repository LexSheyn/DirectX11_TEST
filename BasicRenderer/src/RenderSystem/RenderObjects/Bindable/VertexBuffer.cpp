#include "../../../PrecompiledHeaders/stdafx.h"
#include "VertexBuffer.h"

namespace dx11
{
// Functions:

	void VertexBuffer::Bind(RenderSystem& renderSystem) noexcept
	{
		const uint32 offset = 0u;

		Bindable::GetContext( renderSystem )->IASetVertexBuffers( 0u, 1u, m_pVertexBuffer.GetAddressOf(), &stride, &offset );
	}

}