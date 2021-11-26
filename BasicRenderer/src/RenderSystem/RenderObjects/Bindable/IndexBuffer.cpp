#include "../../../PrecompiledHeaders/stdafx.h"
#include "IndexBuffer.h"

namespace dx11
{
// Constructors and Destructor:

	IndexBuffer::IndexBuffer(RenderSystem& renderSystem, const std::vector<uint32>& indices)
		: count( static_cast<uint32>( indices.size() ) )
	{
		D3D11_BUFFER_DESC index_buffer_desc = {};

		index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
		index_buffer_desc.CPUAccessFlags = 0u;
		index_buffer_desc.MiscFlags = 0u;
		index_buffer_desc.ByteWidth = static_cast<uint32>( count * sizeof(uint16) );
		index_buffer_desc.StructureByteStride = sizeof( uint16 );

		D3D11_SUBRESOURCE_DATA index_subresource_data = {};

		Bindable::GetDevice( renderSystem )->CreateBuffer( &index_buffer_desc, &index_subresource_data, &m_pIndexBuffer );
	}


// Functions:

	void IndexBuffer::Bind(RenderSystem& renderSystem) noexcept
	{
		Bindable::GetContext( renderSystem )->IASetIndexBuffer( m_pIndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0u );
	}


// Accessors:

	const uint32& IndexBuffer::GetCount() const noexcept
	{
		return count;
	}

}