/*
#include "../PrecompiledHeaders/stdafx.h"
#include "DxgiInfoManager.h"

namespace dx11
{
// Constructors and Destructor:

	DxgiInfoManager::DxgiInfoManager()
	{
	// Define function sifnature of DXGIGetDebugInterface

		typedef HRESULT ( WINAPI* DXGIGetDebugInterface )( REFIID, void** );

	// Load the dll that contains a function DXGIGetDebugInterface:

		const auto hModDxgiDebug = LoadLibraryExA( "dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS);

		if ( hModDxgiDebug == nullptr )
		{
			throw GetLastError();
		}

	// Get address of DXGIGetDebugInterface in dll:

		const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>( reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface")) );

		if ( DxgiGetDebugInterface == nullptr )
		{
			throw GetLastError();
		}

		DxgiGetDebugInterface( __uuidof( IDXGIInfoQueue ), reinterpret_cast<void**>(m_pDxgiInfoQueue) );
	}

	DxgiInfoManager::~DxgiInfoManager()
	{
		if ( m_pDxgiInfoQueue == nullptr )
		{
			m_pDxgiInfoQueue->Release();
		}
	}


// Functions:

	void DxgiInfoManager::Set() noexcept
	{
	}


// Accessors:

	std::vector<std::string> DxgiInfoManager::GetMessages() const
	{
		return std::vector<std::string>();
	}
}
*/