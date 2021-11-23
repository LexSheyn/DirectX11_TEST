#ifndef GRAPHICS_H
#define GRAPHICS_H

namespace dx11
{
	class Graphics
	{
	public:

	// Constructors and Destructor:

		Graphics( HWND hWnd );
		Graphics( const Graphics& ) = delete;		

		~Graphics();

	// Operatprs:

		Graphics& operator=(const Graphics&) = delete;

	private:

	// Variables:

		ID3D11Device*        m_pDevice    = nullptr;

		IDXGISwapChain*      m_pSwapChain = nullptr;

		ID3D11DeviceContext* m_pContext   = nullptr;
	};
}

#endif // GRAPHICS_H