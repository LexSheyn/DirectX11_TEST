#ifndef APPLICATION_H
#define APPLICATION_H

#include "../Window/Window.h"
#include "../Timer/Timer.h"

#include "../RenderSystem/RenderObjects/Drawable/Objects/Box.h"
#include "../RenderSystem/RenderObjects/Drawable/Objects/Pyramid.h"
#include "../RenderSystem/RenderObjects/Drawable/Objects/Melon.h"

namespace dx11
{
	class Application
	{
	public:

	// Constructors and Destructor:

		Application();

		~Application();

	// Functions:

		int32 Run();

	private:

	// Private Functions:

		void DoFrame();

	// Components:

		Window m_Window;
		Timer  m_Timer;

	// TEST:

		std::vector<std::unique_ptr<class Drawable>> drawables;

		static constexpr size_t nDrawables = 180;
	};
}

#endif // APPLICATION_H