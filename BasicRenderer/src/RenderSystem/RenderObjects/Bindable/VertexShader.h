#ifndef VERTEXSHADER_H
#define VERTEXSHADER_H

#include "Bindable.h"

namespace dx11
{
	class VertexShader : public Bindable
	{
	public:

	// Constructors and Destructor:

		VertexShader( RenderSystem& renderSystem, const std::wstring& filePath );

	// Functions:

		void Bind( RenderSystem& renderSystem ) noexcept override;

	// Accessors:

		ID3DBlob* GetBytecode() const noexcept;

	protected:

	// Variables:

		Microsoft::WRL::ComPtr<ID3DBlob> m_pBytecodeBlob;
		Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	};
}

#endif // VERTEXSHADER_H