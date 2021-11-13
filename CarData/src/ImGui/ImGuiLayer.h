#pragma once

#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

//#include "Core/Application.h"
//#include <fstream>

//struct CarData::ResultData;

namespace CarData {

	class ImGuiLayer
	{
	public:
		ImGuiLayer();

		//void OnAttach();
		void OnEvent(Event& e);
		void OnUpdate();

	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	public:
		int errorCode = 0;  // 0 - no error
							// 1 - no link
							// 2 - bad link

	private:
		//ResultData layerResultData;
		float m_Time = 0.0f;
		bool open2 = false;
	};
}