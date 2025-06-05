#include <string>
#include "Layer.h"

namespace TrexEngine
{

	Layer::Layer(std::string p_LayerName) 
		: LayerName(p_LayerName)
	{
		
	}

	Layer::~Layer()
	{

	}


	TX_API void Layer::EnableLayer()
	{
		Enable = true;
	}

	TX_API void Layer::DisableLayer()
	{
		Enable = false;

	}

};