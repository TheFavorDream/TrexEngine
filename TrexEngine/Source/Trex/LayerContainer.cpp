#include "Include/LayerContainer.h"


namespace TrexEngine
{

	LayerContainer::LayerContainer()
	{

	}


	LayerContainer::~LayerContainer()
	{

	}

	void LayerContainer::PushLayer(Layer* p_NewLayer)
	{

		if (p_NewLayer == NULL)
		{
			Logger::CoreLogger->SetError("Layer pointer was NULL");
			return;
		}

		if (m_OverLayerPointer == NULL) 
		{
			m_Layers.push_back({p_NewLayer, true});
			return;
		}

		m_Layers.push_back({m_OverLayerPointer, true});
		m_Layers[m_Layers.size()-2] = {p_NewLayer, true};

	}
	void LayerContainer::PushOverLayer(Layer* p_NewLayer)
	{

		if (p_NewLayer == NULL)
		{
			Logger::CoreLogger->SetError("OverLayer pointer was NULL");
			return;
		}

		if (m_OverLayerPointer == NULL)
		{
			m_Layers.push_back({ p_NewLayer, true });
			m_OverLayerPointer = m_Layers[m_Layers.size() - 1].m_Layer;
			return;
		}

	}

	void LayerContainer::PopLayer()
	{
		//if the vector was empty, there is nothing to delete
		if (m_Layers.empty())
			return;

		if (m_OverLayerPointer == NULL)
		{
			m_Layers[m_Layers.size() - 1].m_Layer->OnDettach();
			m_Layers.pop_back();
			return;
		}

		m_Layers[m_Layers.size() - 2].m_Layer->OnDettach();

		m_Layers.pop_back();
		m_Layers[m_Layers.size() - 1].m_Layer = m_OverLayerPointer;

	}

	void LayerContainer::PopOverLayer()
	{
		if (m_OverLayerPointer == NULL)
			return;

		m_Layers.pop_back();
		m_OverLayerPointer->OnDettach();
		m_OverLayerPointer = NULL;
	}

	TX_API void LayerContainer::EnableLayer(std::string p_LayerName)
	{
		for (auto &i : m_Layers)
		{
			if (i.m_Layer->GetLayerName() == p_LayerName)
			{
				i.Enable = true;
				Logger::CoreLogger->SetWarning(p_LayerName + " Layer got enabled");
				return;
			}
		}

		Logger::CoreLogger->SetWarning(p_LayerName + " Layer not found to enable");
	}

	TX_API void LayerContainer::DisableLayer(std::string p_LayerName)
	{
		for (auto &i : m_Layers)
		{
			if (i.m_Layer->GetLayerName() == p_LayerName)
			{
				i.Enable = false;
				Logger::CoreLogger->SetWarning(p_LayerName + " Layer got Disabled");
				return;
			}
		}
		Logger::CoreLogger->SetWarning(p_LayerName + " Layer not found to disable");

	}

};