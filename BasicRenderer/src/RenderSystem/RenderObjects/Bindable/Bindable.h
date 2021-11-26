#ifndef BINDABLE_H
#define BINDABLE_H

#include "../../RenderSystem.h"

namespace dx11
{
	class Bindable
	{
	public:

	// Destructor:

		virtual ~Bindable() = default;

	// Functions:

		virtual void Bind( RenderSystem& renderSystem ) noexcept = 0;

	protected:

	// Accessors:

		static ID3D11DeviceContext* GetContext( RenderSystem& renderSystem ) noexcept;

		static ID3D11Device* GetDevice( RenderSystem& renderSystem ) noexcept;

	//	static DxgiInfoManager& GetInfoManager&( RenderSystem& renderSystem ) noexcept;
	};
}

#endif // BINDABLE_H