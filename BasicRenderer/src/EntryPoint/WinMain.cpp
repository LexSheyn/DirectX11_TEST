#include "../PrecompiledHeaders/stdafx.h"

#include "../Window/Window.h"

int32 __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int32 nCmdShow)
{
// Create Window:

	try
	{
		dx11::Window window(1050, 450, "DirectX11 Test Window");

		// Message pump:

		MSG message;

		while (GetMessageA(&message, nullptr, 0u, 0u) > 0)
		{
			TranslateMessage(&message);

			DispatchMessageA(&message);

		// MOUSE TEST

			while ( !window.mouse.IsEmpty() )
			{
				const auto mouse_event = window.mouse.Read();

				switch ( mouse_event.GetType() )
				{
					case dx11::MouseEvent::Type::Leave:
					{
						window.SetTitle("Mouse gone!");

						break;
					}

					case dx11::MouseEvent::Type::Enter:
					{
						window.SetTitle("Mouse here!");

						break;
					}
				}
			}
		}

		return static_cast<int32>(message.wParam);
	}
	catch ( const dx11::Exception& exception )
	{
		MessageBoxA( nullptr, exception.what(), exception.GetType(), MB_OK | MB_ICONEXCLAMATION );
	}
	catch ( const std::exception& exception )
	{
		MessageBoxA( nullptr, exception.what(), "Standatd Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch ( ... )
	{
		MessageBoxA( nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION );
	}
	return -1;
}