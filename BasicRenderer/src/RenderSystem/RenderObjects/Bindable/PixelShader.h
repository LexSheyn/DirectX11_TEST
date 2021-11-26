#ifndef PIXELSHADER_H
#define PIXELSHADER_H

#include "Bindable.h"

namespace dx11
{
	class PixelShader : public Bindable
	{
	public:

	// Constructors and Destructor:

		PixelShader( RenderSystem& renderSystem, const std::wstring& filePath );

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override;

	protected:

	// Variables:

		Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
	};
}

#endif // PIXELSHADER_H