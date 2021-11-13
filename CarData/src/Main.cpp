#include "cdpch.h"

#include "Core/Application.h"

//extern CarData::Application* CarData::CreateApplication();

int main(int argc, char** argv)
{
	CarData::Log::Init();

	auto app = new CarData::Application();
	app->Run();
	delete app;

}

