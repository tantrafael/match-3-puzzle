#pragma once

#include <memory>

#include <SDL2/SDL.h>

namespace King {
	class SdlWindow;

	class GlContext {
	public:
		GlContext(SdlWindow& sdlWindow);
		operator SDL_GLContext();
	private:
		std::unique_ptr<void, void(*)(SDL_GLContext)> mContext;
	};
}