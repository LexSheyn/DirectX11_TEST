#ifndef INPUTLAYOUT_H
#define INPUTLAYOUT_H

#include "Bindable.h"

namespace dx11
{
	class InputLayout : public Bindable
	{
	public:

	// Constructors and Destructor:

		InputLayout( RenderSystem& renderSystem,
		  const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout,
			         ID3DBlob* pVertexShaderBytecode );

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override;

	protected:

	// Variables:

		Microsoft::WRL::ComPtr<ID3D11InputLayout> m_pInputLayout;
	};
}

#endif // INPUTLAYOUT_H