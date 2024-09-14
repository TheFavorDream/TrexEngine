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

		if ( m_OverLayerPointer == NULL)
		{
			m_Layers.push_back(p_NewLayer);
		}

		else
		{
			m_Layers.emplace(m_Layers.end(), p_NewLayer);
			m_Layers.push_back(*m_OverLayerPointer);
		}

		p_NewLayer->OnAttach();
	}
	void LayerContainer::PushOverLayer(Layer* p_NewLayer)
	{

		if (p_NewLayer == NULL)
		{
			Logger::CoreLogger->SetError("OverLayer pointer was NULL");
			return;
		}

		m_OverLayerPointer = &p_NewLayer;

		m_Layers.push_back(p_NewLayer);

		p_NewLayer->OnAttach();
	}

	void LayerContainer::PopLayer()
	{
		if (m_Layers.empty())
		{
			return;
		}

		if (m_OverLayerPointer != NULL)
		{
			m_Layers.at(m_Layers.size() - 2)->OnDettach();
			delete m_Layers.at(m_Layers.size() - 2);
			m_Layers.emplace(m_Layers.end() - 1, *m_OverLayerPointer);
		}

		m_Layers.at(m_Layers.size() - 1)->OnDettach();
		delete m_Layers.at(m_Layers.size()-1);
		m_Layers.pop_back();

	}

	void LayerContainer::PopOverLayer()
	{
		if (m_Layers.empty())
		{
			return;
		}

		m_Layers.pop_back();
		delete *m_OverLayerPointer;
		m_OverLayerPointer = NULL;
	}

};