#pragma once

#include <vector>
#include "Core.h"
#include "Layer.h"

namespace TrexEngine
{ 

	struct LayerStructure 
	{
		LayerStructure() : m_Layer(NULL), Enable(true) {}
		LayerStructure(Layer* p_Layer, bool p_Enable) : m_Layer(p_Layer), Enable(p_Enable) {}

		Layer* m_Layer = NULL;
		bool Enable = true;
	};

	class  LayerContainer
	{
	public:

		TX_API LayerContainer();
		TX_API ~LayerContainer();

		TX_API void PushLayer(Layer* p_NewLayer);
		TX_API void PushOverLayer(Layer* p_NewLayer);

		TX_API void PopLayer();
		TX_API void PopOverLayer();

		TX_API void EnableLayer(std::string p_LayerName);

		TX_API void DisableLayer(std::string p_LayerName);

		TX_API inline LayerStructure* GetOverLayer() { return m_OverLayerPointer; }

		TX_API inline std::vector<LayerStructure>& GetLayers() { return m_Layers; }

	public:

		std::vector<LayerStructure>::iterator begin() { return m_Layers.begin(); }
		std::vector<LayerStructure>::iterator end() { return m_Layers.end(); }

	private:

		std::vector<LayerStructure> m_Layers;
		LayerStructure* m_OverLayerPointer = NULL;
	};

};