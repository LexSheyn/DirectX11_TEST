#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "Bindable.h"

namespace dx11
{
	class VertexBuffer : public Bindable
	{
	public:

	// Constructors and Destructor:

		template<class V>
		VertexBuffer( RenderSystem& renderSystem, const std::vector<V>& vertices )
			: stride( sizeof( V ) )
		{
			D3D11_BUFFER_DESC buffer_desc = {};

			buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			buffer_desc.Usage = D3D11_USAGE_DEFAULT;
			buffer_desc.CPUAccessFlags = 0u;
			buffer_desc.MiscFlags = 0u;
			buffer_desc.ByteWidth = static_cast<uint32>( sizeof( V ) * vertices.size() );
			buffer_desc.StructureByteStride = sizeof( V );

			D3D11_SUBRESOURCE_DATA subresource_data = {};

			subresource_data.pSysMem = vertices.data();

			Bindable::GetDevice( renderSystem )->CreateBuffer( &buffer_desc, &subresource_data, &m_pVertexBuffer );
		}

		void Bind( RenderSystem& renderSystem ) noexcept override;

	protected:

		uint32 stride;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
	};
}

#endif // VERTEXBUFFER_H