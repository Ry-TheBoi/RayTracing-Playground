#pragma once

#ifdef RYAPP_PLATFORM_WINDOWS

extern Ry_App::Application* Ry_App::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace Ry_App {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			Ry_App::Application* app = Ry_App::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef RYAPP_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return Ry_App::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return Ry_App::Main(argc, argv);
}

#endif // RYAPP_DIST

#endif // APP_PLATFORM_WINDOWS
