#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "Bindable.h"

namespace dx11
{
	class IndexBuffer : public Bindable
	{
	public:

	// Constructors and Destructor:

		IndexBuffer( RenderSystem& renderSystem, const std::vector<uint16>& indices );

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override;

	// Accessors:

		const UINT& GetCount() const noexcept;

	protected:

		UINT count;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer;
	};
}

#endif // INDEXBUFFER_H