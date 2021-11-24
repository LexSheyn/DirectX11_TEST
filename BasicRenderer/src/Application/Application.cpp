#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

namespace dx11
{
// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1050, 450, "DirectX11_Test_Window" )
	{
	}

	Application::~Application()
	{
	}


// Functions:

	int32 Application::Run()
	{
		while ( true ) // CONDITION REQUIRED!!!
		{
		// Process all messages pending, but to not block for new messages:

			if ( const auto ecode = Window::ProcessMessages() )
			{
			// If return optional has value, means we're quitting so return exit code
				
				return *ecode;
			}
			
			this->DoFrame();

		// Limit cpu cycles to ~ 60 frames per second:

			Sleep(15);
		}
	}


// Private Functions:

	void Application::DoFrame()
	{
	// Elapsed time in the window title:

		const float time = m_Timer.Peek();

		std::ostringstream out_str_stream;

		out_str_stream << "Time elapsed: " << std::setprecision( 1 ) << std::fixed << time << "s.";

		m_Window.SetTitle( out_str_stream.str() );

	// Clearing buffer with the red hue depends on time elapsed:

		const float color = std::sin( m_Timer.Peek() ) / 2.0f + 0.5f;

		m_Window.GetRenderSystem().ClearBuffer( color, color / 1.7f, 0.0f );

		m_Window.GetRenderSystem().EndFrame();
	}

}