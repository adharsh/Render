#pragma once

#include "graphics/Window.h"

namespace ginkgo {

	class Handle 
	{
	private:
		Window* window;

	public:
		Handle(Window* window)
			: window(window)
		{}

		Window* getWindow() { return window; }

	};

}
