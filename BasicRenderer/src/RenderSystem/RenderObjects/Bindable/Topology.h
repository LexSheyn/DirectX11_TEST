#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "Bindable.h"

namespace dx11
{
	class Topology : public Bindable
	{
	public:

	// Constructors and Destructor:

		Topology( RenderSystem& renderSystem, D3D11_PRIMITIVE_TOPOLOGY _type );

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override;

	protected:

	// Variables:

		D3D11_PRIMITIVE_TOPOLOGY type;
	};
}

#endif // TOPOLOGY_H