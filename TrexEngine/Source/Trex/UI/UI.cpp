#include "UI.h"


namespace TrexEngine
{
	TrexUI::TrexUI(Window* pWindow)
	{
		Logger::CoreLogger->SetInfo("TrexUI Constructed");
		Init(pWindow);
	}

	TrexUI::~TrexUI()
	{
		Shutdown();
	}

	

	int TrexUI::Init(Window* pWindow)
	{
		Logger::CoreLogger->SetInfo("Ui Core Init");
		
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		m_IO = &ImGui::GetIO();
		m_IO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		ImGui_ImplGlfw_InitForOpenGL(pWindow->GetWindow(), true);
		ImGui_ImplOpenGL3_Init(m_GLSLVersion);

		return 0;
	}

	int TrexUI::Shutdown()
	{


		for (auto &i : m_Widgets)
		{
			delete i.second;
		}

		m_Widgets.clear();

		Logger::CoreLogger->SetInfo("Ui Core Shutdown");
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		return 0;
	}

	TX_API uint32 TrexUI::CreateWidget(std::string pTitle, ImVec2 pSize, ImVec2 pPosition, ImGuiWindowFlags pFlags)
	{
		Widget* widget = new Widget(m_Widgets.size(),pTitle, pSize, pPosition, pFlags);
		m_Widgets[widget->GetID()] = widget;
		return widget->GetID();
	}

	TX_API Widget* TrexUI::GetWidget(uint32 ID)
	{
		WidgetValidation(ID);
		return m_Widgets[ID];
	}

	TX_API bool TrexUI::DoesWidgetExist(uint32 ID)
	{
		return (m_Widgets.find(ID) == m_Widgets.end()) ? false : true;
	}

	int TrexUI::RemoveWidget(uint32 pID)
	{
		auto loc = m_Widgets.find(pID);

		if (loc != m_Widgets.end())
		{
			delete m_Widgets[pID];
			m_Widgets.erase(m_Widgets.find(pID));

			return 0;
		}
		return 1;
	}

	void TrexUI::Render()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		for (auto &i : m_Widgets)
		{
			if (!i.second->IsOpen())
				continue;

			i.second->Update();
			i.second->Render();
		}



		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (m_IO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void TrexUI::WidgetValidation(uint32 pID)
	{
		if (m_Widgets.find(pID) == m_Widgets.end())
		{
			Logger::CoreLogger->SetError("Invalid Widget ID");
			STOP();
		}
	}


};
