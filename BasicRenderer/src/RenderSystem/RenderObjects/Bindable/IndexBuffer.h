#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "Bindable.h"

namespace dx11
{
	class IndexBuffer : public Bindable
	{
	public:

	// Constructors and Destructor:

		IndexBuffer( RenderSystem& renderSystem, const std::vector<uint32>& indices );

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override;

	// Accessors:

		const uint32& GetCount() const noexcept;

	protected:

		uint32 count;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
	};
}

#endif // INDEXBUFFER_H