#include "../../../PrecompiledHeaders/stdafx.h"
#include "VertexShader.h"

namespace dx11
{
// Constructors and Destructor:

	VertexShader::VertexShader(RenderSystem& renderSystem, const std::wstring& filePath)
	{
		D3DReadFileToBlob( filePath.c_str(), &m_pBytecodeBlob );

		Bindable::GetDevice( renderSystem )->CreateVertexShader( m_pBytecodeBlob->GetBufferPointer(),
			                                                     m_pBytecodeBlob->GetBufferSize(),
			                                                     nullptr,
			                                                     &m_pVertexShader);
	}
	

// Functions:

	void VertexShader::Bind(RenderSystem& renderSystem) noexcept
	{
		Bindable::GetContext( renderSystem )->VSSetShader( m_pVertexShader.Get(), nullptr, 0u );
	}
	

// Accessors:

	ID3DBlob* VertexShader::GetBytecode() const noexcept
	{
		return m_pBytecodeBlob.Get();
	}
}