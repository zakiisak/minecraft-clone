#pragma once

#include <GL/glew.h>
#include <string>
#include "window.h"
#include "input.h"

namespace Core {

	struct AppConfig {
		std::string title;
		int width;
		int height;

		int msaaSamples;
	};

	class App {
	public:
		App(AppConfig config);
		~App();

		static App* Instance;

		virtual void create();
		virtual void render();
		virtual void update();

		int run();

		float deltaTime();
		float getFps();

		Window* getWindow();

	protected:
		AppConfig m_Config;
		Window* m_Window;

	private:
		float m_Delta = 0;

		void initImGui();
	};
}