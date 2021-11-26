#include "../../../PrecompiledHeaders/stdafx.h"
#include "PixelShader.h"

namespace dx11
{
// Constructors and Destructor:

	PixelShader::PixelShader(RenderSystem& renderSystem, const std::wstring& filePath)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> pBlob;

		D3DReadFileToBlob( filePath.c_str(), &pBlob );

		Bindable::GetDevice( renderSystem )->CreatePixelShader( pBlob->GetBufferPointer(),
			                                                    pBlob->GetBufferSize(),
			                                                    nullptr,
			                                                    &m_pPixelShader);
	}


// Functions:

	void PixelShader::Bind(RenderSystem& renderSystem) noexcept
	{
		Bindable::GetContext( renderSystem )->PSSetShader( m_pPixelShader.Get(), nullptr, 0u );
	}

}