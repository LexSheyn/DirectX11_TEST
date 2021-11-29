#include "../PrecompiledHeaders/stdafx.h"
#include "Application.h"

namespace dx11
{
// Constructors and Destructor:

	Application::Application()
		: m_Window ( 1050, 450, "DirectX11_Test_Window" )
	{
		class Factory
		{
		public:
			Factory(RenderSystem& gfx)
				:
				gfx(gfx)
			{}
			std::unique_ptr<Drawable> operator()()
			{
				switch (typedist(rng))
				{
				case 0:
					return std::make_unique<Pyramid>(
						gfx, rng, adist, ddist,
						odist, rdist
						);
				case 1:
					return std::make_unique<Box>(
						gfx, rng, adist, ddist,
						odist, rdist, bdist
						);
				case 2:
					return std::make_unique<Melon>(
						gfx, rng, adist, ddist,
						odist, rdist, longdist, latdist
						);
				default:
					assert(false && "bad drawable type in factory");
					return {};
				}
			}
		private:
			RenderSystem& gfx;
			std::mt19937 rng{ std::random_device{}() };
			std::uniform_real_distribution<float> adist{ 0.0f,PI_f32 * 2.0f };
			std::uniform_real_distribution<float> ddist{ 0.0f,PI_f32 * 0.5f };
			std::uniform_real_distribution<float> odist{ 0.0f,PI_f32 * 0.08f };
			std::uniform_real_distribution<float> rdist{ 6.0f,20.0f };
			std::uniform_real_distribution<float> bdist{ 0.4f,3.0f };
			std::uniform_int_distribution<int> latdist{ 5,20 };
			std::uniform_int_distribution<int> longdist{ 10,40 };
			std::uniform_int_distribution<int> typedist{ 0,2 };
		};

		Factory f(m_Window.GetRenderSystem());
		drawables.reserve(nDrawables);
		std::generate_n(std::back_inserter(drawables), nDrawables, f);

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
		const auto dt = m_Timer.Mark();
		m_Window.GetRenderSystem().ClearBuffer(0.07f, 0.0f, 0.12f);
		for (auto& d : drawables)
		{
			d->Update(dt);
			d->Draw(m_Window.GetRenderSystem());
		}
		m_Window.GetRenderSystem().EndFrame();
	}

}