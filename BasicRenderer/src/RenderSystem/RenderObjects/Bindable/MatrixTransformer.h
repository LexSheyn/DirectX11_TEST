#ifndef MATRIXTRANSFORMER_H
#define MATRIXTRANSFORMER_H

#include "PixelConstantBuffer.h"
#include "VertexConstantBuffer.h"

#include "../Drawable/Drawable.h"

namespace dx11
{
	class MatrixTransformer : public Bindable
	{
	public:

	// Constructors and Destructor:

		MatrixTransformer( RenderSystem& renderSystem, const Drawable& _parent );

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override;

	private:

	// Variables:

		static std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> m_pVertexConstantBuffer;

		const Drawable& parent;
	};
}

#endif // MATRIXTRANSFORMER_H