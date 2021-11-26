#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

namespace dx11
{
// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1050, 450, "DirectX11_Test_Window" )
	{
		std::mt19937 rng(std::random_device{}());
		std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
		std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 2.0f);
		std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
		std::uniform_real_distribution<float> rdist(6.0f, 20.0f);

		for (auto i = 0; i < 80; i++)
		{
			boxes.push_back(std::make_unique<Box>( m_Window.GetRenderSystem(), 
				                                   rng, 
				                                   adist,
				                                   ddist, 
				                                   odist, 
				                                   rdist));
		}

		m_Window.GetRenderSystem().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 9.0f / 21.0f, 0.5f, 40.0f));
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
//	// Elapsed time in the window title:
//
//		const float time = m_Timer.Peek();
//
//		std::ostringstream out_str_stream;
//
//		out_str_stream << "Time elapsed: " << std::setprecision( 1 ) << std::fixed << time << "s.";
//
//		m_Window.SetTitle( out_str_stream.str() );
//
//	// Clearing buffer with the red hue depends on time elapsed:
//
//		const float color = std::sin( m_Timer.Peek() ) / 2.0f + 0.5f;
//
//		m_Window.GetRenderSystem().ClearBuffer( color * 0.2f , color * 0.2f, color * 0.2f );
//
//	// Working on DrawTestTriangle:
//
//		m_Window.GetRenderSystem().DrawIndexedTEST( -m_Timer.Peek(), 0.0f, 0.0f );
//
//		m_Window.GetRenderSystem().DrawIndexedTEST( m_Timer.Peek(),
//			                   static_cast<float32>(m_Window.mouse.GetX()) /  525.0f  - 1.0f, 
//			                  (static_cast<float32>(m_Window.mouse.GetY()) / -225.0f) + 1.0f );

		// TEST
		auto dt = m_Timer.Mark();

		m_Window.GetRenderSystem().ClearBuffer(0.07f, 0.0f, 0.12f);

		for (auto& box : boxes)
		{
			box->Update( dt );
			box->Draw( m_Window.GetRenderSystem() );
		}

		m_Window.GetRenderSystem().EndFrame();
	}

}