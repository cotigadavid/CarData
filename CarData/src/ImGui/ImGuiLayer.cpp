#include "cdpch.h"
#include "ImGuiLayer.h"

#include "TempGui/imgui.h"

#include "TempGui/imgui_impl_glfw.h"
#include "TempGui/imgui_impl_opengl3.h"
//#include "ImGui/ImGuiRenderer.h"
#include "Core/Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <fstream>
//std::ifstream fin2;

void TextCentered(std::string text) {
	auto windowWidth = ImGui::GetWindowSize().x;
	auto textWidth = ImGui::CalcTextSize(text.c_str()).x;

	ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
}


CarData::ResultData layerResultData;

namespace CarData {


	ImGuiLayer::ImGuiLayer()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);

		dispatcher.Dispatch<MouseButtonPressedEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		//dispatcher.Dispatch<MouseScrolledEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		//dispatcher.Dispatch<KeyPressedEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		//dispatcher.Dispatch<KeyTypedEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
		//dispatcher.Dispatch<KeyReleasedEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		//dispatcher.Dispatch<WindowResizeEvent>(CD_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
	
		//io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		io.DisplaySize = ImVec2(1000, 562);

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 1.0f));

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
		ImGui::SetNextWindowSize(ImVec2(1000, 562));
		ImGui::SetNextWindowPos(ImVec2(0, 0));

		bool open;
		ImGui::Begin("Car Data", &open, flags);


		ImGui::SetCursorPosX(10);
		ImGui::SetCursorPosY(10);
		if (ImGui::Button("?", ImVec2(25.0f, 25.0f)))
		{
			open2 = !open2;
		}

		static char str[1280] = "";

		ImGui::SetWindowFontScale(2);
		TextCentered("Car Data");
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetWindowHeight() / 10 - ImGui::CalcTextSize("Car Data").y);
		ImGui::Text("Car Data");

		ImGui::SetWindowFontScale(1);
		ImGui::Spacing();
		ImGui::Spacing();
		TextCentered("  Search  ");

		bool ok = false;
		if (ImGui::Button("  Search  ", ImVec2(0, 0)))
		{
			errorCode = 0;
			layerResultData.empty = true;
			ok = true;
			//app.GenerateData(str);
			//layerResultData = app.GetResultData();
		}

		ImGui::SetWindowFontScale(1.5);
		ImGui::SetCursorPosX(100 - 3 * ImGui::GetTextLineHeightWithSpacing() + 55);
		ImGui::SetCursorPosY(ImGui::GetCursorPosY() + ImGui::GetWindowHeight() / 7 - ImGui::CalcTextSize("Your link").y);
		ImGui::Text("Your link");

		ImGui::SameLine();
		ImGui::InputText("", str, IM_ARRAYSIZE(str));

		ImGui::SameLine();
		const char* items[] = { "EURO", "RON" };
		static int itemIndex = 0;

		ImGui::BeginListBox("", ImVec2(3 * ImGui::GetTextLineHeightWithSpacing(), 2.1 * ImGui::GetTextLineHeightWithSpacing()));
		//ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())
		for (int i = 0; i < IM_ARRAYSIZE(items); ++i)
		{
			const bool isSelected = (itemIndex == i);
			if (ImGui::Selectable(items[i], isSelected))
				itemIndex = i;
			if (isSelected)
				ImGui::SetItemDefaultFocus();
		}

		ImGui::EndListBox();

		if (!layerResultData.empty)
		{
			//CD_INFO("DAD");
			CD_INFO("{0}", layerResultData.conversionRate);

			std::stringstream ss;
			ss << layerResultData.medieAn;
			ss << " ";
			ss << layerResultData.medieKm;
			ss << " ";
			ss << layerResultData.mediePret;
			//ss << layerResultData.carburantMap;

			std::string word;
			std::vector<std::string> words;
			while (ss >> word)
			{
				words.push_back(word);
			}

			ImGui::Spacing();
			ImGui::Spacing();
			ImGui::Spacing();
			
			ImGui::SetCursorPosX((ImGui::GetWindowSize().x - 300) / 2);
			ImGui::BeginTable("table", 3, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersInner | ImGuiTableFlags_NoHostExtendX, ImVec2(0.0f, 0.0f));

			ImGui::TableSetupColumn("one", ImGuiTableColumnFlags_WidthFixed, 100.0f); 
			ImGui::TableSetupColumn("two", ImGuiTableColumnFlags_WidthFixed, 100.0f); 
			ImGui::TableSetupColumn("three", ImGuiTableColumnFlags_WidthFixed, 100.0f);

			ImGui::TableNextRow();

			ImGui::TableNextColumn(); ImGui::Text("an");
			ImGui::TableNextColumn(); ImGui::Text("km");
			ImGui::TableNextColumn(); ImGui::Text("pret");

			if (itemIndex == 1)
			{
				words[2] = std::to_string(int(std::stoi(words[2]) * layerResultData.conversionRate));
			}

			ImGui::TableNextColumn(); ImGui::Text(words[0].c_str());
			ImGui::TableNextColumn(); ImGui::Text(words[1].c_str());
			ImGui::TableNextColumn(); ImGui::Text(words[2].c_str());

			ImGui::EndTable();


		}
		else if (errorCode == 1)
		{
			TextCentered("No link");
			ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.0f, 1.0f), "No link");
		}

		else if (errorCode == 2)
		{
			TextCentered("Invalid link");
			ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.0f, 1.0f), "Invalid link");
		}

		if (ok == true) 
		{
			app.GenerateData(str);
			layerResultData = app.GetResultData();
		}

		ImGui::SetWindowFontScale(1);
		ImGui::End();

		{
			
			static ImGuiWindowFlags flags2 = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			ImGui::SetNextWindowSize(ImVec2(515, 150));
			ImGui::SetNextWindowPos(ImVec2((1000 - 515) / 2, (562 - 150) / 2 + 100));

			//CD_ERROR("{0}", open2);

			if (open2)
			{
				ImGui::Begin("Help", &open2, flags2);

				ImGui::Text("1. Access the following link: ");
				ImGui::PushItemWidth(500);
				static char str0[128] = "https://www.olx.ro/auto-masini-moto-ambarcatiuni/autoturisme/";
				ImGui::InputText("", str0, IM_ARRAYSIZE(str0) + 10, ImGuiInputTextFlags_ReadOnly);
				ImGui::PopItemWidth();
				//ImGui::Text("https://www.olx.ro/auto-masini-moto-ambarcatiuni/autoturisme/");
				ImGui::Text("2. Fill in the desired filters");
				ImGui::Text("3. Make sure there are no parts for sale at the top of the page");
				ImGui::Text("4. Copy the page link and paste it in the field");
				ImGui::Text("Note that the search may take up to a few minutes");

				ImGui::End();
			}

		}
		ImGui::PopStyleColor();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;

		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;

		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());

		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();

		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		//io.KeysDown[e.GetKeyCode()] = true;

		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		//io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		//if (keycode > 0 && keycode < 0x10000)
			//io.AddInputCharacter((unsigned short)keycode);


		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());

		return false;
	}

}