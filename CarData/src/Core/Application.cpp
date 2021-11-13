#include "cdpch.h"

#include "Application.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <fstream>


namespace CarData {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		/*m_medieAn = 0;
		m_medieKm = 0;
		m_mediePret = 0;*/

		//fout.flush();

		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_imguiLayer = new ImGuiLayer();
 	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_imguiLayer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnUpdate()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		m_imguiLayer->OnEvent(e);
	}

	void Application::GenerateData(const char* str)
	{
		if (strlen(str))
		{
			std::ifstream fin("output.txt");
			std::ofstream fout("linkFile.txt");
			std::ofstream fout2("result.txt");
			
			//CD_INFO("merge");
			fout.flush();
			fout << str;
			fout.close();

			Py_Initialize();

			PyObject* obj = Py_BuildValue("s", "test2.py");
			FILE* file = _Py_fopen_obj(obj, "r+");
			if (file != NULL) {
				PyRun_SimpleFile(file, "test2.py");
			}

			if (fin.peek() == std::ifstream::traits_type::eof())
			{
				m_ResultData.empty = true;
				m_imguiLayer->errorCode = 2;
				CD_ERROR("INVALID LINK");
				return;
			}

			std::string line;

			int type;
			int sumaKm = 0;
			int nrMasini = 0;
			int sumaAni = 0;
			int sumaPret = 0;

			std::getline(fin, line);
			m_ResultData.conversionRate = std::stof(line);

			while (std::getline(fin, line))
			{
				nrMasini++;

				std::string SType = line.substr(0, 3);
				if (SType == "olx")
					type = 0;
				else
					type = 1;

				std::string an = line.substr(22, 4);
				sumaAni += stoi(an);

				unsigned int pos = line.find("km");
				std::string km;
				if (type == 0)
					km = line.substr(34, pos - 35);
				else
					km = line.substr(34, pos - 34);
				if (km.find(" ") != std::string::npos)
					km.erase(km.find(" "), 1);
				sumaKm += stoi(km) / 1000;

				//unsigned int pos2 = line.find("cm");
				//std::string motor = line.substr(pos + 3, pos2 - pos - 4);

				//unsigned int posFinalCarburant = line.find("/");
				//std::string carburant = line.substr(pos2 + 4, posFinalCarburant - pos2 - 5);

				unsigned int pos3 = line.find("km");
				//unsigned int pos4 = line.find("EUR");
				std::string pret = line.substr(pos3 + 3);
				if (pret.find(" ") != std::string::npos)
					pret.erase(pret.find(" "), 1);
				sumaPret += stoi(pret);


				fout2 << an << " " << km << " " << pret << "\n";
			}
			//ResultData m_ResultData;
			if (nrMasini != 0)
			{
				m_ResultData.medieAn = sumaAni / nrMasini;
				m_ResultData.medieKm = (sumaKm / nrMasini) * 1000;
				m_ResultData.mediePret = sumaPret / nrMasini;
				m_ResultData.empty = false;

			}
				//fout2 << sumaAni / nrMasini << " " << (sumaKm / nrMasini) * 1000 << " " << sumaPret / nrMasini << "\n";

			m_imguiLayer->errorCode = 0;
			Py_Finalize();
			fin.close();
			fout2.close();
		}

		else
		{
			m_ResultData.empty = true;
			m_imguiLayer->errorCode = 1;
			CD_ERROR("No Link");
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
