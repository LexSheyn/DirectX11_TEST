#include "../../../PrecompiledHeaders/stdafx.h"
#include "InputLayout.h"

namespace dx11
{
// Constructors and Destructor:

	InputLayout::InputLayout(RenderSystem& renderSystem, 
		          const std::vector<D3D11_INPUT_ELEMENT_DESC>& layout, 
		                     ID3DBlob* pVertexShaderBytecode)
	{
		Bindable::GetDevice( renderSystem )->CreateInputLayout( layout.data(),
			                 UINT(layout.size()),
			                 pVertexShaderBytecode->GetBufferPointer(),
			                 pVertexShaderBytecode->GetBufferSize(),
			                 &m_pInputLayout);
	}

	void InputLayout::Bind(RenderSystem& renderSystem) noexcept
	{
		Bindable::GetContext( renderSystem )->IASetInputLayout( m_pInputLayout.Get() );
	}

}