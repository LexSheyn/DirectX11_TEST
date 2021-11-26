#ifndef VERTEXCONSTANTBUFFER_H
#define VERTEXCONSTANTBUFFER_H

#include "ConstantBuffer.h"

namespace dx11
{
	template<typename C>
	class VertexConstantBuffer : public ConstantBuffer<C>
	{
	public:

		using ConstantBuffer<C>::ConstantBuffer;

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override
		{
			Bindable::GetContext( renderSystem )->VSSetConstantBuffers( 0u, 1u, ConstantBuffer<C>::m_pConstantBuffer.GetAddressOf() );
		}

	};
}

#endif // VERTEXCONSTANTBUFFER_H