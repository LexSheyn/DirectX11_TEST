#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "../../RenderSystem.h"

#include "../Bindable/IndexBuffer.h"

class Bindable;

namespace dx11
{
	class Drawable
	{
		template<class T>
		friend class DrawableBase;

	public:

	// Constructors and Destructor:

		Drawable() = default;
		Drawable( const Drawable& ) = delete;

		virtual ~Drawable() = default;

	// Functions:

		void Draw( RenderSystem& renderSystem ) const noexcept;

		virtual void Update( const float& dt ) noexcept = 0;

		void AddBind( std::unique_ptr<Bindable> bind ) noexcept;

		void AddIndexBuffer( std::unique_ptr<class IndexBuffer> indexBuffer ) noexcept;

	// Accessors:

		virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;

	private:

	// Private Accessors:

		virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;

	// Variables:

		const class IndexBuffer* pIndexBuffer = nullptr;

		std::vector<std::unique_ptr<Bindable>> binds;
	};
}

#endif // DRAWABLE_H