#ifndef PIXELCONSTANTBUFFER_H
#define PIXELCONSTANTBUFFER_H

#include "ConstantBuffer.h"

namespace dx11
{
	template<typename C>
	class PixelConstantBuffer : public ConstantBuffer<C>
	{
	public:

		using ConstantBuffer<C>::ConstantBuffer;

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override
		{
			Bindable::GetContext( renderSystem )->PSSetConstantBuffers( 0u, 1u, ConstantBuffer<C>::m_pConstantBuffer.GetAddressOf() );
		}
	};
}

#endif // PIXELCONSTANTBUFFER_H