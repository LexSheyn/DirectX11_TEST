#ifndef CONSTANTBUFFER_H
#define CONSTANTBUFFER_H

#include "Bindable.h"

namespace dx11
{
	template<typename C>
	class ConstantBuffer : public Bindable
	{
	public:

	// Constructors:

		ConstantBuffer( RenderSystem& renderSystem, const C& consts )
		{
			D3D11_BUFFER_DESC constant_buffer_desc = {};

			constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constant_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
			constant_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			constant_buffer_desc.MiscFlags = 0u;
			constant_buffer_desc.ByteWidth = sizeof( consts );
			constant_buffer_desc.StructureByteStride = 0u;

			D3D11_SUBRESOURCE_DATA subresource_data = {};

			subresource_data.pSysMem = &consts;

			Bindable::GetDevice( renderSystem )->CreateBuffer( &constant_buffer_desc, &subresource_data, &m_pConstantBuffer );
		}
		ConstantBuffer( RenderSystem& renderSystem )
		{
			D3D11_BUFFER_DESC constant_buffer_desc = {};

			constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			constant_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
			constant_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			constant_buffer_desc.MiscFlags = 0u;
			constant_buffer_desc.ByteWidth = sizeof( C );
			constant_buffer_desc.StructureByteStride = 0u;

			Bindable::GetDevice( renderSystem )->CreateBuffer( &constant_buffer_desc, nullptr, &m_pConstantBuffer );
		}

	// Functions:

		void Update( RenderSystem& renderSystem, const C& consts )
		{
			D3D11_MAPPED_SUBRESOURCE mapped_subresource = {};

			Bindable::GetContext( renderSystem )->Map( m_pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mapped_subresource );

			std::memcpy( mapped_subresource.pData, &consts, sizeof( consts ) );

			Bindable::GetContext( renderSystem )->Unmap( m_pConstantBuffer.Get(), 0u );
		}

	protected:

	// Variables:

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pConstantBuffer;
	};
}

#endif // CONSTANTBUFFER_H