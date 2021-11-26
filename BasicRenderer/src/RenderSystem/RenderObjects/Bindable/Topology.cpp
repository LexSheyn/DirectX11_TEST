#include "../../../PrecompiledHeaders/stdafx.h"
#include "Topology.h"

namespace dx11
{
// Constructors and Destructor:

	Topology::Topology(RenderSystem& renderSystem, D3D11_PRIMITIVE_TOPOLOGY _type)
		: type( _type )
	{
	}


// Functions:

	void Topology::Bind(RenderSystem& renderSystem) noexcept
	{
		Bindable::GetContext( renderSystem )->IASetPrimitiveTopology( type );
	}

}