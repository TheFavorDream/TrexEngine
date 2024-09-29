#pragma once

#include <vector>
#include "../Core/Core.h"
#include "../Application/Layer.h"

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

		TX_API inline Layer* GetOverLayer() const { return m_OverLayerPointer; }
		TX_API inline std::vector<Layer*>& GetLayers() { return m_Layers; }

	public:

		std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layers.end(); }

	private:

		std::vector<Layer*> m_Layers;
		Layer* m_OverLayerPointer = NULL;
	};

};