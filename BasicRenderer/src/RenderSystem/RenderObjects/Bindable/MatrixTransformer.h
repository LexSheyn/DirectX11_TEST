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

		VertexConstantBuffer<DirectX::XMMATRIX> m_VertexConstantBuffer;

		const Drawable& parent;
	};
}

#endif // MATRIXTRANSFORMER_H