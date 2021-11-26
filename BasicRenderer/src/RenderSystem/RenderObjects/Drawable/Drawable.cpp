#include "../../../PrecompiledHeaders/stdafx.h"
#include "Drawable.h"

namespace dx11
{
// Functions:

	void Drawable::Draw(RenderSystem& renderSystem) const noexcept
	{
		for ( auto& bind : binds )
		{
			bind->Bind( renderSystem );
		}

		renderSystem.DrawIndexed( pIndexBuffer->GetCount() );
	}
	
	void Drawable::AddBind(std::unique_ptr<Bindable> bind) noexcept
	{
		assert( "*Must* ise AddIndexBuffer to bind index buffer" && typeid(&bind) != typeid(IndexBuffer) );

		binds.push_back( std::move( bind ) );
	}
	
	void Drawable::AddIndexBuffer(std::unique_ptr<class IndexBuffer> indexBuffer) noexcept
	{
		assert( "Attempting to add index buffer a second time" && pIndexBuffer == nullptr );

		pIndexBuffer = indexBuffer.get();

		binds.push_back( std::move( indexBuffer ) );
	}
}