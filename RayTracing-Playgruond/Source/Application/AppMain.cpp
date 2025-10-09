#include "Framework/Application.h"
#include "Framework/ClientEntry.h"

#include "AppLayer.h"

Ry_App::Application* Ry_App::CreateApplication(int argc, char** argv)
{
	Ry_App::ApplicationSpecification spec;
	spec.Name = "Ray-Tracing Playground";

	Ry_App::Application* app = new Ry_App::Application(spec);
	app->PushLayer<AppLayer>();

	//Additional app configs
	app->ToggleMenuBarState(false);

	return app;
}