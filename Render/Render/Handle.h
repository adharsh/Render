#pragma once

#include "graphics/Window.h"
#include "Game.h"
#include "Engine.h"

namespace ginkgo {

	class Handle 
	{
	private:
		Window& window;

	public:
		Handle(Window& a)
			: window(a)
		{}

		Window& getWindow() { return window; }


	};

}
