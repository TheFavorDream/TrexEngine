#include "LayerContainer.h"


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
			m_Layers.push_back(p_NewLayer);
			return;
		}

		m_Layers.push_back(m_OverLayerPointer);
		m_Layers[m_Layers.size()-2] = p_NewLayer;

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
			m_Layers.push_back(p_NewLayer);
			m_OverLayerPointer = m_Layers[m_Layers.size() - 1];
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
			m_Layers[m_Layers.size() - 1]->OnDettach();
			m_Layers.pop_back();
			return;
		}

		m_Layers[m_Layers.size() - 2]->OnDettach();

		m_Layers.pop_back();
		m_Layers[m_Layers.size() - 1] = m_OverLayerPointer;

	}

	void LayerContainer::PopOverLayer()
	{
		if (m_OverLayerPointer == NULL)
			return;

		m_Layers.pop_back();
		m_OverLayerPointer->OnDettach();
		m_OverLayerPointer = NULL;
	}

};