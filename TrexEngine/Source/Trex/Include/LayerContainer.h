#pragma once

#include <vector>
#include "Core.h"
#include "Layer.h"

namespace TrexEngine
{ 

	class  LayerContainer
	{
	public:

		TX_API LayerContainer();
		TX_API ~LayerContainer();

		TX_API void PushLayer(Layer* p_NewLayer);
		TX_API void PushOverLayer(Layer* p_NewLayer);

		TX_API void PopLayer();
		TX_API void PopOverLayer();

		TX_API std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		TX_API std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:
		std::vector<Layer*> m_Layers;
		Layer** m_OverLayerPointer = NULL;
	};

};