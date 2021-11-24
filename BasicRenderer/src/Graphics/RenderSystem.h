#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "HrException.h"
#include "DeviceRemovedException.h"

namespace dx11
{
	class RenderSystem
	{
	public:

	// Constructors and Destructor:

		RenderSystem( HWND hWnd );
		RenderSystem( const RenderSystem& ) = delete;

		~RenderSystem();

	// Operatprs:

		RenderSystem& operator=(const RenderSystem&) = delete;

	// Functions:

		void EndFrame();

		void ClearBuffer( float32 red, float32 green, float32 blue ) noexcept;

	private:

	// Exceptions:

		HrException m_HrException;
		DeviceRemovedException m_DeviceRemovedException;

	// Variables:

		ID3D11Device*        m_pDevice    = nullptr;

		IDXGISwapChain*      m_pSwapChain = nullptr;

		ID3D11DeviceContext* m_pContext   = nullptr;

		ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
	};
}

#endif // RENDERSYSTEM_H