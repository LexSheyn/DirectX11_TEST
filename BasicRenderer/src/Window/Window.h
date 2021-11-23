#ifndef WINDOW_H
#define WINDOW_H

#include "../../resource.h"

#include "WindowException.h"

#include "../InputDevices/Keyboard/Keyboard.h"
#include "../InputDevices/Mouse/Mouse.h"

namespace dx11
{
	class Window
	{
	public:

	// Constructors and Destructor:

		Window( int32 width, int32 height, const char* name );
		Window( const Window& ) = delete;

		~Window();

	// Functions:

		//

	// Accessors:

		//

	// Modifiers:

		void SetTitle( const std::string& title );

	// Operators:

		Window& operator=( const Window& ) = delete;

	// Input devices:

		Keyboard keyboard;
		Mouse    mouse;

	private:

	// Private Functions:

		static LRESULT __stdcall HandleMessageSetup( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) noexcept;

		static LRESULT __stdcall HandleMessageThunk( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) noexcept;

		LRESULT HandleMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) noexcept;

	// Variables:

		int32 m_Width;
		int32 m_Height;

		HWND m_hWnd;

	// WindowException:

	//	WindowException m_Exception;

	// Private WindowClass:

		// Singleton manages registration/cleanup of window class.
		class WindowClass
		{
		public:

		// Accessors:

			static const char* GetName() noexcept;

			static HINSTANCE   GetInstance() noexcept;

		private:

		// Private Constructors and Destructor:

			WindowClass() noexcept;
			WindowClass(const WindowClass&) = delete;

			~WindowClass();

		// Private Operators:

			WindowClass& operator=(const WindowClass&) = delete;

		// Variables:

			static constexpr const char* wndClassName = "DirectX11_Window";

			static WindowClass wndClass;

			HINSTANCE hInstance;
		};
		
	};
}

#endif // WINDOW_H