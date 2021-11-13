#pragma once

#include "Core.h"
#include "Window/Window.h"
#include "Events/ApplicationEvent.h"

#include "ImGui/ImGuiLayer.h"

namespace CarData {

	struct ResultData
	{
		ResultData() 
		{ 
			empty = true; 
			medieAn = -1;
			medieKm = -1;
			mediePret = -1;

		}

		int medieAn;
		int medieKm;
		int mediePret;
		float conversionRate;

		bool empty;
	};

	class Application
	{
	public:

		Application();
		~Application();

		void Run();
		void OnEvent(Event& e);
		void OnUpdate();

		Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }

		void GenerateData(const char* str);

		ResultData& GetResultData() { return m_ResultData; }

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

	private:
		ResultData m_ResultData = ResultData();

		ImGuiLayer* m_imguiLayer;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

		static Application* s_Instance;

	};
}